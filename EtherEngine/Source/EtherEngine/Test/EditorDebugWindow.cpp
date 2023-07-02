#include <EtherEngine/Test/EditorDebugWindow.h>
#include <Base/BaseInput.h>
#include <Base/WindowsDefine.h>
#include <EtherEngine/EditorApplication.h>


//----- EditorDebug ’è‹`
namespace EtherEngine {
    void EditorDebugWindow::Draw(void) {
        ImGui::ShowDemoWindow();
        ImGui::Begin(ImGuiDefine::Name::WINDOW_DEBUG.c_str());
        if (InputSystem::GetMousePostion().has_value()) {
            
            ImGui::Text("MousePostion : %d %d", InputSystem::GetMousePostion().value().x(), InputSystem::GetMousePostion().value().y());
        }
        ImGui::End();
    }
}
