#include <Base/GameObjectStorage.h>


//----- GameObejctStorage宣言
namespace EtherEngine {
    // ゲームオブジェクトを作成する
    Handle<GameObject> GameObjectStorage::CreateGameObject(const Transform& transform, const std::string& name) {
        auto handle = Handle<GameObject>(GameObject(transform, name));
        handle.GetAtomicData().m_handle = handle;
        // @ MEMO : シーンへの追加あたり作り直し
        //if (SceneLoader::Get()->GetCurrentSceneData().has_value()) { handle.GetAtomicData().SetScene(SceneLoader::Get()->GetCurrentSceneData().value()); }
        m_gameObjects.push_back(handle);
        return handle.GetRefHandle();
    }
    // ゲームオブジェクトを削除する
    bool GameObjectStorage::DeleteGameObject(const Handle<GameObject>& gameObject) {
        //----- 削除するハンドルをなめる
        for (auto&& it : m_gameObjects){
            if (it == gameObject) {
                //----- 同ハンドル。削除する
                it.GetAtomicData().Delete();
                it.GetAtomicData().DeleteObject();
                return true;
            }
        }

        //----- 同じハンドルが存在しない
        return false;
    }


    // 全てのゲームオブジェクトを取得する
    std::vector<Handle<GameObject>> GameObjectStorage::GetGameObjectAll(void) const{
        return m_gameObjects;
    }


    // 削除済みのゲームオブジェクトを削除する
    void GameObjectStorage::DeleteGameObjectsDelete(void) {
        for (auto it = m_gameObjects.begin(); it != m_gameObjects.end();) {
            if (it->GetAtomicData().GetDelete()) {
                //----- 削除
                it->Delete();
                it = m_gameObjects.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
