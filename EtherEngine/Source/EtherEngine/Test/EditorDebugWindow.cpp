#include <EtherEngine/Test/EditorDebugWindow.h>
#include <Base/BaseInput.h>
#include <Base/SceneLoader.h>
#include <Base/WindowsDefine.h>
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/EditorSceneSerializer.h>
#include <EtherEngine/ProjectMediation.h>
#include <EtherEngine/MSVCMediation.h>


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

            //----- 現在シーン出力
            if (SceneLoader::Get()->GetCurrentSceneData().has_value()) {
                ImGui::Text("CurrentScene : %s", SceneLoader::Get()->GetCurrentSceneData().value().c_str());
            }

            //----- シーン情報出力
            if (ImGui::Button("OutPut Current SceneData")) {
                EditorSceneSerialize(PathClass::GetCurDirectory(), SceneLoader::Get()->GetCurrentSceneData().value());
            }

            //----- Build
            if (ImGui::Button("Script Build")) {
                MSVCMediation::Get()->Command(std::string("msbuild ") + ProjectMediation::Get()->GetSln().Get());
            }
        }
        ImGui::End();
    }
}
