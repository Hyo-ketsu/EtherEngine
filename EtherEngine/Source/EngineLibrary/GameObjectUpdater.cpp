#include <EngineLibrary/GameObjectUpdater.h>
#include <Base/NativeGameObjectUpdater.h>
#include <EngineLibrary/GameObjectStorage.h>


//----- GameObjectUpdater 定義
namespace EtherEngine {
    void GameObjectUpdater::Update(void) {
        //----- 物理更新
        NativeGameObjectUpdater::Get()->FixedUpdate();
        {
            for each (auto it in GameObjectStorage::Get->GameObjects) {
                if (it->IsUnvalidObject() == false) continue;

                it->FixedUpdate();
            }
            NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
        }

        //----- 更新処理
        NativeGameObjectUpdater::Get()->Update();
        {
            for each (auto it in GameObjectStorage::Get->GameObjects) {
                if (it->IsUnvalidObject() == false) continue;

                //----- 更新
                it->Update();
            }
            NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();

            for each (auto it in GameObjectStorage::Get->GameObjects) {
                if (it->IsUnvalidObject() == false) continue;

                //----- 衝突処理
                it->CollisionHit();
            }
            NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
        }
    }
    void GameObjectUpdater::Draw(const CameraData& cameraData) {

    }
}
