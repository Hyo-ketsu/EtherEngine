#ifndef I_COLLISIONCOMPONENT_H
#define I_COLLISIONCOMPONENT_H
#include <Base/ComponentBase.h>
#include <Base/CollisionBase.h>
#include <Base/ConceptUtility.h>


//----- CollisionComponent 宣言
namespace EtherEngine {
    // 当たり判定のコンポーネント
    class CollisionComponent : public ComponentBase {
    public:
        // コンストラクタ
        // @ Temp : コリジョンのタイプ
        // @ Arg1 : ゲームオブジェクトのポインタ
        // @ Arg2 : コリジョン
        template <Concept::SameSubClass<CollisionBase> Type>
        CollisionComponent(void* gameObject, Type&& collision);

    
        // コリジョンゲッター
        template <Concept::SameSubClass<CollisionBase> Type>
        std::weak_ptr<Type> GetCollision(void) { return std::weak_ptr<Type>(m_collision); }

        // コリジョン形状ゲッター
        CollisionShape GetCollisionShape(void) const { return m_collision->GetShape(); }
        // コリジョン種類
        CollisionType GetCollisionType(void) const { return m_collision->GetType(); }

    private:
        std::shared_ptr<CollisionBase> m_collision; // コリジョン
    };
}


//----- CollisionComponent 定義
namespace EtherEngine {
    // コンストラクタ
    template <Concept::SameSubClass<CollisionBase> Type>
    CollisionComponent::CollisionComponent(void* gameObject, Type&& collision) 
        : ComponentBase(gameObject) 
        , m_collision(std::make_shared<CollisionBase>(collision)) {
    }
}
#endif // !I_COLLISIONCOMPONENT_H
