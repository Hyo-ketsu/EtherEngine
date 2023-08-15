#ifndef I_EDITORCOMPONENTBASE_H
#define I_EDITORCOMPONENTBASE_H
#include <Base/BaseObject.h>


//----- EditorComponent宣言
namespace EtherEngine {
    class EditorComponentBase : public BaseObject {
    public:
        // コンストラクタ
        // @ Arg1 : エディターオブジェクト
        EditorComponentBase(void* editorObject);
        // 純粋仮想デストラクタ
        virtual ~EditorComponentBase(void) = 0 {}


        // 親エディターオブジェクト取得
        // @ Memo : ヘルパーをご利用ください
        // @ Arg1 : 親エディターオブジェクトへのポインタ
        void GetEditorObject(void** editerObject) const;


        // 更新処理
        void UpdateFunction(void);
        // 描画処理
        void DrawFunction(void);
        // 削除時処理
        void DeleteFunction(void);


        // 外部出力
        Json Output(void) override { return Json(); }
        // 外部入力
        void Input(const Json& input) override {}
        // Inspector表示
        void ShowInspector(void) override {}

    protected:
        virtual void Start(void) {}
        virtual void Update(void) {}
        virtual void Draw(void) {}
        virtual void Delete(void) {}

    private:
        void* m_eidtorObject;   // 保持してる
        bool m_isStart;         // 初期化関数を行っているか
    };
}


#endif // !I_EDITORCOMPONENTBASE_H
