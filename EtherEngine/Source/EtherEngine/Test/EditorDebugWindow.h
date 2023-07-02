#ifndef I_EDITORDEBUG_H
#define I_EDITORDEBUG_H
#include <EtherEngine/EditorWindowBase.h>


//----- EditorDebugWindow 宣言
namespace EtherEngine {
    // デバッグ用のウィンドウ
    class EditorDebugWindow : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;

        
        void Draw(void) override;
    };
}


#endif // !I_EDITORDEBUG_H
