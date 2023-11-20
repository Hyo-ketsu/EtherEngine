#include <EtherEngine/EditorExplorerWindow.h>
#include <Base/WindowsDefine.h>
#include <Base/EtherEngineUtility.h>
#include <EtherEngine/FileOpener.h>
#include <EtherEngine/FileCreater.h>
#include <EtherEngine/FileDeleter.h>


//----- �֐�����
namespace EtherEngine {
    // �p�X��S�ĕ\������
    // @ Arg1 : �t���O
    // @ Arg2 : �p�X
    // @ Arg3 : �I�����ꂽ�ꍇ�ɐݒ肷��J�����g�f�B���N�g��
    // @ Arg4 : ���[�g�f�B���N�g����
    // @ Arg5 : �I���t���O
    void ShowPath(const ImGuiTreeNodeFlags& flag, const PathClass& path, PathClass* current, const bool isRoot, bool* isContentsFrag) {
        //----- �g���q������i�f�B���N�g���ł͂Ȃ��j�t�@�C���͕\���͍s��Ȃ�
        if (path.HasExtension()) return;

        //----- �\�������_��`
        auto showPath = [&](const PathClass& showPath) -> bool {
            //----- �ʏ�t�@�C��(=�g���q�����݂���)�̕\���͂��Ȃ�
            if (showPath.HasExtension()) return false;

            //----- ���݂̃p�X���擾
            // @ Memo : "Hoge/Fuga" �ł���� "Hoge/Fuga"
            std::string thisPath = showPath.GetFile();

            //----- �\��
            bool ret = ImGui::TreeNodeEx(thisPath.c_str(), flag);

            //----- �I�����ꂽ�f�B���N�g�����J�����g�f�B���N�g���Ƃ��Đݒ肷��
            if (ImGui::IsItemClicked()) {
                *current = showPath;
                *isContentsFrag = false;
            }

            //----- D&D�\��
            if (ImGui::BeginDragDropSource()) {
                ImGui::SetDragDropPayload("ExplorerHierarchyD&D", NULL, 0);
                ImGui::EndDragDropSource();
            }

            //----- �ԋp
            return ret;
        };

        //----- ���g�����[�g�f�B���N�g���ł���Ε\������
        if (isRoot) {
            if (showPath(path) == false) return;
        }

        //----- �m�[�h�\��
        for (auto&& it : path.GetLowerDirectory()) {
            //----- �J����Ă���m�[�h�̕\��(�ċA)
            if (showPath(it)) {
                ShowPath(flag, it, current, false, isContentsFrag);
            }
        }
        ImGui::TreePop();
    }
}


//----- ExplorerWindow ��`
namespace EtherEngine {
    void ExplorerWindow::StartWindow(void) {
        //----- �����f�B���N�g���ݒ�
        // @ MEMO : ���ŃJ�����g�f�B���N�g��
        if (ms_rootDirectory.has_value() == false) {
            ms_rootDirectory = PathClass::GetCurDirectory();
            ms_currentDirectory = ms_rootDirectory.value();
        }
    }
    void ExplorerWindow::UpdateWindow(void) {
    }


