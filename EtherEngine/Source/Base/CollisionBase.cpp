#include <Base/CollisionBase.h>


//----- CollsionBase ��`
namespace EtherEngine {
    // �R���X�g���N�^
    CollisionBase::CollisionBase(const CollisionShape& shape, const CollisionType& type)
        : mc_shape(shape)
        , m_type(type) {
    }
}
