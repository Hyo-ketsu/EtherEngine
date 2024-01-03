#include <Base/NativeGameObjectUpdater.h>
#include <Base/CollisionBase.h>
#include <Base/CollisionFunction.h>


namespace EtherEngine {
    // ゲームオブジェクトに更新処理を行う
    void NativeGameObjectUpdater::Update(void) {
        auto updates = NativeGameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : updates) {
            if (it.IsEnable() == false) continue;

            it.GetAtomicData().Update();
        }
        NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
    // ゲームオブジェクトに物理更新処理を行う
    void NativeGameObjectUpdater::FixedUpdate(void) {
        //----- 物理処理
        {
            auto fixedUpdates = NativeGameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : fixedUpdates) {
                if (it.IsEnable() == false) continue;

                it.GetAtomicData().FixedUpdate();
            }
            NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
        }

        //----- ゲームオブジェクトの衝突情報削除
        {
            auto collisions = NativeGameObjectStorage::Get()->GetGameObjectAll();

            for (auto& it : collisions) {
                if (it.IsEnable() == false) continue;

                it.GetAtomicData().SidelineCollisionData();
            }
        }

        //----- 衝突判定
        {
            auto gameObjects = NativeGameObjectStorage::Get()->GetGameObjectAll();

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
                auto collisions = NativeGameObjectStorage::Get()->GetGameObjectAll();

                for (auto& it : collisions) {
                    if (it.IsEnable() == false) continue;

                    it.GetAtomicData().CollisionStart();
                }
                NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
            }
            {
                auto collisions = NativeGameObjectStorage::Get()->GetGameObjectAll();

                for (auto& it : collisions) {
                    if (it.IsEnable() == false) continue;

                    it.GetAtomicData().CollisionEnd();
                }
                NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
            }
            {
                auto collisions = NativeGameObjectStorage::Get()->GetGameObjectAll();

                for (auto& it : collisions) {
                    if (it.IsEnable() == false) continue;

                    it.GetAtomicData().CollisionHit();
                }
                NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
            }
        }
    }


    // ゲームオブジェクトの描画処理を行う
    void NativeGameObjectUpdater::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        auto draw = NativeGameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : draw) {
            if (it.IsEnable() == false) continue;

            it.GetAtomicData().Draw(view, projection);
        }
        NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
}
