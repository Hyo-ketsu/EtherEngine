#ifndef I_EDITORDEBUG_H
#define I_EDITORDEBUG_H
#include <Base/Timer.h>
#include <EtherEngine/EditorWindowBase.h>


//----- EditorDebugWindow 宣言
namespace EtherEngine {
    // デバッグ用のウィンドウ
    class EditorDebugWindow : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;

        void Start(void) override;
        void Update(void) override;
        void Draw(void) override;

    private:
        Timer m_timer;  // 保持しているタイマー
    };
}


#endif // !I_EDITORDEBUG_H
