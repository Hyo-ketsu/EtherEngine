#include <Base/GameObjectUpdater.h>


namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g�ɍX�V�������s��
    void GameObjectUpdater::Update(void) {
        auto update = GameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : update) {
            if (it.GetEnable() == false) continue;

            
        }
    }
}
