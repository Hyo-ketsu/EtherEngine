#include <Base/NativeGameObjectStorage.h>


//----- GameObejctStorage�錾
namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g���쐬����
    Handle<NativeGameObject> NativeGameObjectStorage::CreateGameObject(const Transform& transform, const std::string& name) {
        auto handle = Handle<NativeGameObject>(NativeGameObject(transform, name));
        handle.GetAtomicData().m_handle = handle;
        // @ MEMO : �V�[���ւ̒ǉ��������蒼��
        //if (SceneLoader::Get()->GetCurrentSceneData().has_value()) { handle.GetAtomicData().SetScene(SceneLoader::Get()->GetCurrentSceneData().value()); }
        m_gameObjects.push_back(handle);
        return handle.GetRefHandle();
    }
    // �Q�[���I�u�W�F�N�g���폜����
    bool NativeGameObjectStorage::DeleteGameObject(const Handle<NativeGameObject>& gameObject) {
        //----- �폜����n���h�����Ȃ߂�
        for (auto&& it : m_gameObjects){
            if (it == gameObject) {
                //----- ���n���h���B�폜����
                it.GetAtomicData().Delete();
                it.GetAtomicData().DeleteObject();
                return true;
            }
        }

        //----- �����n���h�������݂��Ȃ�
        return false;
    }


    // �S�ẴQ�[���I�u�W�F�N�g���擾����
    std::vector<Handle<NativeGameObject>> NativeGameObjectStorage::GetGameObjectAll(void) const{
        return m_gameObjects;
    }


    // �폜�ς݂̃Q�[���I�u�W�F�N�g���폜����
    void NativeGameObjectStorage::DeleteGameObjectsDelete(void) {
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
