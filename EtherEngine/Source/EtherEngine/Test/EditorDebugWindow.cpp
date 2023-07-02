#include <EtherEngine/Test/EditorDebugWindow.h>
#include <Base/BaseInput.h>
#include <Base/WindowsDefine.h>
#include <EtherEngine/EditorApplication.h>


//----- EditorDebug 定義
namespace EtherEngine {
    void EditorDebugWindow::Start(void) {
    }
    void EditorDebugWindow::Update(void) {
    }
    void EditorDebugWindow::Draw(void) {
        ImGui::ShowDemoWindow();
        ImGui::Begin(ImGuiDefine::Name::WINDOW_DEBUG.c_str());
        if (InputSystem::GetMousePostion().has_value()) {
            //----- FPS表示
            {
                // @ MEMO : 後回し。微妙。おとなしくEditorApplicationから持ってきた方が効果的かと
                //using namespace std::chrono;
                //ImGui::Text("FPS : %d", m_timer.GetDeltaTime().count());
            }
            //----- マウスポインタ位置表示
            ImGui::Text("MousePostion : %d %d", InputSystem::GetMousePostion().value().x(), InputSystem::GetMousePostion().value().y());
        }
        ImGui::End();
    }
}
