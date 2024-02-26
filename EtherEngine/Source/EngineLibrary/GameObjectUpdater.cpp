#include <EngineLibrary/GameObjectUpdater.h>
#include <Base/NativeGameObjectUpdater.h>
#include <EngineLibrary/GameObjectStorage.h>


//----- GameObjectUpdater ��`
namespace EtherEngine {
    // �R���X�g���N�^
    GameObjectUpdater::GameObjectUpdater(void) {
    }


    void GameObjectUpdater::Update(void) {
        //----- �����X�V
        NativeGameObjectUpdater::Get()->FixedUpdate();
        {
            for each (auto it in GameObjectStorage::Get->GameObjects) {
                if (it->IsUnvalidObject() == false) continue;

                it->FixedUpdate();
            }
            NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
        }

        //----- �X�V����
        {
            for each (auto it in GameObjectStorage::Get->GameObjects) {
                if (it->IsUnvalidObject() == false) continue;

                //----- �X�V
                it->Update();
            }
            NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();

            for each (auto it in GameObjectStorage::Get->GameObjects) {
                if (it->IsUnvalidObject() == false) continue;

                //----- �Փˏ���
                it->CollisionHit();
            }
            NativeGameObjectStorage::Get()->DeleteGameObjectsDelete();
        }
    }
    void GameObjectUpdater::Draw(const CameraData& cameraData) {

    }
}
