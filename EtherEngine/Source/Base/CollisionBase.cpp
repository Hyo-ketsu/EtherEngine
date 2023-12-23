#include <Base/CollisionBase.h>
#include <Base/NativeGameObject.h>


//----- CollisionHitData ��`
namespace EtherEngine {
    // �R���X�g���N�^
    CollisionHitData::CollisionHitData(void* gameObject) 
        : m_hitTarget(static_cast<NativeGameObject*>(gameObject)){
    }


    // �ՓˑΏۃQ�b�^�[
    void CollisionHitData::GetHitTarget(void** gameObject) const {
        *gameObject = m_hitTarget;
    }
}


//----- CollsionBase ��`
namespace EtherEngine {
    // �R���X�g���N�^
    CollisionBase::CollisionBase(const CollisionShape& shape, const CollisionType& type, const Eigen::Vector3f& offset)
        : mc_shape(shape)
        , m_type(type) 
        , m_offset(offset)
        , m_id(/*CameraSystem<CollisionBase>::Get()->AddData(*this)*/) {
    }
}
