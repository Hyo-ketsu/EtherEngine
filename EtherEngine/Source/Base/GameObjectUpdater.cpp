#include <Base/GameObjectUpdater.h>


namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g�ɍX�V�������s��
    void GameObjectUpdater::Update(void) {
        auto update = GameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : update) {
            if (it.GetEnable() == false) continue;

            it.GetAtomicData().Update();
        }
    }

    // �Q�[���I�u�W�F�N�g�̕`�揈�����s��
    void GameObjectUpdater::Draw(void) {
        auto draw = GameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : draw) {
            if (it.GetEnable() == false) continue;

            it.GetAtomicData().Update();
        }
    }
}
