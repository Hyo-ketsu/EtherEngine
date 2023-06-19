#include <Base/GameObjectStorage.h>
#include <Base/HandleHelper.h>


//----- GameObejctStorage�錾
namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g���쐬����
    BaseHandle<GameObject> GameObjectStorage::CreateGameObject(const Transform& transform) {
        auto handle = HandleHelper::AddItem<GameObject, HandleCountType::UnCount>(GameObject(transform));
        handle.GetAtomicData().m_handle = handle;
        m_gameObjects.push_back(handle);
        return handle;
    }


    // �S�ẴQ�[���I�u�W�F�N�g���擾����
    std::vector<BaseHandle<GameObject>> GameObjectStorage::GetGameObjectAll(void) {
        return m_gameObjects;
    }

    void GameObjectStorage::GetFriend(int* hoge) {

    }
}
