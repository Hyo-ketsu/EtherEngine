#ifndef I_EDITORBUILDMENUWINDOW_H
#define I_EDITORBUILDMENUWINDOW_H
#include <EtherEngine/EditorWindowBase.h>


//----- BuildMenu �錾
namespace EtherEngine {
    class BuildMenu : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;

        // �X�V
        void Update(void) override;
        // �`��
        void Draw(void) override;
        // �E�B���h�E�`��
        void DrawWindow(void) override;
    };
}


#endif // !I_EDITORBUILDMENUWINDOW_H
