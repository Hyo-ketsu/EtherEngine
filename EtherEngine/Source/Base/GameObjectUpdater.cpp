#include <Base/GameObjectUpdater.h>


namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g�ɍX�V�������s��
    void GameObjectUpdater::Update(void) {
        auto update = GameObjectStorage::Get()->GetEditorObjectAll();

        for (auto& it : update) {
            if (it.GetEnable() == false) continue;

            it.GetAtomicData().Update();
        }
        GameObjectStorage::Get()->DeleteGameObjectsDelete();
    }

    // �Q�[���I�u�W�F�N�g�̕`�揈�����s��
    void GameObjectUpdater::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        auto draw = GameObjectStorage::Get()->GetEditorObjectAll();

        for (auto& it : draw) {
            if (it.GetEnable() == false) continue;

            it.GetAtomicData().Draw(view, projection);
        }
        GameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
}
