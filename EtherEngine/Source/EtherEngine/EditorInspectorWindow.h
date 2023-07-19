#ifndef I_EDITORINSPECTORWINDOW_H
#define I_EDITORINSPECTORWINDOW_H
#include <EtherEngine/EditorComponentBase.h>


//----- EditorInspectorWindow 宣言
namespace EtherEngine {
    // ゲームオブジェクトの詳細を表示するクラス
    // @ MEMO : ひとまずGameObject専用とします
    class EditorInspectorWindow : public EditorComponentBase {
    public:
        void Update(void) override {}
    };
}


#endif // !I_EDITORINSPECTORWINDOW_H
