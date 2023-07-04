#include <Base/CollisionBase.h>


//----- CollsionBase 定義
namespace EtherEngine {
    // コンストラクタ
    CollisionBase::CollisionBase(const CollisionShape& shape, const CollisionType& type)
        : mc_shape(shape)
        , m_type(type) {
    }
}
