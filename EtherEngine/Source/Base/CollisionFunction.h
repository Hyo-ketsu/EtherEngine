#ifndef I_COLLISIONFUNCTION_H
#define I_COLLISIONFUNCTION_H
#include <Base/CollisionComponent.h>
#include <Base/CollisionHelper.h>
// @ MEMO : 重かったらベクトル化できるよう要検討？


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
