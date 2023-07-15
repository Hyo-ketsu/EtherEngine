#include <Base/CollisionSphereXSphereFunction.h>


namespace EtherEngine {
    namespace Collision {
        // ���Ƌ��̓����蔻����Ƃ�
        std::optional<CollisionHitData> SphereXSphereFunction(CollisionFunction::CollisionCheckData<CollisionSphere> thisSphere, CollisionFunction::CollisionCheckData<CollisionSphere> subjectCollision) {
            //----- �߂�l�錾
            std::optional<CollisionHitData> ret;

            //----- �T�C�Y�v�Z
            Eigen::Vector3f subjectToThis = subjectCollision.m_transform.AccessPostion() - thisSphere.m_transform.AccessPostion();

            //----- �����v�Z
            Eigen::Vector3f distance = { powf(subjectToThis.x(), 2), powf(subjectToThis.y(), 2) ,powf(subjectToThis.z(), 2) };
            float radius = powf(thisSphere.mc_data.GetRadius(), 2) + powf(subjectCollision.mc_data.GetRadius(), 2);

            //----- ����
            if (distance.x() + distance.y() + distance.z() <= radius) {
                //----- �Փ˂��Ă���B�f�[�^���i�[
                ret = CollisionHitData(subjectCollision.m_gameObject);
            }

            //----- �ԋp
            return ret;
        }
    }
}
