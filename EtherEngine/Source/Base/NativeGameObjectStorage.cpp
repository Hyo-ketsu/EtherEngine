#include <Base/NativeGameObjectStorage.h>


//----- GameObejctStorage宣言
namespace EtherEngine {
    // ゲームオブジェクトを作成する
    Handle<NativeGameObject> NativeGameObjectStorage::CreateGameObject(const Transform& transform, const std::string& name) {
        //----- 作成・取得
        m_gameObjects.emplace_back(Handle<NativeGameObject>(NativeGameObject(transform, name)));
        auto&& handle = m_gameObjects.back().GetHandle();

        //----- 自身のを追加
        handle.GetAtomicData().m_handle = handle;

        //----- シーンへの追加
        // @ MEMO : シーンへの追加あたり作り直し
        //if (SceneLoader::Get()->GetCurrentSceneData().has_value()) { handle.GetAtomicData().SetScene(SceneLoader::Get()->GetCurrentSceneData().value()); }

        //----- 返却
        return handle;
    }
    // ゲームオブジェクトを削除する
    bool NativeGameObjectStorage::DeleteGameObject(const Handle<NativeGameObject>& gameObject) {
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
    std::vector<Handle<NativeGameObject>> NativeGameObjectStorage::GetGameObjectAll(void) const{
        return m_gameObjects;
    }


    // 削除済みのゲームオブジェクトを削除する
    void NativeGameObjectStorage::DeleteGameObjectsDelete(void) {
        for (auto it = m_gameObjects.begin(); it != m_gameObjects.end();) {
            if (it->GetAtomicData().GetDelete()) {
                //----- 削除
                it = m_gameObjects.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
