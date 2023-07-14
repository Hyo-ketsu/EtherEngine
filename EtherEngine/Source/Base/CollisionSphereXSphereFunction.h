#ifndef I_COLLISIONSPHEREXSPHEREFUNCTION_H
#define I_COLLISIONSPHEREXSPHEREFUNCTION_H
#include <Base/CollisionBase.h>
#include <Base/CollisionFunction.h>
#include <Base/CollisionSphere.h>


namespace EtherEngine {
    namespace Collision {
        // ���Ƌ��̓����蔻����Ƃ�
        // @ Ret  : �Փˏ��
        // @ Arg1 : ���g�̓����蔻��
        // @ Arg2 : �Ώۂ̓����蔻��
        std::optional<CollisionHitData> SphereXSphereFunction(CollisionFunction::CollisionCheckData<CollisionSphere> thisSphere, CollisionFunction::CollisionCheckData<CollisionSphere> subjectCollision);
    }
}


#endif // !I_COLLISIONSPHEREXSPHEREFUNCTION_H
