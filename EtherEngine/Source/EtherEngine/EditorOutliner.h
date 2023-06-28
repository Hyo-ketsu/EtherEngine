#ifndef I_EDITOROUTLINER_H
#define I_EDITOROUTLINER_H
#include <Base/Handle.h>
#include <DirectX/DirectX.h>
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorComponentBase.h>


//----- EditorOutliner 宣言
namespace EtherEngine {
    class EditorOutliner : public EditorComponentBase {
    public:
        // コンストラクタ
        // @ Arg1 : ゲームオブジェクトのポインタ
        // @ Arg2 : DirectX
        EditorOutliner(EditorObject* editorObject, const BaseHandle<DirectXRender>& directX);


        // 更新処理
        void Update(void) override;
        // 描画処理
        void Draw(void) override;
    };
}


#endif // !I_EDITOROUTLINER_H
