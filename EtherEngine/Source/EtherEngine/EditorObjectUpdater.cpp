#include <EtherEngine/EditorObjectUpdater.h>
#include <Base/ConceptUtility.h>
#include <Base/EtherEngineUtility.h>
#include <Base/HandleHelper.h>
#include <Base/WindowsDefine.h>
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/EditorObjectStorage.h>

#include <EtherEngine/EditorBuildMenuWindow.h>

#include <EtherEngine/EditorLogWindow.h>
#include <EtherEngine/EditorOutliner.h>
#include <EtherEngine/EditorExplorerWindow.h>
#include <EtherEngine/EditorInspectorWindow.h>


namespace EtherEngine {
    // ���C�����j���[��\������
    // @ Temp : �\������E�B���h�E�̌^
    // @ Arg1 : �I�u�W�F�N�g���
    // @ Arg2 : �\����
    template <Concept::BaseOfConcept<EditorWindowBase> WindowType>
    void ShowWindowMenu(std::vector<BaseHandle<EditorObject>>* windows, const std::string& name);
}


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

        ////----- �펞�����E�h�b�L���O�\�ȃE�B���h�E��\������
        //{
        //    //----- ���j���[�o�[�p�E�B���h�E�\��
        //    if (ImGui::Begin(ImGuiDefine::Name::WINDOW_MENU.c_str(), NULL, ImGuiWindowFlags_None
        //        | ImGuiWindowFlags_NoTitleBar
        //        | ImGuiWindowFlags_NoResize
        //        | ImGuiWindowFlags_NoMove
        //        | ImGuiWindowFlags_NoScrollbar
        //        | ImGuiWindowFlags_NoScrollWithMouse
        //        | ImGuiWindowFlags_NoCollapse
        //        | ImGuiWindowFlags_NoBackground
        //        | ImGuiWindowFlags_NoSavedSettings
        //        | ImGuiWindowFlags_MenuBar
        //        | ImGuiWindowFlags_HorizontalScrollbar
        //        | ImGuiWindowFlags_NoFocusOnAppearing
        //        | ImGuiWindowFlags_NoDocking
        //        )) {
        //        //----- ���j���[�\��
        //        if (ImGui::BeginMenuBar()) {
        //            //----- "File"���ڕ\��
        //            if (ImGui::BeginMenu("File")) {
        //                //if (ImGui::MenuItem("Hoge", NULL, true)) {
        //                //}
        //                ImGui::EndMenu();
        //            }

        //            //----- "Menu" �\��
        //            if (ImGui::BeginMenu("Menu")) {
        //                using namespace EtherEngine::ImGuiDefine;

        //                //----- ���ڕ\��
        //                ShowWindowMenu<BuildMenu>(&m_windows, Name::WINDOW_BUILD_MENU);

        //                ImGui::EndMenu();
        //            }

        //            //----- "Editor Window"���ڕ\��
        //            if (ImGui::BeginMenu("Editor Window")) {
        //                using namespace EtherEngine::ImGuiDefine;

        //                //----- �S�폜���j���[�\��
        //                if (ImGui::MenuItem("All Window Delete", NULL)) {
        //                    for (auto&& it : m_windows) {
        //                        EditorObjectStorage::Get()->DeleteEditorObject(it);
        //                    }
        //                }

        //                //----- ���ڕ\��
        //                ShowWindowMenu<EditorLogWindow>(&m_windows, Name::WINDOW_LOG);
        //                ShowWindowMenu<EditorOutliner>(&m_windows, Name::WINDOW_OUTLINER);
        //                ShowWindowMenu<ExplorerWindow>(&m_windows, Name::WINDOW_EXPLORER);
        //                ShowWindowMenu<EditorInspectorWindow>(&m_windows, Name::WINDOW_INSPECTOR);

        //                ImGui::EndMenu();
        //            }
        //            ImGui::EndMenuBar();
        //        }
        //        //----- �Q�[���Đ��E��~�{�^���\��
        //        ImGui::Columns(5, (ImGuiDefine::Name::WINDOW_MENU + "GameButton Columns").c_str(), false);
        //        ImGui::Dummy(ImVec2()); ImGui::NextColumn(); ImGui::Dummy(ImVec2()); ImGui::NextColumn();
        //        if (ImGui::Button("Start")) EditorApplication::Get()->StartGameMode(); ImGui::SameLine();
        //        if (ImGui::Button("Stop")) EditorApplication::Get()->StopGameMode(); ImGui::SameLine();
        //        if (ImGui::Button("End")) EditorApplication::Get()->EndGameMode(); ImGui::SameLine();
        //        ImGui::Dummy(ImVec2()); ImGui::NextColumn(); ImGui::Dummy(ImVec2()); ImGui::NextColumn();

        //        //----- �E�B���h�E�ʒu�E���W�ݒ�
        //        Eigen::Vector2i windowPostion;
        //        Eigen::Vector2i frameSize;
        //        RECT clientSize;
        //        {
        //            auto hWnd = EditorApplication::Get()->GetHWND();

        //            //----- �ϐ��錾
        //            RECT windowSize;

        //            //----- �E�B���h�E�ʒu�E�T�C�Y���擾
        //            if (GetWindowRect(hWnd, &windowSize) == false) std::exception("Error! Non GetWindowRect");

        //            //----- �N���C�A���g�̈���擾
        //            if (GetClientRect(hWnd, &clientSize) == false) std::exception("Error! Non GetClientRect");

        //            //----- �t���[���T�C�Y�Z�o
        //            frameSize.x() = (windowSize.right - windowSize.left) - (clientSize.right - clientSize.left);
        //            frameSize.y() = (windowSize.bottom - windowSize.top) - (clientSize.bottom - clientSize.top);

        //            //----- �ŏI�I�Ȉʒu�v�Z
        //            windowPostion.x() = windowSize.left + clientSize.left;
        //            windowPostion.y() = windowSize.top + clientSize.top;
        //        }
        //        ImGui::SetWindowPos(ImVec2(windowPostion.x() + (frameSize.x() / 2), windowPostion.y() + (frameSize.y() / 2) + (frameSize.y() / 4)));
        //        ImGui::SetWindowSize(ImVec2(clientSize.right, 60));

        //        ImGui::End();
        //    }
        //}

        //----- EditorObject�`��
        auto draw = EditorObjectStorage::Get()->GetEditorObjectAll();
        for (auto&& it : draw) {
            it.GetAtomicData().Draw();
        }

        EditorObjectStorage::Get()->DeleteEditorObjectsDelete();

        ImGui::Render();
    }
    // �G�f�B�^�[�I�u�W�F�N�g�̕`��㏈�����s��
    void EditorUpdater::LateDraw(void) {
        //----- IMGUI�`��㏈��
        auto io = ImGui::GetIO();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }
}


