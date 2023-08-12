#include <EtherEngine/EditorExplorerWindow.h>
#include <Base/WindowsDefine.h>
#include <EtherEngine/FileOpener.h>


//----- �֐�����
namespace EtherEngine {
    // �p�X��S�ĕ\������
    // @ Arg1 : �t���O
    // @ Arg2 : �p�X
    // @ Arg3 : �I�����ꂽ�ꍇ�ɐݒ肷��J�����g�f�B���N�g��
    // @ Arg4 : ���[�g�f�B���N�g����
    void ShowPath(const ImGuiTreeNodeFlags& flag, const PathClass& path, PathClass* current, const bool isRoot) {
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
                ShowPath(flag, it, current, false);
            }
        }
        ImGui::TreePop();
    }
}


//----- ExplorerWindow ��`
namespace EtherEngine {
    void ExplorerWindow::Start(void) {
        //----- �����f�B���N�g���ݒ�
        // @ MEMO : ���ŃJ�����g�f�B���N�g��
        if (ms_rootDirectory.has_value() == false) {
            ms_rootDirectory = PathClass::GetCurDirectory();
            ms_currentDirectory = ms_rootDirectory.value();
        }
    }
    void ExplorerWindow::Update(void) {
    }


    void ExplorerWindow::DrawWindow(void) {
        if (ms_rootDirectory.has_value() == false) return;

        //----- �E�B���h�E�t���O�̐ݒ�
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;

        //----- �K�w�E�B���h�E�T�C�Y�ݒ�
        m_hierarchyView.x = ImGui::GetWindowSize().x / 2;
        m_hierarchyView.y = 65535;

        //----- �K�w�E�B���h�E�\��
        auto oldPath = ms_currentDirectory; // ���݂̃p�X���ς������
        ImGui::Begin(ImGuiDefine::Name::WINDOW_EXPLORER_HIERARCHY.c_str());
        {
            //----- �ϐ��錾
            ImGuiTreeNodeFlags flags = 
                ImGuiTreeNodeFlags_Selected;
                ImGuiTreeNodeFlags_OpenOnArrow;
                ImGuiTreeNodeFlags_OpenOnDoubleClick;

            //----- �����\��
            ShowPath(flags, ms_rootDirectory.value(), &ms_currentDirectory, true);
        }
        ImGui::End();
        //----- ���K�w���X�V����Ă�����R���e���c�I��ԍ������Z�b�g����
        if (oldPath.Get() != ms_currentDirectory.Get()) {
            ms_selectNumber = -1;
        }

        //----- �R���e���c(�f�B���N�g����)�\��
        ImGui::Begin(ImGuiDefine::Name::WINDOW_EXPLORER_CONTENTS.c_str());
        {
            //----- ���e���̕\��
            // @ MEMO : ���ň��
            if (ImGui::BeginListBox("ContentsList")) {
                int i = 0;
                for (auto&& it : ms_currentDirectory.GetLowerDirectory()) {
                    //----- �f�B���N�g���͕\�����Ȃ�
                    if (it.IsDirectory()) continue;

                    //----- ���X�g�v�f�\��
                    if (i == ms_selectNumber) {
                        //----- ���̔ԍ��̂��̂��I���ς݁B�g�p
                        if (ImGui::Selectable(it.GetFile().c_str(), true)) {
                            ImGui::SetItemDefaultFocus();
                            FileOpen(it);
                        }
                    }
                    else {
                        //----- �I������Ă��Ȃ��B�ʏ�\���E�I��
                        if (ImGui::Selectable(it.GetFile().c_str(), false)) {
                            ms_selectNumber = i;
                            ImGui::SetItemDefaultFocus();
                        }
                    }

                    i++;
                }

                ImGui::EndListBox();
            }
        }
        ImGui::End();
    }


    std::optional<PathClass> ExplorerWindow::ms_rootDirectory;  // �ŏ�ʃf�B���N�g��
    PathClass ExplorerWindow::ms_currentDirectory;              // ���ݕ\���f�B���N�g��
    int ExplorerWindow::ms_selectNumber = -1; // �I������Ă��郊�X�g�ԍ�
}
