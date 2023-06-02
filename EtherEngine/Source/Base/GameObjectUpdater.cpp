#include <Base/GameObjectUpdater.h>


namespace EtherEngine {
    // ゲームオブジェクトに更新処理を行う
    void GameObjectUpdater::Update(void) {
        auto update = GameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : update) {
            if (it.GetEnable() == false) continue;

            
        }
    }
}