    void ExplorerWindow::DrawWindow(void) {
        if (ms_rootDirectory.has_value() == false) return;

        //----- �E�B���h�E�t���O�̐ݒ�
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;

        //----- �E�B���h�E�T�C�Y�ݒ�
        m_windowSize.x = ImGui::GetWindowSize().x / 3;
        m_windowSize.y = 0;

        //----- �K�w�E�B���h�E�\��
        auto oldPath = ms_currentDirectory; // ���݂̃p�X���ς������
        ImGui::BeginChild(ImGuiDefine::Name::WINDOW_EXPLORER_HIERARCHY.c_str(), m_windowSize, true, window_flags);
        {
            //----- �E�N���b�N���j���[�\��
            if (ImGui::IsWindowFocused() && ImGui::IsMouseReleased(1)) {
                ImGui::OpenPopup("Explorer Hierarchy Popup");
            }

            //----- �ϐ��錾
            ImGuiTreeNodeFlags flags =
                ImGuiTreeNodeFlags_Selected;
            ImGuiTreeNodeFlags_OpenOnArrow;
            ImGuiTreeNodeFlags_OpenOnDoubleClick;

            //----- �����\��
            ShowPath(flags, ms_rootDirectory.value(), &ms_currentDirectory, true, &ms_isContentsSelect);

            ImGui::EndChild();
        }

        //----- �K�w�E�B���h�E�E�N���b�N���j���[�\��
        if (ImGui::BeginPopupContextItem("Explorer Hierarchy Popup")) {
            //----- �I�u�W�F�N�g����
            if (ImGui::MenuItem("Create")) {
                FileCreate("NewDirectory", "", ms_currentDirectory, Utility::DuplicationNameObjectName::ParenthesesNumber, "", true);
            }
            if (ImGui::MenuItem("Delete")) {
            }
            //----- ���j���[�\���I��
            ImGui::EndPopup();
        }

        //----- ���K�w���X�V����Ă�����R���e���c�I��ԍ������Z�b�g����
        if (oldPath.Get() != ms_currentDirectory.Get()) {
            ms_selectNumber = -1;
        }

        //----- �R���e���c(�f�B���N�g����)�\��

        //----- �E�B���h�E�T�C�Y�ݒ�
        m_windowSize.x = ImGui::GetWindowSize().x / 3 * 2;
        m_windowSize.y = 0;

        //----- ���e���̕\��
        // @ MEMO : ���ň��
        ImGui::SameLine();
        ImGui::BeginChild(ImGuiDefine::Name::WINDOW_EXPLORER_CONTENTS.c_str(), m_windowSize, true, window_flags);
        {
            //----- �E�N���b�N���j���[�\��
            if (ImGui::IsWindowFocused() && ImGui::IsMouseReleased(1)) {
                ImGui::OpenPopup("Explorer Contents Popup");
            }

            //----- �v�f�\��
            int i = 0;
            std::vector<std::pair<PathClass, std::string>> createFile;  // �쐬�t�@�C���ꗗ
            std::vector<PathClass> deleteFile;  // �폜�t�@�C���ꗗ
            for (auto&& it : ms_currentDirectory.GetLowerDirectory()) {
                //----- �f�B���N�g���͕\�����Ȃ�
                if (it.IsDirectory()) continue;

                //----- ���X�g�v�f�\��
                ImGuiUtility::RenameableSelectableMessage mes;
                do {
                    if (i == ms_selectNumber) {
                        //----- ���̔ԍ��̂��̂��I���ς݁B�g�p
                        mes = m_renameableSelectable.Show(it.GetFile(), i, true);

                        //----- �I����
                        if (mes == decltype(mes)::SelectYes) {
                            ImGui::SetItemDefaultFocus();
                            FileOpen(it);
                            break;
                        }
                    }
                    else {
                        //----- �I������Ă��Ȃ��B�ʏ�\���E�I��
                        mes = m_renameableSelectable.Show(it.GetFile(), i, false);

                        //----- �I����
                        if (mes == decltype(mes)::SelectYes) {
                            ms_selectNumber = i;
                            ms_isContentsSelect = true;
                            ImGui::SetItemDefaultFocus();
                            break;
                        }
                    }
                    //----- ���l�[�����s��ꂽ��
                    if (mes == decltype(mes)::RenameDecision) {
                        createFile.push_back(std::make_pair<PathClass,std::string>(it.GetDirectory() / m_renameableSelectable.GetRename(), RoadFileAll(it)));
                        deleteFile.push_back(it);
                    }
                } while (false);

                i++;
            }

            //----- �t�@�C���폜�E�t�@�C���쐬
            for (auto&& it : deleteFile) {
                it.Delete_File(true);
            }
            for (auto&& it : createFile) {
                it.first.Create_File(it.second);
            }

            ImGui::EndChild();
        }


        //----- �R���e���c�E�B���h�E�E�N���b�N���j���[�\��
        if (ImGui::BeginPopupContextItem("Explorer Contents Popup")) {
            //----- �I�u�W�F�N�g����
            if (ImGui::BeginMenu("Create")) {
                //----- �e�t�@�C������
                if (ImGui::MenuItem("Scene")) {
                    FileCreate("NewScene", FileDefine::Extended::SCENE, ms_currentDirectory, Utility::DuplicationNameObjectName::ParenthesesNumber);
                }
                if (ImGui::MenuItem("Script")) {
                    FileCreate("Script", FileDefine::Extended::SCRIPT, ms_currentDirectory, Utility::DuplicationNameObjectName::ParenthesesNumber, FileDefine::SCRIPT_FILE_STRING);
                }

                ImGui::EndMenu();
            }
            //----- �I�u�W�F�N�g�폜
            if (ImGui::MenuItem("Delete")) {
                //----- �I��ԍ��̃t�@�C���폜
                if (ms_currentDirectory.GetLowerDirectory().size() > ms_selectNumber) {
                    FileDelete(ms_currentDirectory.GetLowerDirectory()[ms_selectNumber], true);
                }
            }

            //----- ���j���[�\���I��
            ImGui::EndPopup();
        }
    }


    std::optional<PathClass> ExplorerWindow::ms_rootDirectory;  // �ŏ�ʃf�B���N�g��
    PathClass ExplorerWindow::ms_currentDirectory;              // ���ݕ\���f�B���N�g��
    int ExplorerWindow::ms_selectNumber = -1; // �I������Ă��郊�X�g�ԍ�
    bool ExplorerWindow::ms_isContentsSelect = true; // �R���e���c�E�B���h�E���I������Ă��邩
}
