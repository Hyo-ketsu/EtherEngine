#include <Base/GameObjectStorage.h>
#include <Base/HandleHelper.h>


//----- GameObejctStorage宣言
namespace EtherEngine {
    // ゲームオブジェクトを追加する
    BaseHandle<GameObject> GameObjectStorage::AddGameObject(GameObject& gameObject) {
        auto handle = HandleHelper::AddItem<GameObject, HandleCountType::UnCount>(std::move(gameObject));
        m_gameObjects.push_back(handle);
        return handle;
    }


    // 全てのゲームオブジェクトを取得する
    std::vector<BaseHandle<GameObject>> GameObjectStorage::GetGameObjectAll(void) {
        return m_gameObjects;
    }
}
