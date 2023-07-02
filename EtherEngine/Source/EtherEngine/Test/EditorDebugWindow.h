#ifndef I_EDITORDEBUG_H
#define I_EDITORDEBUG_H
#include <Base/Timer.h>
#include <EtherEngine/EditorWindowBase.h>


//----- EditorDebugWindow �錾
namespace EtherEngine {
    // �f�o�b�O�p�̃E�B���h�E
    class EditorDebugWindow : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;

        void Start(void) override;
        void Update(void) override;
        void Draw(void) override;

    private:
        Timer m_timer;  // �ێ����Ă���^�C�}�[
    };
}


#endif // !I_EDITORDEBUG_H
