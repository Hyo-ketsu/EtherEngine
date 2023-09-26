#include <EtherEngine/EditorProgressBar.h>
#include <Base/WindowsDefine.h>
#include <Base/MathUtility.h>


//----- 進捗クラス 定義
namespace EtherEngine {
    // コンストラクタ
    ProgressClass::ProgressClass(const float progress, const float max) 
        : m_progress(progress) 
        , m_max(max) {
    }


    // 進捗を取得する
    float ProgressClass::GetProgress(void) const {
        return m_progress / m_max;
    }
    // 終了したか
    bool ProgressClass::IsEnd(void) const {
        return MathUtility::FloatEqual(GetProgress(), 1.0f) || GetProgress() >= 1.0f;
    }
}




//----- EditorProgressBar 定義
namespace EtherEngine {
    // コンストラクタ
    EditorProgressBar::EditorProgressBar(EditorObject* editorObject, const std::string& message, Progress progress, const bool isSound) 
        : EditorPopupWindow(editorObject, ImGuiDefine::Name::WINDOW_PROGRESS_TITLE, EditorPopupControl::None, {100,30})
        , m_message(message) 
        , m_progress(progress) 
        , m_isSound(isSound) {
    }

    // ウィンドウ描画
    void EditorProgressBar::DrawWindow(void) {
        //----- テキスト表示
        ImGui::Text(m_message.c_str());

        //----- 進捗管理元が生きているか
        if (m_progress.expired()) {
            WindowKill();
            return;
        }

        //----- プログレスバーの表示
        ImGui::ProgressBar(m_progress.lock()->GetProgress());

        //----- 最後まで進んでいれば自ウィンドウを削除する
        if (m_progress.lock()->IsEnd()) {
            WindowKill();
            return;
        }
    }


    // プログレスバーを削除する
    void EditorProgressBar::WindowKill(void) {
        //----- 音を鳴らす
        if (m_isSound) {
            MessageBeep(-1);
        }

        //----- 自ポップアップを削除する
        m_isOpen = false;
    }
}
