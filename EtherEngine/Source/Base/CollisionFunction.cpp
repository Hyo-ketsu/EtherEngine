#include <Base/CollisionFunction.h>
#include <Base/ComponentHelper.h>

#include <Base/CollisionSphere.h>
#include <Base/CollisionSphereXSphereFunction.h>


namespace {
    using CollSphere = EtherEngine::CollisionFunction::CollisionCheckData<EtherEngine::CollisionSphere>;
}


namespace EtherEngine {
    // �����蔻����s���֐�
    void AllCollisionCheck(std::vector<std::weak_ptr<CollisionComponent>> collisions) {
        //----- �Փ˔���
        for (auto&& thisCollision : collisions) {
            //----- ����`�F�b�N(�K�[�h��)
            // �R���|�[�l���g���w����Q�ƃ|�C���^�������Ȃ画�肵�Ȃ�
            if (thisCollision.expired()) continue;
            // �R���|�[�l���g���̂������Ă��Ȃ��Ȃ画�肵�Ȃ�
            if (thisCollision.lock()->IsUnvalidObject()) continue;

            for (auto&& subjectCollision : collisions) {
                //----- ����`�F�b�N(�K�[�h��)
                // �R���|�[�l���g���w����Q�ƃ|�C���^�������Ȃ画�肵�Ȃ�
                if (subjectCollision.expired()) continue;
                // �R���|�[�l���g���̂������Ă��Ȃ��Ȃ画�肵�Ȃ�
                if (subjectCollision.lock()->IsUnvalidObject()) continue;
                // ���g�̓����蔻��Ƃ͔��肵�Ȃ�
                if (thisCollision.lock()->GetId() == subjectCollision.lock()->GetId()) continue;

                //----- �����蔻����Ƃ�
                auto result = CollisionCheck(thisCollision.lock(), subjectCollision.lock());

                //----- �Փ˂��Ă�����ǉ�����
                if (result.has_value()) {
                    thisCollision.lock()->AccessCollisionHitData().push_back(result.value());
                }
            }
        }
    }   
    // �����蔻����s���֐�
    void AllCollisionCheck(std::vector<std::weak_ptr<CollisionComponent>> thisCollisions, std::vector<std::weak_ptr<CollisionComponent>> subjectCollisions) {
        //----- �Փ˔���
        for (auto&& thisCollision : thisCollisions) {
            //----- ����`�F�b�N(�K�[�h��)
            // �R���|�[�l���g���w����Q�ƃ|�C���^�������Ȃ画�肵�Ȃ�
            if (thisCollision.expired()) continue;
            // �R���|�[�l���g���̂������Ă��Ȃ��Ȃ画�肵�Ȃ�
            if (thisCollision.lock()->IsUnvalidObject()) continue;

            for (auto&& subjectCollision : subjectCollisions) {
                //----- ����`�F�b�N(�K�[�h��)
                // �R���|�[�l���g���w����Q�ƃ|�C���^�������Ȃ画�肵�Ȃ�
                if (subjectCollision.expired()) continue;
                // �R���|�[�l���g���̂������Ă��Ȃ��Ȃ画�肵�Ȃ�
                if (subjectCollision.lock()->IsUnvalidObject()) continue;
                // ���g�̓����蔻��Ƃ͔��肵�Ȃ�
                if (thisCollision.lock()->GetId() == subjectCollision.lock()->GetId()) continue;

                //----- �����蔻����Ƃ�
                auto result = CollisionCheck(thisCollision.lock(), subjectCollision.lock());

                //----- �Փ˂��Ă�����ǉ�����
                if (result.has_value()) {
                    ComponentHelper::GetParentObject(*thisCollision.lock())->AddCollisionData(result.value());
                }
            }
        }
    }


    // �����蔻����Ƃ�
    std::optional<CollisionHitData> CollisionCheck(std::shared_ptr<CollisionComponent> thisCollision, std::shared_ptr<CollisionComponent> subjectCollision) {
        //----- �Q�[���I�u�W�F�N�g�̎擾
        auto thisGameObject = ComponentHelper::GetParentObject(*thisCollision);
        auto subjectGameObject = ComponentHelper::GetParentObject(*subjectCollision);

        //----- �� x ��
        if (thisCollision->GetCollisionShape() == CollisionShape::Sphere && thisCollision->GetCollisionShape() == CollisionShape::Sphere) {
            return Collision::SphereXSphereFunction(
                CollSphere(thisGameObject, thisGameObject->GetTransform(), *thisCollision->GetCollision<CollisionSphere>()),
                CollSphere(subjectGameObject, subjectGameObject->GetTransform(), *subjectCollision->GetCollision<CollisionSphere>()));
        }
        // @ MEMO : �����r��
    }
}
