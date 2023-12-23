#include <Base/CollisionBase.h>
#include <Base/NativeGameObject.h>


//----- CollisionHitData 定義
namespace EtherEngine {
    // コンストラクタ
    CollisionHitData::CollisionHitData(void* gameObject) 
        : m_hitTarget(static_cast<NativeGameObject*>(gameObject)){
    }


    // 衝突対象ゲッター
    void CollisionHitData::GetHitTarget(void** gameObject) const {
        *gameObject = m_hitTarget;
    }
}


//----- CollsionBase 定義
namespace EtherEngine {
    // コンストラクタ
    CollisionBase::CollisionBase(const CollisionShape& shape, const CollisionType& type, const Eigen::Vector3f& offset)
        : mc_shape(shape)
        , m_type(type) 
        , m_offset(offset)
        , m_id(/*CameraSystem<CollisionBase>::Get()->AddData(*this)*/) {
    }
}
