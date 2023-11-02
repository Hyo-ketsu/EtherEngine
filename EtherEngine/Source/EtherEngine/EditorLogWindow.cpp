#include <EtherEngine/EditorLogWindow.h>
#include <EtherEngine/EditorAssemblyRefresh.h>


//----- EditorLogWindow 定義
namespace EtherEngine {
    void EditorLogWindow::StartWindow(void) {
        //----- 一応削除
        LogSystem::DeleteLogWindowMessage();
    }
    void EditorLogWindow::UpdateWindow(void) {
        //----- ログの取得
        m_log = LogSystem::GetLogWindowMessage();

    }
    void EditorLogWindow::DrawWindow(void) {
        //----- ログ削除ボタン表示
        if (ImGui::Button("Delete")) {
            LogSystem::DeleteLogWindowMessage();
            m_log.clear();
        }

        //----- ログ表示
        ImGui::BeginChild("LogWindow");
        for (auto&& it : m_log) {
            // @ MEMO : 時間表示がおかしいがまあ放置。後で直す
            //auto message = std::format("{:%X}", it.m_timeStamp) + " : " + it.m_message;
            ImGui::Text(it.m_message.c_str());
        }
        ImGui::Text("BuildLog");
        for (auto&& it : Refresh::GetRefreshLog()) {
            int hoge = 1;//ImGui::Text(it)
        }
        ImGui::EndChild();
    }
}
