#include <Base/CollisionSphere.h>


//----- CollisionSphere ��`
namespace EtherEngine {
    // �R���X�g���N�^
    CollisionSphere::CollisionSphere(const CollisionType& type, const float& radius, const Eigen::Vector3f& offset)
        : CollisionBase(CollisionShape::Sphere, type, offset) 
        , m_radius(radius) {
    }
}
