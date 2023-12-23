#ifndef I_EDITORCOMPONENTBASE_H
#define I_EDITORCOMPONENTBASE_H
#include <Base/NativeBaseObject.h>


//----- EditorComponent宣言
namespace EtherEngine {
    class EditorComponentBase : public NativeBaseObject {
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
