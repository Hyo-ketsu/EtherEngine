#include <Base/GameObjectUpdater.h>


namespace EtherEngine {
    // ゲームオブジェクトに更新処理を行う
    void GameObjectUpdater::Update(void) {
        auto update = GameObjectStorage::Get()->GetEditorObjectAll();

        for (auto& it : update) {
            if (it.GetEnable() == false) continue;

            it.GetAtomicData().Update();
        }
        GameObjectStorage::Get()->DeleteGameObjectsDelete();
    }

    // ゲームオブジェクトの描画処理を行う
    void GameObjectUpdater::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        auto draw = GameObjectStorage::Get()->GetEditorObjectAll();

        for (auto& it : draw) {
            if (it.GetEnable() == false) continue;

            it.GetAtomicData().Draw(view, projection);
        }
        GameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
}
