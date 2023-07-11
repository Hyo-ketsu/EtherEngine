#ifndef I_COLLISIONHELPER_H
#define I_COLLISIONHELPER_H
#include <Base/CollisionBase.h>
#include <Base/GameObject.h>


//----- CollisionHelper �錾
namespace EtherEngine {
    class CollisionHelper {
    public:
        CollisionHelper(void) = delete;


        // �ՓˑΏۃQ�[���I�u�W�F�N�g�擾
        // @ Ret  : �ՓˑΏۃQ�[���I�u�W�F�N�g
        // @ Arg1 : �ՓˑΏۃQ�[���I�u�W�F�N�g���擾�������R���|�[�l���g
        static GameObject* const GetParentObject(const CollisionHitData& hitData);
        // �ՓˑΏۃQ�[���I�u�W�F�N�g�擾
        // @ Ret  : �ՓˑΏۃQ�[���I�u�W�F�N�g
        // @ Arg1 : �ՓˑΏۃQ�[���I�u�W�F�N�g���擾�������R���|�[�l���g
        static GameObject* const GetParentObject(const CollisionHitData* const hitData);
    };
}


#endif // !I_COLLISIONHELPER_H
