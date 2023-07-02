#include <EtherEngine/Test/EditorDebugWindow.h>
#include <Base/BaseInput.h>


//----- EditorDebug ’è‹`
namespace EtherEngine {
    void EditorDebugWindow::Draw(void) {
        ImGui::ShowDemoWindow();
        ImGui::Begin("hoge");
        if (InputSystem::GetMousePostion().has_value()) {
            ImGui::Text("%d %d", InputSystem::GetMousePostion().value().x(), InputSystem::GetMousePostion().value().y());
        }
        ImGui::End();
    }
}
