#ifndef I_EDITORDEBUG_H
#define I_EDITORDEBUG_H
#include <EtherEngine/EditorWindowBase.h>


//----- EditorDebugWindow �錾
namespace EtherEngine {
    // �f�o�b�O�p�̃E�B���h�E
    class EditorDebugWindow : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;

        
        void Draw(void) override;
    };
}


#endif // !I_EDITORDEBUG_H
