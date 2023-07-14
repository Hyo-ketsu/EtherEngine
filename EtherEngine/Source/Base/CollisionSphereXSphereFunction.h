#ifndef I_COLLISIONSPHEREXSPHEREFUNCTION_H
#define I_COLLISIONSPHEREXSPHEREFUNCTION_H
#include <Base/CollisionBase.h>
#include <Base/CollisionFunction.h>
#include <Base/CollisionSphere.h>


namespace EtherEngine {
    namespace Collision {
        // ‹…‚Æ‹…‚Ì“–‚½‚è”»’è‚ğ‚Æ‚é
        // @ Ret  : Õ“Ëî•ñ
        // @ Arg1 : ©g‚Ì“–‚½‚è”»’è
        // @ Arg2 : ‘ÎÛ‚Ì“–‚½‚è”»’è
        std::optional<CollisionHitData> SphereXSphereFunction(CollisionFunction::CollisionCheckData<CollisionSphere> thisSphere, CollisionFunction::CollisionCheckData<CollisionSphere> subjectCollision);
    }
}


#endif // !I_COLLISIONSPHEREXSPHEREFUNCTION_H
