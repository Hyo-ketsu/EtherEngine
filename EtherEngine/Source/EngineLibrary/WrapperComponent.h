#ifndef I_GAMECOMPONENT_H
#define I_GAMECOMPONENT_H
#include <Base/NativeGameObject.h>
#include <EngineLibrary/Component.h>


//----- GameCompnent 宣言
namespace EtherEngine {
    // 
    class WrapperComponent : public ComponentBase {
    public:
        // コンストラクタ
        // @ Memo : コンポーネントが生成できなければ例外を送出します
        // @ Arg1 : 親ゲームオブジェクト
        // @ Arg2 : 生成コンポーネント名
        WrapperComponent(NativeGameObject* gameObject, const std::string& componentName);


        // 開始処理
        void Start(void);
        // 更新処理
        void Update(void);
        // 削除時処理
        void Delete(void);
        // 衝突開始処理
        void CollisionStart(void);
        // 衝突終了処理
        void CollisionEnd(void);
        // 衝突処理
        void CollisionHit(void);

    protected:
        msclr::gcroot<Component^> m_component;  // 保持しているコンポーネント
    };
}


#endif // !I_GAMECOMPONENT_H
