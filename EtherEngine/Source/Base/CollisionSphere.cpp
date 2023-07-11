#include <Base/CollisionSphere.h>


//----- CollisionSphere 定義
namespace EtherEngine {
    // コンストラクタ
    CollisionSphere::CollisionSphere(const CollisionType& type, const float& radius, const Eigen::Vector3f& offset)
        : CollisionBase(CollisionShape::Sphere, type, offset) 
        , m_radius(radius) {
    }
}
