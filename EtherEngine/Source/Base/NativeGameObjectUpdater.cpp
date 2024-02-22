#include <Base/NativeGameObjectUpdater.h>
#include <Base/CollisionBase.h>
#include <Base/CollisionFunction.h>


namespace EtherEngine {
    // ゲームオブジェクトに物理更新処理を行う
    void NativeGameObjectUpdater::FixedUpdate(void) {
        //----- ゲームオブジェクトの衝突情報削除
        for (auto& it : NativeGameObjectStorage::Get()->GetGameObjectAll()) {
            if (it.IsEnable() == false) continue;

            //----- 現在シーン設定
            SetCurrentSceneID(it.GetAtomicData().GetScene());

            //----- 更新
            it.GetAtomicData().SidelineCollisionData();
        }

        //----- 全てのゲームオブジェクトからCollisionComponentを取得、当たり判定処理を行う
        for (auto& thisGameObject : NativeGameObjectStorage::Get()->GetGameObjectAll()) {  // 自身のゲームオブジェクト
            for (auto& subjectCollision : NativeGameObjectStorage::Get()->GetGameObjectAll()) {    // 対象のゲームオブジェクト
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


    // ゲームオブジェクトの描画処理を行う
    void NativeGameObjectUpdater::Draw(const CameraData& camera) {
        auto draw = NativeGameObjectStorage::Get()->GetGameObjectAll();

        for (auto& it : draw) {
            if (it.IsEnable() == false) continue;

            //----- 現在シーン設定
            SetCurrentSceneID(it.GetAtomicData().GetScene());

            //----- 更新
            it.GetAtomicData().Draw(camera.GetView(), camera.GetProjection());
        }
        NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
    }
}
