#ifndef I_EDITOREXPLORERWINDOW_H
#define I_EDITOREXPLORERWINDOW_H
#include <EtherEngine/EditorComponentBase.h>
#include <EtherEngine/EditorWindowBase.h>


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
        static void SetTopDirectory(const PathClass& in) { ms_topDirectory = in; }

    private:
        static std::optional<PathClass> ms_topDirectory;     // �ŏ�ʃf�B���N�g��
        static PathClass ms_currentDirectory; // ���ݕ\��Directory
        ImVec2 m_hierarchyView;  // �K�w�\���E�B���h�E�̃T�C�Y
    };
}


#endif // !I_EDITOREXPLORERWINDOW_H
