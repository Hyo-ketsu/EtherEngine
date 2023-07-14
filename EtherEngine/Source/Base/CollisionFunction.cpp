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
        // @ MEMO : �R���|�[�l���g�������Ă��邩���肪�K�v�H
        //----- �Փ˔���
        for (auto&& thisCollision : collisions) {
            //----- �R���|�[�l���g���L����
            if (thisCollision.expired()) continue;

            for (auto&& subjectCollision : collisions) {
                //----- �R���|�[�l���g���L����
                if (subjectCollision.expired()) continue;

                //----- ���g�̓����蔻��Ƃ͓����蔻������Ȃ� 
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


    // �����蔻����Ƃ�
    std::optional<CollisionHitData> CollisionCheck(std::shared_ptr<CollisionComponent> thisCollision, std::shared_ptr<CollisionComponent> subjectCollision) {
        //----- �Q�[���I�u�W�F�N�g�̎擾
        auto thisGameObject = ComponentHelper::GetParentObject(*thisCollision);
        auto subjectGameObject = ComponentHelper::GetParentObject(*subjectCollision);

        //----- �� X ��
        if (thisCollision->GetCollisionShape() == CollisionShape::Sphere && thisCollision->GetCollisionShape() == CollisionShape::Sphere) {
            return Collision::SphereXSphereFunction(
                CollSphere(thisGameObject, thisGameObject->GetTransform(), *thisCollision->GetCollision<CollisionSphere>().lock()),
                CollSphere(subjectGameObject, subjectGameObject->GetTransform(), *subjectCollision->GetCollision<CollisionSphere>().lock()));
        }
        // @ MEMO : �����r��
    }
}
