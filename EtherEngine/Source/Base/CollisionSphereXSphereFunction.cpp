#include <Base/CollisionSphereXSphereFunction.h>


namespace EtherEngine {
    namespace Collision {
        // 球と球の当たり判定をとる
        std::optional<CollisionHitData> SphereXSphereFunction(CollisionFunction::CollisionCheckData<CollisionSphere> thisSphere, CollisionFunction::CollisionCheckData<CollisionSphere> subjectCollision) {
            //----- 戻り値宣言
            std::optional<CollisionHitData> ret;

            //----- サイズ計算
            Eigen::Vector3f subjectToThis = subjectCollision.m_transform.AccessPostion() - thisSphere.m_transform.AccessPostion();

            //----- 距離計算
            Eigen::Vector3f distance = { powf(subjectToThis.x(), 2), powf(subjectToThis.y(), 2) ,powf(subjectToThis.z(), 2) };
            float radius = powf(thisSphere.mc_data.GetRadius(), 2) + powf(subjectCollision.mc_data.GetRadius(), 2);

            //----- 判定
            if (distance.x() + distance.y() + distance.z() <= radius) {
                //----- 衝突している。データを格納
                ret = CollisionHitData(subjectCollision.m_gameObject);
            }

            //----- 返却
            return ret;
        }
    }
}
