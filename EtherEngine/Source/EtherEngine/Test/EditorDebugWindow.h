#ifndef I_EDITORDEBUG_H
#define I_EDITORDEBUG_H
#include <Base/Timer.h>
#include <EtherEngine/EditorWindowBase.h>


//----- EditorDebugWindow �錾
namespace EtherEngine {
    // �f�o�b�O�p�̃E�B���h�E
    class EditorDebugWindow : public EditorWindowBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �e�G�f�B�^�[�I�u�W�F�N�g
        EditorDebugWindow(EditorObject* editorObject);


        void StartWindow(void) override;
        void UpdateWindow(void) override;
        void DrawWindow(void) override;

    private:
        Timer m_timer;  // �ێ����Ă���^�C�}�[
    };
}


#endif // !I_EDITORDEBUG_H
