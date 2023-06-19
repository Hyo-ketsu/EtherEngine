#include <Base/GameObjectStorage.h>
#include <Base/HandleHelper.h>


//----- GameObejctStorage宣言
namespace EtherEngine {
    // ゲームオブジェクトを作成する
    BaseHandle<GameObject> GameObjectStorage::CreateGameObject(const Transform& transform) {
        auto handle = HandleHelper::AddItem<GameObject, HandleCountType::UnCount>(GameObject(transform));
        handle.GetAtomicData().m_handle = handle;
        m_gameObjects.push_back(handle);
        return handle;
    }


    // 全てのゲームオブジェクトを取得する
    std::vector<BaseHandle<GameObject>> GameObjectStorage::GetGameObjectAll(void) {
        return m_gameObjects;
    }

    void GameObjectStorage::GetFriend(int* hoge) {

    }
}
