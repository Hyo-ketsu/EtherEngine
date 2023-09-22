#ifndef I_EDITORLOGWINDOW_H
#define I_EDITORLOGWINDOW_H
#include <EtherEngine/EditorWindowBase.h>
#include <Base/LogSystem.h>


//----- EditorLogWindow 宣言
namespace EtherEngine {
    // メッセージを表示するクラス
    class EditorLogWindow : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;


        void StartWindow(void) override;
        void UpdateWindow(void) override;
        void DrawWindow(void) override;

    private:
        std::vector<LogWindowMessage> m_log;    // 保持しているログ
    };
}


#endif // !I_EDITORLOGWINDOW_H
