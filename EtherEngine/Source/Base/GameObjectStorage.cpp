#include <Base/GameObjectStorage.h>
#include <Base/HandleHelper.h>


//----- GameObejctStorage�錾
namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g���쐬����
    BaseHandle<GameObject> GameObjectStorage::CreateEditorObject(const Transform& transform) {
        auto handle = Handle<GameObject>(GameObject(transform));
        handle.GetAtomicData().m_handle = handle;
        m_gameObjects.push_back(handle);
        return handle;
    }
    // �Q�[���I�u�W�F�N�g���폜����
    bool GameObjectStorage::DeleteGameObject(const BaseHandle<GameObject>& gameObject) {
        //----- �폜����n���h�����Ȃ߂�
        for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
            if (*it == gameObject) {
                //----- ���n���h���B�폜����
                it->GetAtomicData().Delete();
                it->GetAtomicData().DeleteObject();
                return true;
            }
        }

        //----- �����n���h�������݂��Ȃ�
        return false;
    }


    // �S�ẴQ�[���I�u�W�F�N�g���擾����
    std::vector<BaseHandle<GameObject>> GameObjectStorage::GetEditorObjectAll(void) {
        return m_gameObjects;
    }


    // �폜�ς݂̃Q�[���I�u�W�F�N�g���폜����
    void GameObjectStorage::DeleteGameObjectsDelete(void) {
        for (auto it = m_gameObjects.begin(); it != m_gameObjects.end();) {
            if (it->GetAtomicData().GetDelete()) {
                //----- �폜
                it->Delete();
                it = m_gameObjects.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
