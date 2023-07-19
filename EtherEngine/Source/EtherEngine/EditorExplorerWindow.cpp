#include <EtherEngine/EditorExplorerWindow.h>
#include <Base/WindowsDefine.h>


//----- �֐�����
namespace EtherEngine {
    // �p�X��S�ĕ\������
    // @ Arg1 : ���ڂ̃m�[�h��
    // @ Arg2 : �t���O
    // @ Arg3 : �p�X
    void ShowPath(int& number, const ImGuiTreeNodeFlags& flag, const std::filesystem::path& path) {
        //----- �g���q������i�f�B���N�g���ł͂Ȃ��j�t�@�C���͕\���͍s��Ȃ�
        if (path.has_extension()) return;

        for (auto&& it : std::filesystem::directory_iterator(path)) {
            //----- �ʏ�t�@�C���̕\���͂��Ȃ�
            if (it.is_regular_file()) continue;

            //----- ���݂̃p�X���擾
            // @ Memo : "C:/Hoge/Fuga/Piyo" �ł���� "Piyo"
            std::string thisPath = it.path().string();
            auto pos = thisPath.find_last_of(std::filesystem::path::preferred_separator);
            if (std::string::npos != pos) {
                thisPath.erase(0, pos + 1);
            }

            //----- �\��
            bool node_open = ImGui::TreeNodeEx(static_cast<void*>(&number), flag, thisPath.c_str());
            if (ImGui::BeginDragDropSource()) {
                ImGui::SetDragDropPayload("ExplorerHierarchyD&D", NULL, 0);
                ImGui::EndDragDropSource();
            }
            if (node_open) {
                ShowPath(number,flag, it);
                ImGui::TreePop();
            }

            number++;
        }
    }
}


//----- ExplorerWindow ��`
namespace EtherEngine {
    void ExplorerWindow::Start(void) {
        //----- �����f�B���N�g���ݒ�
        // @ MEMO : ���ŃJ�����g�f�B���N�g��
        if (ms_topDirectory.has_value() == false) {
            ms_topDirectory = std::filesystem::current_path();
            ms_currentDirectory = ms_topDirectory.value();
        }
    }
    void ExplorerWindow::Update(void) {

    }

    void ExplorerWindow::DrawWindow(void) {
        if (ms_topDirectory.has_value() == false) return;

        //----- �E�B���h�E�t���O�̐ݒ�
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;

        //----- �K�w�E�B���h�E�T�C�Y�ݒ�
        m_hierarchyView.x = ImGui::GetWindowSize().x / 2;
        m_hierarchyView.y = 65535;

        //----- �K�w�E�B���h�E�\��
        ImGui::BeginChild((ImGuiDefine::Name::WINDOW_EXPLORER + " HierarchyView").c_str(), m_hierarchyView, false, window_flags);
        {
            //----- ���X�g�\��
            if (ImGui::BeginListBox("HierarchyList")) {
                //----- �ϐ��錾
                int i = 0;
                ImGuiTreeNodeFlags flags = 
                    ImGuiTreeNodeFlags_OpenOnArrow | 
                    ImGuiTreeNodeFlags_OpenOnDoubleClick | 
                    ImGuiTreeNodeFlags_SpanAvailWidth | 
                    ImGuiTreeNodeFlags_Selected;

                //----- �����\��
                ShowPath(i, flags, ms_currentDirectory);

                ImGui::EndListBox();
            }
        }
        ImGui::EndChild();

        //----- �f�B���N�g�����\��
        //ImGui::BeginChild((ImGuiDefine::Name::WINDOW_EXPLORER + "FileView").c_str(), m_hierarchyView, false, window_flags);
        {

        }
    }


    std::optional<std::filesystem::path> ExplorerWindow::ms_topDirectory;   // �ŏ�ʃf�B���N�g��
    std::filesystem::path ExplorerWindow::ms_currentDirectory;              // ���ݕ\��Directory
}
