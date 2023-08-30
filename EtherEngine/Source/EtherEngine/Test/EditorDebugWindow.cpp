#include <EtherEngine/Test/EditorDebugWindow.h>
#include <Base/BaseInput.h>
#include <Base/SceneLoader.h>
#include <Base/WindowsDefine.h>
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/EditorSceneSerializer.h>
#include <EtherEngine/ProjectMediation.h>
#include <EtherEngine/MSVCMediation.h>


//----- EditorDebug ��`
namespace EtherEngine {
    void EditorDebugWindow::Start(void) {
    }
    void EditorDebugWindow::Update(void) {
    }
    void EditorDebugWindow::Draw(void) {
        ImGui::ShowDemoWindow();
        ImGui::Begin(ImGuiDefine::Name::WINDOW_DEBUG.c_str());
        if (InputSystem::GetMousePostion().has_value()) {
            //----- FPS�\��
            {
                // @ MEMO : ��񂵁B�����B���ƂȂ���EditorApplication���玝���Ă����������ʓI����
                //using namespace std::chrono;
                //ImGui::Text("FPS : %d", m_timer.GetDeltaTime().count());
            }
            //----- �}�E�X�|�C���^�ʒu�\��
            ImGui::Text("MousePostion : %d %d", InputSystem::GetMousePostion().value().x(), InputSystem::GetMousePostion().value().y());

            //----- ���݃V�[���o��
            if (SceneLoader::Get()->GetCurrentSceneData().has_value()) {
                ImGui::Text("CurrentScene : %s", SceneLoader::Get()->GetCurrentSceneData().value().c_str());
            }

            //----- �V�[�����o��
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
