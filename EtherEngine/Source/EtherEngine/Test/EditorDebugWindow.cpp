#include <EtherEngine/Test/EditorDebugWindow.h>
#include <Base/BaseInput.h>
#include <Base/SceneLoader.h>
#include <Base/WindowsDefine.h>
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/EditorSceneSerializer.h>
#include <EtherEngine/ProjectMediation.h>
#include <EtherEngine/CommandPrompt.h>
#include <EtherEngine/EditorAssemblyRefresh.h>


//----- EditorDebug ��`
namespace EtherEngine {
    // �R���X�g���N�^
    EditorDebugWindow::EditorDebugWindow(EditorObject* editorObject) 
        : EditorWindowBase(editorObject, ImGuiDefine::Name::WINDOW_DEBUG,true, ImGuiWindowFlags_None,EditorWindowSizeType::AutoSizeFixed) {
    }
    void EditorDebugWindow::StartWindow(void) {
    }
    void EditorDebugWindow::UpdateWindow(void) {
    }
    void EditorDebugWindow::DrawWindow(void) {
        ImGui::ShowDemoWindow();
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

            //----- Refresh
            if (ImGui::Button("Script Refresh")) {
                Refresh::AssemblyRefresh();
            }
        }
    }
}
