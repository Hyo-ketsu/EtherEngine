#include <EtherEngine/EditorWindowBase.h>
#include <Base/MathUtility.h>
#include <EtherEngine/EditorObjectStorage.h>
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/EditorComponentHelper.h>


namespace EtherEngine {
    // コンストラクタ
    EditorWindowBase::EditorWindowBase(EditorObject* editorObject, const std::string& name, const bool isUseTransform, 
        const ImGuiWindowFlags& flag, const EditorWindowSizeType& sizeType, const Eigen::Vector2f& windowSize)
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

        //----- サイズ設定がManualなら何もしない
        if (m_sizeType == EtherEngine::EditorWindowSizeType::ManualSize) return;

        //----- キャッシング
        auto gameObject = EditorComponentHelper::GetEditorObject(this);
        auto& transform = gameObject->AccessTransform();
        auto& position = transform.AccessPostion();
        auto& scale = transform.AccessScale();
        return;

        //----- 既に取得している過去Transformと現在Transformが違う(=他コンポーネント等で座標や拡縮が編集されている)か
        bool isEqualPos = m_prevTransform.has_value()   // 全て同値であればtrue
            && MathUtility::FloatEqual(position.x(), m_prevTransform->GetPostion().x())
            && MathUtility::FloatEqual(position.y(), m_prevTransform->GetPostion().y())
            && MathUtility::FloatEqual(position.z(), m_prevTransform->GetPostion().z());
        bool isEqualScale = m_prevTransform.has_value() // 全て同値であればtrue
            && MathUtility::FloatEqual(scale.x(), m_prevTransform->GetScale().x())
            && MathUtility::FloatEqual(scale.y(), m_prevTransform->GetScale().y())
            && MathUtility::FloatEqual(scale.z(), m_prevTransform->GetScale().z());
        if (isEqualPos == false || isEqualScale == false) { // 同値でないものがあるか
            //----- ImGuiウィンドウの座標、サイズを自身の親エディターオブジェクトのTrasnformに適用する
            if (m_isUseTranform) {
                //----- 拡縮を設定
                switch (m_sizeType) {
                case EtherEngine::EditorWindowSizeType::AutoSizeFixed:
                    for (int i = 0; i < 2; i++) {
                        scale[i] = fabsf(ImGui::GetContentRegionAvail()[i]);
                    }
                    break;
                case EtherEngine::EditorWindowSizeType::AutoSizeFluctuation:
                    for (int i = 0; i < 2; i++) {
                        scale[i] = fabsf(ImGui::GetWindowSize()[i]);
                        if (scale[i] < fabsf(ImGui::GetContentRegionAvail()[i])) scale[i] = fabsf(ImGui::GetContentRegionAvail()[i]);
                    }
                    break;
                    //case EtherEngine::EditorWindowSizeType::SemiAutoSize
                }
                scale = Eigen::Vector3f(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y, scale.z());
            }
        }
        else {
            //----- 自身の親エディターオブジェクトのTransformをImGuiウィンドウの座標、サイズに適用する
            if (m_isUseTranform) {
                //----- 最適なサイズを設定
                ImGui::SetWindowSize(ImVec2(scale.x(),scale.y()));
            }
        }

        //----- 過去座標を現在のTransformで上書き
        m_prevTransform = transform;
    }


    std::unordered_map<std::string, uint> EditorWindowBase::ms_windowCount; // ウィンドウの使用数
}
