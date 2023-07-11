#include <Base/CollisionHelper.h>


//----- CollisionHelper ��`
namespace EtherEngine {
    // �ՓˑΏۃQ�[���I�u�W�F�N�g�擾
    // @ Ret  : �ՓˑΏۃQ�[���I�u�W�F�N�g
    // @ Arg1 : �ՓˑΏۃQ�[���I�u�W�F�N�g���擾�������R���|�[�l���g
    GameObject* const CollisionHelper::GetParentObject(const CollisionHitData& hitData) {
        void* ret = nullptr;
        hitData.GetHitTarget(&ret);
        return static_cast<GameObject*>(ret);
    }
    // �ՓˑΏۃQ�[���I�u�W�F�N�g�擾
    // @ Ret  : �ՓˑΏۃQ�[���I�u�W�F�N�g
    // @ Arg1 : �ՓˑΏۃQ�[���I�u�W�F�N�g���擾�������R���|�[�l���g
    GameObject* const CollisionHelper::GetParentObject(const CollisionHitData* const hitData) {
        return GetParentObject(*hitData);
    }
}
