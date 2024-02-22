#ifndef I_GAMEDRAWCOMPONENT_H
#define I_GAMEDRAWCOMPONENT_H
#include <Base/NativeDrawComponent.h>
#include <EngineLibrary/WrapperDrawComponent.h>


//----- 描画コンポーネント
namespace EtherEngine {
    // 描画コンポーネント
    public ref class WrapperDrawComponent : public Component {
    public:
        // コンストラクタ
        // @ Memo : コンポーネントが生成できなければ例外を送出します
        // @ Arg1 : 親ゲームオブジェクト
        // @ Arg2 : 生成コンポーネント名
        WrapperDrawComponent(NativeGameObject* gameObject, const std::string& componentName);


        // 描画前更新処理
        void Update(void) override;
        // 描画後更新処理
        void LateUpdate(void) override;


        // 描画
        void Draw(void) override;
    };
}


#endif // !I_GAMEDRAWCOMPONENT_H
