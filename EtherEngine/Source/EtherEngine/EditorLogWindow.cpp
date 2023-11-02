#include <EtherEngine/EditorLogWindow.h>
#include <EtherEngine/EditorAssemblyRefresh.h>


//----- EditorLogWindow ��`
namespace EtherEngine {
    void EditorLogWindow::StartWindow(void) {
        //----- �ꉞ�폜
        LogSystem::DeleteLogWindowMessage();
    }
    void EditorLogWindow::UpdateWindow(void) {
        //----- ���O�̎擾
        m_log = LogSystem::GetLogWindowMessage();

    }
    void EditorLogWindow::DrawWindow(void) {
        //----- ���O�폜�{�^���\��
        if (ImGui::Button("Delete")) {
            LogSystem::DeleteLogWindowMessage();
            m_log.clear();
        }

        //----- ���O�\��
        ImGui::BeginChild("LogWindow");
        for (auto&& it : m_log) {
            // @ MEMO : ���ԕ\���������������܂����u�B��Œ���
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
