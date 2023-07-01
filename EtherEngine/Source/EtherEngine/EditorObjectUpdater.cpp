#include <EtherEngine/EditorObjectUpdater.h>
#include <Base/WindowsDefine.h>
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/EditorObjectStorage.h>


namespace EtherEngine {
    // �G�f�B�^�[�I�u�W�F�N�g�ɍX�V�������s��
    void EditorUpdater::Update(void) {
        auto update = EditorObjectStorage::Get()->GetEditorObjectAll();
        for (auto&& it : update) {
            it.GetAtomicData().Update();
        }
        EditorObjectStorage::Get()->DeleteEditorObjectsDelete();
    }

    // �G�f�B�^�[�I�u�W�F�N�g�̕`�揈�����s��
    void EditorUpdater::Draw(void) {
        //----- IMGUI�`�揈��
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        //----- �펞�����E�h�b�L���O�\�ȃE�B���h�E��\������
        {
            //----- ���j���[�o�[�p�E�B���h�E�\��
            ImGui::Begin(ImGuiDefine::Name::WINDOW_MENU.c_str(), NULL, ImGuiWindowFlags_None
                | ImGuiWindowFlags_NoTitleBar
                | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoScrollbar
                | ImGuiWindowFlags_NoScrollWithMouse
                | ImGuiWindowFlags_NoCollapse
                | ImGuiWindowFlags_NoBackground
                | ImGuiWindowFlags_NoSavedSettings
                | ImGuiWindowFlags_MenuBar
                | ImGuiWindowFlags_HorizontalScrollbar
                | ImGuiWindowFlags_NoFocusOnAppearing
                | ImGuiWindowFlags_NoDocking
            );
            //----- ���j���[�\��
            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    //if (ImGui::MenuItem("Hoge", NULL, true)) {
                    //}
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            //----- �E�B���h�E�ʒu�E���W�ݒ�
            ImGui::SetWindowPos(ImVec2(0 - 1, 0));
            ImGui::SetWindowSize(ImVec2(EditorApplication::Get()->GetWindSize().x() + 2, EditorApplication::Get()->GetWindSize().y()));

            //----- �h�b�L���O�p�E�B���h�E�쐬
            {
                ImGui::Begin(ImGuiDefine::Name::WINDOW_SCENE_VIEW.c_str(), NULL, ImGuiWindowFlags_None
                    | ImGuiWindowFlags_NoTitleBar
                    | ImGuiWindowFlags_NoResize
                    | ImGuiWindowFlags_NoMove
                    | ImGuiWindowFlags_NoScrollbar
                    | ImGuiWindowFlags_NoScrollWithMouse
                    | ImGuiWindowFlags_NoCollapse
                    | ImGuiWindowFlags_NoBackground
                    | ImGuiWindowFlags_NoSavedSettings
                    | ImGuiWindowFlags_HorizontalScrollbar
                );
                ImGui::SetWindowPos(ImVec2(0 - 1, 18));
                ImGui::SetWindowSize(ImVec2(EditorApplication::Get()->GetWindSize().x() + 2, EditorApplication::Get()->GetWindSize().y() - 18));
                ImGui::End();
            }
            ImGui::End();
        }

        //----- EditorObject�`��
        auto draw = EditorObjectStorage::Get()->GetEditorObjectAll();
        for (auto&& it : draw) {
            it.GetAtomicData().Draw();
        }

        EditorObjectStorage::Get()->DeleteEditorObjectsDelete();

        ImGui::Render();
    }
}
