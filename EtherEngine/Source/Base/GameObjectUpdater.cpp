#include <Base/GameObjectUpdater.h>
#include <Base/CollisionBase.h>


namespace EtherEngine {
    // ゲームオブジェクトに更新処理を行う
    void GameObjectUpdater::Update(void) {
        auto update = GameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : update) {
            if (it.GetEnable() == false) continue;

            it.GetAtomicData().Update();
        }
        GameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
    // ゲームオブジェクトに物理更新処理を行う
    void GameObjectUpdater::FixedUpdate(void) {
        //----- 物理処理
        {
            auto fixedUpdate = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : fixedUpdate) {
                if (it.GetEnable() == false) continue;

                it.GetAtomicData().FixedUpdate();
            }
            GameObjectStorage::Get()->DeleteGameObjectsDelete();
        }

        //----- ゲームオブジェクトの衝突情報削除
        {
            auto collision = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : collision) {
                if (it.GetEnable() == false) continue;

                it.GetAtomicData().DeleteCollisionData();
            }
        }

        //----- 衝突判定
        {
            auto collision = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : collision) {
                if (it.GetEnable() == false) continue;

                it.GetAtomicData().GetComponents<CollisionComponent>();
            }
        }

        //----- 各衝突処理実行
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


    // ゲームオブジェクトの描画処理を行う
    void GameObjectUpdater::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        auto draw = GameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : draw) {
            if (it.GetEnable() == false) continue;

            it.GetAtomicData().Draw(view, projection);
        }
        GameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
}
