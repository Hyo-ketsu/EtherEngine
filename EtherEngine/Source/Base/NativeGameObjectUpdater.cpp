#include <Base/NativeGameObjectUpdater.h>
#include <Base/CollisionBase.h>
#include <Base/CollisionFunction.h>


namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g�ɕ����X�V�������s��
    void NativeGameObjectUpdater::FixedUpdate(void) {
        //----- �Q�[���I�u�W�F�N�g�̏Փˏ��폜
        for (auto& it : NativeGameObjectStorage::Get()->GetGameObjectAll()) {
            if (it.IsEnable() == false) continue;

            //----- ���݃V�[���ݒ�
            SetCurrentSceneID(it.GetAtomicData().GetScene());

            //----- �X�V
            it.GetAtomicData().SidelineCollisionData();
        }

        //----- �S�ẴQ�[���I�u�W�F�N�g����CollisionComponent���擾�A�����蔻�菈�����s��
        for (auto& thisGameObject : NativeGameObjectStorage::Get()->GetGameObjectAll()) {  // ���g�̃Q�[���I�u�W�F�N�g
            for (auto& subjectCollision : NativeGameObjectStorage::Get()->GetGameObjectAll()) {    // �Ώۂ̃Q�[���I�u�W�F�N�g
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
