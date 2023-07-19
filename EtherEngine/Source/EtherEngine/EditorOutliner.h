#ifndef I_EDITOROUTLINER_H
#define I_EDITOROUTLINER_H
#include <Base/Handle.h>
#include <DirectX/DirectX.h>
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorWindowBase.h>


//----- EditorOutliner 宣言
namespace EtherEngine {
    class EditorOutliner : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;


        // 初期化処理
        void Start(void) override;
        // 更新処理
        void Update(void) override;
        // 描画処理
        void DrawWindow(void) override;

        // 現在選択されているゲームオブジェクトを渡す
        // @ Ret  : 現在選択されているゲームオブジェクト(無効ハンドルを返す場合があります)
        static BaseHandle<GameObject> GetSelectGameObject(void);

    private:
        static int ms_selectNumber; // 選択されている番号
    };
}


#endif // !I_EDITOROUTLINER_H
