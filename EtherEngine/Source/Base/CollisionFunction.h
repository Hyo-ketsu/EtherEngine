#ifndef I_COLLISIONFUNCTION_H
#define I_COLLISIONFUNCTION_H
#include <Base/ConceptUtility.h>
#include <Base/CollisionBase.h>
#include <Base/CollisionComponent.h>
#include <Base/CollisionHelper.h>
#include <Base/GameObject.h>
// @ MEMO : 重かったらベクトル化できるよう要検討？


//----- 当たり判定用構造体宣言
namespace EtherEngine {
    namespace CollisionFunction {
        // 衝突判定用関数に渡す用の構造体
        template <Concept::BaseOfConcept<CollisionBase> CollisionData>
        struct CollisionCheckData {
            // コンストラクタ
            // @ Arg1 : 自身のゲームオブジェクトへのポインタ
            // @ Arg2 : 座標
            // @ Arg3 : 情報
            CollisionCheckData(GameObject* gameObject, const Transform& transform, const CollisionData& data) : m_gameObject(gameObject), m_transform(transform), m_data(data) {}


            GameObject* m_gameObject;   // 自身のゲームオブジェクト
            Transform m_transform;      // 座標
            CollisionData m_data;       // 情報
        };
    }
}


// 当たり判定を行う関数
namespace EtherEngine {
    // 当たり判定を行う関数
    // @ Arg1 : 判定を行う当たり判定コンポーネント
    void AllCollisionCheck(std::vector<std::weak_ptr<CollisionComponent>> collisions);


    // 当たり判定をとる
    // @ Ret  : 衝突情報
    // @ Arg1 : 自身の当たり判定
    // @ Arg2 : 対象の当たり判定
    std::optional<CollisionHitData> CollisionCheck(std::shared_ptr<CollisionComponent> thisCollision, std::shared_ptr<CollisionComponent> subjectCollision);
}


#endif // !I_COLLISIONFUNCTION_H
