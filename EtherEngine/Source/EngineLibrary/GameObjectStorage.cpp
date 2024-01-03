#include <EngineLibrary/GameObjectStorage.h>
#include <EngineLibrary/GameObject.h>


//----- GameObjectStorage 定義
namespace EtherEngine {
    // コンストラクタ
    GameObjectStorage::GameObjectStorage(void) 
        : m_gameObjects(gcnew System::Collections::Generic::List<GameObject^>(0)) 
        , m_updateVersion(false) {
    }


    // ゲームオブジェクトを追加する
    void GameObjectStorage::AddGameObject(GameObject^ gameObject) {
        m_gameObjects->Add(gameObject);

        m_updateVersion++;
    }
    // ゲームオブジェクトを削除する
    void GameObjectStorage::DeleteGameObject(GameObject^ gameObject) {
        for (int i = 0; i < m_gameObjects->Count; i++) {
            if (gameObject->ReferenceEquals(gameObject, m_gameObjects[i])) {
                m_gameObjects->RemoveAt(i);
                return;
            }
        }

        m_updateVersion++;
    }
    // ゲームオブジェクトを削除する
    void GameObjectStorage::DeleteGameObject(IDClass^ id) {
        for (int i = 0; i < m_gameObjects->Count; i++) {
            if (m_gameObjects[i]->ID == id) {
                m_gameObjects->RemoveAt(i);
                return;
            }
        }

        m_updateVersion++;
    }
}
