#include <Base/GameObjectUpdater.h>
#include <Base/CollisionBase.h>
#include <Base/CollisionFunction.h>


namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g�ɍX�V�������s��
    void GameObjectUpdater::Update(void) {
        auto updates = GameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : updates) {
            if (it.IsEnable() == false) continue;

            it.GetAtomicData().Update();
        }
        GameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
    // �Q�[���I�u�W�F�N�g�ɕ����X�V�������s��
    void GameObjectUpdater::FixedUpdate(void) {
        //----- ��������
        {
            auto fixedUpdates = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : fixedUpdates) {
                if (it.IsEnable() == false) continue;

                it.GetAtomicData().FixedUpdate();
            }
            GameObjectStorage::Get()->DeleteGameObjectsDelete();
        }

        //----- �Q�[���I�u�W�F�N�g�̏Փˏ��폜
        {
            auto collisions = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : collisions) {
                if (it.IsEnable() == false) continue;

                it.GetAtomicData().SidelineCollisionData();
            }
        }

        //----- �Փ˔���
        {
            auto gameObjects = GameObjectStorage::Get()->GetGameObjectAll();

            //----- �S�ẴQ�[���I�u�W�F�N�g����CollisionComponent���擾�A�����蔻�菈�����s��
            for (auto& thisGameObject : gameObjects) {  // ���g�̃Q�[���I�u�W�F�N�g
                for (auto& subjectCollision : gameObjects) {    // �Ώۂ̃Q�[���I�u�W�F�N�g
                    //----- �ϐ��錾
                    decltype(auto) thisAtomic = thisGameObject.GetAtomicData();
                    decltype(auto) subjectAtomic = subjectCollision.GetAtomicData();

                    //----- ����`�F�b�N(�K�[�h��)
                    // �ǂ��炩���g�p�s�Ȃ�X���[����
                    if (thisAtomic.IsUnvalidObject() || subjectAtomic.IsUnvalidObject()) continue;
                    // ���I�u�W�F�N�g�Ȃ�X���[����
                    if (thisAtomic.GetId() == subjectAtomic.GetId()) continue;

                    //----- �R���W�����̎擾
                    auto thisCollisions = thisAtomic.GetComponents<CollisionComponent>();
                    auto subjectCollisions = subjectAtomic.GetComponents<CollisionComponent>();

                    //----- ����
                    AllCollisionCheck(thisCollisions, subjectCollisions);
                }
            }
        }

        //----- �e�Փˏ������s
        {
            {
                auto collisions = GameObjectStorage::Get()->GetGameObjectAll();

                for (auto& it : collisions) {
                    if (it.IsEnable() == false) continue;

                    it.GetAtomicData().CollisionHit();
                }
                GameObjectStorage::Get()->DeleteGameObjectsDelete();
            }
            {
                auto collisions = GameObjectStorage::Get()->GetGameObjectAll();

                for (auto& it : collisions) {
                    if (it.IsEnable() == false) continue;

                    it.GetAtomicData().CollisionEnd();
                }
                GameObjectStorage::Get()->DeleteGameObjectsDelete();
            }
            {
                auto collisions = GameObjectStorage::Get()->GetGameObjectAll();

                for (auto& it : collisions) {
                    if (it.IsEnable() == false) continue;

                    it.GetAtomicData().CollisionHit();
                }
                GameObjectStorage::Get()->DeleteGameObjectsDelete();
            }
        }
    }


    // �Q�[���I�u�W�F�N�g�̕`�揈�����s��
    void GameObjectUpdater::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        auto draw = GameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : draw) {
            if (it.IsEnable() == false) continue;

            it.GetAtomicData().Draw(view, projection);
        }
        GameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
}
