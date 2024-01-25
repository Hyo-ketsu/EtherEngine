#include <Base/NativeGameObjectStorage.h>
#include <Base/NativeGameObjectUpdater.h>


//----- GameObejctStorage�錾
namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g���쐬����
    Handle<NativeGameObject> NativeGameObjectStorage::CreateGameObject(const Transform& transform, const std::string& name) {
        //----- �쐬�E�擾
        m_gameObjects.emplace_back(Handle<NativeGameObject>(NativeGameObject(transform, name)));
        auto&& handle = m_gameObjects.back().GetHandle();

        //----- ���g�̂�ǉ�
        handle.GetAtomicData().m_handle = handle;

        //----- �V�[���ւ̒ǉ�
        handle.GetAtomicData().SetScene(NativeGameObjectUpdater::Get()->GetCurrentSceneID()); 

        //----- �ԋp
        return handle;
    }
    // �Q�[���I�u�W�F�N�g���폜����
    bool NativeGameObjectStorage::DeleteGameObject(const Handle<NativeGameObject>& gameObject) {
        //----- �폜����n���h�����Ȃ߂�
        for (auto&& it : m_gameObjects) {
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
    // �Q�[���I�u�W�F�N�g���폜����
    void NativeGameObjectStorage::DeleteGameObject(const SceneIDType& deleteScene) {
        //----- �폜����ׂ��Q�[���I�u�W�F�N�g�𑖍�����
        for (int i = 0; i < m_gameObjects.size(); ) {
            auto&& gameObject = m_gameObjects[i];
            if (gameObject.GetData().GetScene() == deleteScene) {
                //----- �폜����
                gameObject.GetAtomicData().Delete();
                gameObject.GetAtomicData().DeleteObject();
            }
            else {
                //----- �폜���Ȃ��B���̃C���f�b�N�X�𒲍�
                i++;
            }
        }
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
                it = m_gameObjects.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
