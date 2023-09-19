#ifndef I_EDITORINSPECTORWINDOW_H
#define I_EDITORINSPECTORWINDOW_H
#include <Base/EtherEngineUtility.h>
#include <Base/Handle.h>
#include <EtherEngine/EditorWindowBase.h>


//----- 表示用オブジェクト 定義
namespace EtherEngine {
    // EditorInspectorWindow用に表示するオブジェクト
    class EditorInspectorObject {
    public:
        // デフォルトコンストラクタ
        EditorInspectorObject(void);
        // コンストラクタ
        // @ Arg1 : 表示オブジェクト
        // @ Arg2 : 存在確認ラムダ(存在していれば true)
        EditorInspectorObject(IInspectorShow* showObject, const std::function<bool(void)>& deleteObject);
        

        // 表示オブジェクト取得
        // @ Ret  : 表示オブジェクト(既に削除されていればnullptr)
        IInspectorShow* GetShowObject(void) const;

    private:
        IInspectorShow* m_showObject;
        std::function<bool(void)> m_deleteObject;
    };
}


//----- EditorInspectorWindow 宣言
namespace EtherEngine {
    // ゲームオブジェクトの詳細を表示するクラス
    class EditorInspectorWindow : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;


        // 更新処理
        void UpdateWindow(void) override {}
        // 描画処理
        void DrawWindow(void) override;


        // @ MEMO : ひとまずポインタで実装。後でHandle的なので換装
        // 表示オブジェクトをセットする
        // @ Arg1 : 表示オブジェクト
        static void SetInspectorShow(const EditorInspectorObject& in) { ms_showObject = in; }

    private:
        static EditorInspectorObject ms_showObject;   // 表示オブジェクト
    };
}


#endif // !I_EDITORINSPECTORWINDOW_H