namespace EtherEngine {
    // ���C�����j���[��\������
    template <Concept::BaseOfConcept<EditorWindowBase> WindowType>
    void ShowWindowMenu(std::vector<BaseHandle<EditorObject>>* windows, const std::string& name) {
        //----- �ꉞnull�`�F�b�N
        if (windows == nullptr) throw std::exception("Error! Null");

        //----- �\��
        if (ImGui::MenuItem(name.c_str(), NULL)) {
            //----- �쐬
            auto object = EditorObjectStorage::Get()->CreateEditorObject();

            //----- �����{��
            uint count = 0;  // �����I�u�W�F�N�g��
            for (auto&& it : *windows) {
                if (it.IsEnable() == false) continue;
                if (count == 0) {   // �d���������O���o���ۂ� Hoge(1) �ȂǂƏƍ����邽��
                    //----- �ʏ�̌���
                    if (it.GetNoAtomicData().GetName() == name) count++; 
                }
                else {
                    //----- ����
                    if (Utility::IsDuplicationName(it.GetNoAtomicData().GetName(), name, count, Utility::DuplicationNameObjectName::ParenthesesNumber)) count++;
                }
            }

            //----- ���O�ύX�E�R���|�[�l���g�ǉ�
            if (count == 0) {
                object.GetAtomicData().AddComponent<WindowType>(name);
                object.GetAtomicData().AccessName() = name;
            }
            else {
                object.GetAtomicData().AddComponent<WindowType>(Utility::DuplicationName(name, count, Utility::DuplicationNameObjectName::ParenthesesNumber));
                object.GetAtomicData().AccessName() = Utility::DuplicationName(name.c_str(), count, Utility::DuplicationNameObjectName::ParenthesesNumber);
            }

            //----- �ǉ�
            windows->push_back(object);
        }
    }
}
