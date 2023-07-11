#include <Base/CollisionFunction.h>
#include <Base/ComponentHelper.h>


namespace EtherEngine {
    // �����蔻����s���֐�
    void AllCollisionCheck(std::vector<std::weak_ptr<CollisionComponent>> collisions) {
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
        // @ MEMO : �����r��
        return std::optional<CollisionHitData>();
    }
}
