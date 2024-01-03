#include <EngineLibrary/GameObjectStorage.h>
#include <EngineLibrary/GameObject.h>


//----- GameObjectStorage ��`
namespace EtherEngine {
    // �R���X�g���N�^
    GameObjectStorage::GameObjectStorage(void) 
        : m_gameObjects(gcnew System::Collections::Generic::List<GameObject^>(0)) 
        , m_updateVersion(false) {
    }


    // �Q�[���I�u�W�F�N�g��ǉ�����
    void GameObjectStorage::AddGameObject(GameObject^ gameObject) {
        m_gameObjects->Add(gameObject);

        m_updateVersion++;
    }
    // �Q�[���I�u�W�F�N�g���폜����
    void GameObjectStorage::DeleteGameObject(GameObject^ gameObject) {
        for (int i = 0; i < m_gameObjects->Count; i++) {
            if (gameObject->ReferenceEquals(gameObject, m_gameObjects[i])) {
                m_gameObjects->RemoveAt(i);
                return;
            }
        }

        m_updateVersion++;
    }
    // �Q�[���I�u�W�F�N�g���폜����
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
