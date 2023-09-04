#ifndef I_EDITOREXPLORERWINDOW_H
#define I_EDITOREXPLORERWINDOW_H
#include <EtherEngine/EditorComponentBase.h>
#include <EtherEngine/EditorWindowBase.h>
#include <EtherEngine/ImGuiUtility.h>


//----- ExplorerWindow �錾
namespace EtherEngine {
    // �t�@�C����\������
    class ExplorerWindow : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;


        void Start(void) override;
        void Update(void) override;
        void DrawWindow(void) override;

        // �ŏ�ʃf�B���N�g���Z�b�^�[
        static void SetTopDirectory(const PathClass& in) { ms_rootDirectory = in; }

    private:
        static std::optional<PathClass> ms_rootDirectory;    // �ŏ�ʃf�B���N�g��
        static PathClass                ms_currentDirectory; // ���ݕ\���f�B���N�g��
        static int ms_selectNumber; // �I������Ă��郊�X�g�ԍ�
        static bool ms_isContentsSelect; // �R���e���c�E�B���h�E���I������Ă��邩
        ImVec2 m_windowSize;  // �K�w�\���E�B���h�E�̃T�C�Y
        ImGuiUtility::RenameableSelectable m_renameableSelectable;
    };
}


#endif // !I_EDITOREXPLORERWINDOW_H
