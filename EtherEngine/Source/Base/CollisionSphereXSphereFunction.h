#ifndef I_COLLISIONSPHEREXSPHEREFUNCTION_H
#define I_COLLISIONSPHEREXSPHEREFUNCTION_H
#include <Base/CollisionBase.h>
#include <Base/CollisionFunction.h>
#include <Base/CollisionSphere.h>


namespace EtherEngine {
    namespace Collision {
        // 球と球の当たり判定をとる
        // @ Ret  : 衝突情報
        // @ Arg1 : 自身の当たり判定
        // @ Arg2 : 対象の当たり判定
        std::optional<CollisionHitData> SphereXSphereFunction(CollisionFunction::CollisionCheckData<CollisionSphere> thisSphere, CollisionFunction::CollisionCheckData<CollisionSphere> subjectCollision);
    }
}


#endif // !I_COLLISIONSPHEREXSPHEREFUNCTION_H
