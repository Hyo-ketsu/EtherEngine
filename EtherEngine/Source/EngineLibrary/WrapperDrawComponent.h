#ifndef I_GAMEDRAWCOMPONENT_H
#define I_GAMEDRAWCOMPONENT_H
#include <Base/DrawComponentBase.h>
#include <EngineLibrary/WrapperComponent.h>
#include <EngineLibrary/WrapperDrawComponent.h>


//----- 描画コンポーネント
namespace EtherEngine {
    // 描画コンポーネント
    class ENGINELIBRARY_API WrapperDrawComponent : public WrapperComponent, public virtual DrawComponent {
    public:
        // コンストラクタ
        // @ Memo : コンポーネントが生成できなければ例外を送出します
        // @ Arg1 : 親ゲームオブジェクト
        // @ Arg2 : 生成コンポーネント名
        WrapperDrawComponent(NativeGameObject* gameObject, const std::string& componentName);


        // 開始処理
        void Start(void) override;
        // 更新処理
        void Update(void) override;
        // 削除時処理
        void Delete(void) override;
        // 衝突開始処理
        void CollisionStart(void) override;
        // 衝突終了処理
        void CollisionEnd(void) override;
        // 衝突処理
        void CollisionHit(void) override;


        // 描画
        void Draw(void) override;
    };
}


#endif // !I_GAMEDRAWCOMPONENT_H
