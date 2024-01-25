#include <Base/NativeGameObjectUpdater.h>
#include <Base/CollisionBase.h>
#include <Base/CollisionFunction.h>


namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g�ɍX�V�������s��
    void NativeGameObjectUpdater::Update(void) {
        auto updates = NativeGameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : updates) {
            if (it.IsEnable() == false) continue;

            //----- ���݃V�[���ݒ�
            SetCurrentSceneID(it.GetAtomicData().GetScene());

            //----- �X�V
            it.GetAtomicData().Update();
        }
        NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
    // �Q�[���I�u�W�F�N�g�ɕ����X�V�������s��
    void NativeGameObjectUpdater::FixedUpdate(void) {
        //----- ��������
        {
            auto fixedUpdates = NativeGameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : fixedUpdates) {
                if (it.IsEnable() == false) continue;

                //----- ���݃V�[���ݒ�
                SetCurrentSceneID(it.GetAtomicData().GetScene());

                //----- �X�V
                it.GetAtomicData().FixedUpdate();
            }
            NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
        }

        //----- �Q�[���I�u�W�F�N�g�̏Փˏ��폜
        {
            auto collisions = NativeGameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : collisions) {
                if (it.IsEnable() == false) continue;

                //----- ���݃V�[���ݒ�
                SetCurrentSceneID(it.GetAtomicData().GetScene());

                //----- �X�V
                it.GetAtomicData().SidelineCollisionData();
            }
        }

        //----- �Փ˔���
        {
            auto gameObjects = NativeGameObjectStorage::Get()->GetGameObjectAll();

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
                auto collisions = NativeGameObjectStorage::Get()->GetGameObjectAll();

                for (auto& it : collisions) {
                    if (it.IsEnable() == false) continue;

                    //----- ���݃V�[���ݒ�
                    SetCurrentSceneID(it.GetAtomicData().GetScene());

                    //----- �X�V
                    it.GetAtomicData().CollisionStart();
                }
                NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
            }
            {
                auto collisions = NativeGameObjectStorage::Get()->GetGameObjectAll();

                for (auto& it : collisions) {
                    if (it.IsEnable() == false) continue;

                    //----- ���݃V�[���ݒ�
                    SetCurrentSceneID(it.GetAtomicData().GetScene());

                    //----- �X�V
                    it.GetAtomicData().CollisionEnd();
                }
                NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
            }
            {
                auto collisions = NativeGameObjectStorage::Get()->GetGameObjectAll();

                for (auto& it : collisions) {
                    if (it.IsEnable() == false) continue;

                    //----- ���݃V�[���ݒ�
                    SetCurrentSceneID(it.GetAtomicData().GetScene());

                    //----- �X�V
                    it.GetAtomicData().CollisionHit();
                }
                NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
            }
        }
    }


    // �Q�[���I�u�W�F�N�g�̕`�揈�����s��
    void NativeGameObjectUpdater::Draw(const CameraData& camera) {
        auto draw = NativeGameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : draw) {
            if (it.IsEnable() == false) continue;

            //----- ���݃V�[���ݒ�
            SetCurrentSceneID(it.GetAtomicData().GetScene());

            //----- �X�V
            it.GetAtomicData().Draw(camera.GetView(), camera.GetProjection());
        }
        NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
}
