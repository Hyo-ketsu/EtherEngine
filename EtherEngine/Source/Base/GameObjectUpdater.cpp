#include <Base/GameObjectUpdater.h>
#include <Base/CollisionBase.h>


namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g�ɍX�V�������s��
    void GameObjectUpdater::Update(void) {
        auto update = GameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : update) {
            if (it.GetEnable() == false) continue;

            it.GetAtomicData().Update();
        }
        GameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
    // �Q�[���I�u�W�F�N�g�ɕ����X�V�������s��
    void GameObjectUpdater::FixedUpdate(void) {
        //----- ��������
        {
            auto fixedUpdate = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : fixedUpdate) {
                if (it.GetEnable() == false) continue;

                it.GetAtomicData().FixedUpdate();
            }
            GameObjectStorage::Get()->DeleteGameObjectsDelete();
        }

        //----- �Q�[���I�u�W�F�N�g�̏Փˏ��폜
        {
            auto collision = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : collision) {
                if (it.GetEnable() == false) continue;

                it.GetAtomicData().DeleteCollisionData();
            }
        }

        //----- �Փ˔���
        {
            auto collision = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : collision) {
                if (it.GetEnable() == false) continue;

                it.GetAtomicData().GetComponents<CollisionComponent>();
            }
        }

        //----- �e�Փˏ������s
        {
            auto collision = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : collision) {
                if (it.GetEnable() == false) continue;

                it.GetAtomicData().CollsionHit();
            }
            GameObjectStorage::Get()->DeleteGameObjectsDelete();
        }
        {
            auto collision = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : collision) {
                if (it.GetEnable() == false) continue;

                it.GetAtomicData().CollsionEnd();
            }
            GameObjectStorage::Get()->DeleteGameObjectsDelete();
        }
        {
            auto collision = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : collision) {
                if (it.GetEnable() == false) continue;

                it.GetAtomicData().CollsionHit();
            }
            GameObjectStorage::Get()->DeleteGameObjectsDelete();
        }
    }


    // �Q�[���I�u�W�F�N�g�̕`�揈�����s��
    void GameObjectUpdater::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        auto draw = GameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : draw) {
            if (it.GetEnable() == false) continue;

            it.GetAtomicData().Draw(view, projection);
        }
        GameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
}
