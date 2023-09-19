#ifndef I_EDITORBUILDMENUWINDOW_H
#define I_EDITORBUILDMENUWINDOW_H
#include <EtherEngine/EditorWindowBase.h>


//----- BuildMenu 宣言
namespace EtherEngine {
    class BuildMenu : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;

        // 更新
        void UpdateWindow(void) override;
        // 描画
        void Draw(void) override;
        // ウィンドウ描画
        void DrawWindow(void) override;
    };
}


#endif // !I_EDITORBUILDMENUWINDOW_H
