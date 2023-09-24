#include <EtherEngine/EditorWindowBase.h>
#include <Base/MathUtility.h>
#include <EtherEngine/EditorObjectStorage.h>
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/EditorComponentHelper.h>


namespace EtherEngine {
    // コンストラクタ
    EditorWindowBase::EditorWindowBase(EditorObject* editorObject, const std::string& name, const bool isUseTransform, 
        const ImGuiWindowFlags& flag, const EditorWindowSizeType& sizeType, const Eigen::Vector2i& windowSize)
        : EditorComponentBase(editorObject)
        , m_name(name) 
        , m_isOpen(true) 
        , m_isUseTranform(isUseTransform)
        , m_flags(flag) 
        , m_sizeType(sizeType) {
        //----- 同名ウィンドウがあればウィンドウ名を設定する
        auto windowCountFindResult = ms_windowCount.find(m_name);
        if (windowCountFindResult != ms_windowCount.end()) {
            //----- 存在した。使用数の数だけ空白追加(Debugでは(数)の形式)
#ifdef _DEBUG
            m_name += " (" + std::to_string(windowCountFindResult->second) + ")";
#else
            for (int i = 0; i < windowCountFindResult->second; i++) {
                m_name += " ";
            }
#endif // _DEBUG
            windowCountFindResult->second++;
        }
        else {
            //----- 存在しない。追加
            ms_windowCount.emplace(m_name, 1);
        }

        //----- ウィンドウのサイズ関連設定
        if (windowSize.x() < 0 && windowSize.y() < 0) {
            //----- どちらも負数。設定されていないものとする
            m_sizeType = decltype(m_sizeType)::ManualSize;
        }
        else {
            //----- どちらかが正数。設定
            m_windowSize = ImVec2(windowSize.x(), windowSize.y());
        }
    }


    // 初期化処理
    void EditorWindowBase::Start(void) {
        //----- サブクラス処理実行
        StartWindow(); 
    }
    // 削除処理
    void EditorWindowBase::Delete(void) {
        //----- サブクラス処理実行
        DeleteWindow();
    }
    // 更新処理
    void EditorWindowBase::Update(void) {
        //----- サブクラス処理実行
        UpdateWindow();
    }
    void EditorWindowBase::Draw(void) {
        //----- ウィンドウ描画
        ImGui::Begin(m_name.c_str(), &m_isOpen, m_flags);
        DrawWindow();
        DrawLateWindow();
            
        ImGui::End();
    }


    // ウィンドウ描画後に行う処理
    void EditorWindowBase::DrawLateWindow(void) {
        //----- 消されたのであれば削除する
        if (m_isOpen == false) {
            EditorObjectStorage::Get()->DeleteEditorObject(EditorComponentHelper::GetEditorObject(this)->GetHandle());
            return;
        }

        //----- キャッシング
        auto gameObject = EditorComponentHelper::GetEditorObject(this);
        auto& transform = gameObject->AccessTransform();
        auto& postion = transform.AccessPostion();
        auto& scale = transform.AccessScale();

        //----- 拡縮に対する処理
        do {
            if (m_isUseTranform) {
                //----- いずれかに該当するなら処理をしない
                if (m_sizeType == EditorWindowSizeType::ManualSize) break;
                if (m_windowSize.has_value() == false) break;

                //----- Transformの拡縮に対してImGuiウィンドウのサイズを適用する
                switch (m_sizeType) {
                case EtherEngine::EditorWindowSizeType::AutoSizeFixed:  // 自動固定サイズ
                    for (int i = 0; i < 2; i++) {
                        scale[i] = fabsf((*m_windowSize)[i]);
                    }
                    break;
                case EtherEngine::EditorWindowSizeType::AutoSizeFluctuation:    // 自動変動サイズ
                    for (int i = 0; i < 2; i++) {
                        scale[i] = fabsf(ImGui::GetWindowSize()[i]);
                        if (scale[i] < fabsf((*m_windowSize)[i])) scale[i] = fabsf((*m_windowSize)[i]);
                    }
                    break;
                //case EtherEngine::EditorWindowSizeType::SemiAutoSize
                }
                
                //----- 調整後の拡縮をImGuiウィンドウに設定する
                ImGui::SetWindowSize(ImVec2(scale.x(), scale.y()));
            }
            else {
                //----- ImGuiウィンドウの拡縮を変更する
                ImVec2 size;
                switch (m_sizeType) {
                case EtherEngine::EditorWindowSizeType::AutoSizeFixed:  // 自動固定サイズ
                    for (int i = 0; i < 2; i++) {
                        size[i] = fabsf((*m_windowSize)[i]);
                    }
                    break;
                case EtherEngine::EditorWindowSizeType::AutoSizeFluctuation:    // 自動変動サイズ
                    for (int i = 0; i < 2; i++) {
                        size[i] = fabsf(ImGui::GetWindowSize()[i]);
                        if (size[i] < fabsf((*m_windowSize)[i])) size[i] = fabsf((*m_windowSize)[i]);
                    }
                    break;
                    //case EtherEngine::EditorWindowSizeType::SemiAutoSize
                }

                //----- 調整後の拡縮を設定する
                ImGui::SetWindowSize(ImVec2(size.x, size.y));
            }
        } while (false);

        //----- 座標に対する処理
        do {
            //----- Transformを使用しないのであれば何もしない
            if (m_isUseTranform == false) break;

            //----- 既に取得している過去座標と現在座標が違う(=他コンポーネント等で座標が編集されている)か
            bool isEqualPostion = m_prevTransform.has_value() // 全て同値であればtrue
                && MathUtility::FloatEqual(postion.x(), m_prevTransform->GetPostion().x())
                && MathUtility::FloatEqual(postion.y(), m_prevTransform->GetPostion().y());
            bool isEqualImGuiPostion = m_prevImGuiPostion.has_value() == false // 全て同値であればtrue
                || MathUtility::FloatEqual(ImGui::GetWindowPos().x, m_prevImGuiPostion->x)
                && MathUtility::FloatEqual(ImGui::GetWindowPos().y, m_prevImGuiPostion->y);

            //----- どちらかも true = ImGuiウィンドウかTransformの座標が変更されていないので何もしない
            if (isEqualPostion && isEqualImGuiPostion) break;

            //----- それぞれの座標を処理（両方動いていればTransformを優先する）
            if (isEqualPostion == false) {
                //----- Transformの座標が変わっている。Transformの座標をImGuiウィンドウの座標に適用
                ImGui::SetWindowPos(ImVec2(postion.x(), postion.y()));
            }
            if (isEqualImGuiPostion == false) {
                //----- ImGuiウィンドウの座標が変わっている。ImGuiウィンドウの座標をTransformの座標に適用
                postion = Eigen::Vector3f(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, postion.z());
            }
        } while (false);

        //----- 過去座標を現在のTransformで上書き
        m_prevTransform = transform;
        m_prevImGuiScale = ImGui::GetWindowSize();
        m_prevImGuiPostion = ImGui::GetWindowPos();
    }


    std::unordered_map<std::string, uint> EditorWindowBase::ms_windowCount; // ウィンドウの使用数
}
