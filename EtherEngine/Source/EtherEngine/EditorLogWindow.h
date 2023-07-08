#ifndef I_EDITORLOGWINDOW_H
#define I_EDITORLOGWINDOW_H
#include <EtherEngine/EditorWindowBase.h>
#include <Base/LogSystem.h>


//----- EditorLogWindow �錾
namespace EtherEngine {
    // ���b�Z�[�W��\������N���X
    class EditorLogWindow : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;


        void Start(void) override;
        void Update(void) override;
        void DrawWindow(void) override;

    private:
        std::vector<LogWindowMessage> m_log;    // �ێ����Ă��郍�O
    };
}


#endif // !I_EDITORLOGWINDOW_H
