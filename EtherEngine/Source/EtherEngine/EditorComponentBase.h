#ifndef I_EDITORCOMPONENTBASE_H
#define I_EDITORCOMPONENTBASE_H


//----- EditorComponent宣言
namespace EtherEngine {
    class EditorComponentBase {
    public:
        // コンストラクタ
        // @ Arg1 : エディターオブジェクト
        EditorComponentBase(void* editorObject);
        // デストラクタ
        ~EditorComponentBase(void) {}


        // 親エディターオブジェクト取得
        // @ MEMO : ヘルパーをご利用ください
        // @ Arg1 : 親エディターオブジェクトへのポインタ
        void GetEditorObject(void** editerObject) const;


        // 更新処理
        void UpdateFunction(void);
        // 描画処理
        void DrawFunction(void);

    protected:
        virtual void Start(void) {}
        virtual void Update(void) {}
        virtual void Draw(void) {}

    private:
        void* m_eidtorObject;   // 保持してる
        bool m_isStart;         // 初期化関数を行っているか
    };
}


#endif // !I_EDITORCOMPONENTBASE_H
