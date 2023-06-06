#include <Base/GameObjectStorage.h>
#include <Base/HandleHelper.h>


//----- GameObejctStorage�錾
namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g��ǉ�����
    BaseHandle<GameObject> GameObjectStorage::AddGameObject(GameObject& gameObject) {
        auto handle = HandleHelper::AddItem<GameObject, HandleCountType::UnCount>(std::move(gameObject));
        m_gameObjects.push_back(handle);
        return handle;
    }


    // �S�ẴQ�[���I�u�W�F�N�g���擾����
    std::vector<BaseHandle<GameObject>> GameObjectStorage::GetGameObjectAll(void) {
        return m_gameObjects;
    }
}
