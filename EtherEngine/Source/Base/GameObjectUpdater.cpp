#include <Base/GameObjectUpdater.h>
#include <Base/CollisionBase.h>
#include <Base/CollisionFunction.h>


namespace EtherEngine {
    // ゲームオブジェクトに更新処理を行う
    void GameObjectUpdater::Update(void) {
        auto updates = GameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : updates) {
            if (it.IsEnable() == false) continue;

            it.GetAtomicData().Update();
        }
        GameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
    // ゲームオブジェクトに物理更新処理を行う
    void GameObjectUpdater::FixedUpdate(void) {
        //----- 物理処理
        {
            auto fixedUpdates = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : fixedUpdates) {
                if (it.IsEnable() == false) continue;

                it.GetAtomicData().FixedUpdate();
            }
            GameObjectStorage::Get()->DeleteGameObjectsDelete();
        }

        //----- ゲームオブジェクトの衝突情報削除
        {
            auto collisions = GameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : collisions) {
                if (it.IsEnable() == false) continue;

                it.GetAtomicData().SidelineCollisionData();
            }
        }

        //----- 衝突判定
        {
            auto gameObjects = GameObjectStorage::Get()->GetGameObjectAll();

            //----- 全てのゲームオブジェクトからCollisionComponentを取得、当たり判定処理を行う
            for (auto& thisGameObject : gameObjects) {  // 自身のゲームオブジェクト
                for (auto& subjectCollision : gameObjects) {    // 対象のゲームオブジェクト
                    //----- 変数宣言
                    decltype(auto) thisAtomic = thisGameObject.GetAtomicData();
                    decltype(auto) subjectAtomic = subjectCollision.GetAtomicData();

                    //----- 判定チェック(ガード節)
                    // どちらかが使用不可ならスルーする
                    if (thisAtomic.IsUnvalidObject() || subjectAtomic.IsUnvalidObject()) continue;
                    // 同オブジェクトならスルーする
                    if (thisAtomic.GetId() == subjectAtomic.GetId()) continue;

                    //----- コリジョンの取得
                    auto thisCollisions = thisAtomic.GetComponents<CollisionComponent>();
                    auto subjectCollisions = subjectAtomic.GetComponents<CollisionComponent>();

                    //----- 判定
                    AllCollisionCheck(thisCollisions, subjectCollisions);
                }
            }
        }

        //----- 各衝突処理実行
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


    // ゲームオブジェクトの描画処理を行う
    void GameObjectUpdater::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        auto draw = GameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : draw) {
            if (it.IsEnable() == false) continue;

            it.GetAtomicData().Draw(view, projection);
        }
        GameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
}
