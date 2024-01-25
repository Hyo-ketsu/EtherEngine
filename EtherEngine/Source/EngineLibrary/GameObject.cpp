#include <EngineLibrary/GameObject.h>
#include <Base/BaseUtility.h>
#include <Base/NativeGameObjectStorage.h>
#include <EngineLibrary/BaseObjectStorage.h>
#include <EngineLibrary/GameObjectStorage.h>


#pragma managed
//----- GameObject ��`
namespace EtherEngine {
    // �R���X�g���N�^
    GameObject::GameObject(void) {
        m_handle = new std::remove_pointer_t<decltype(m_handle)>(NativeGameObjectStorage::Get()->CreateGameObject());
    }
    // �f�X�g���N�^
    GameObject::~GameObject(void) {
        this->!GameObject();
    }
    // �t�@�C�i���C�U
    GameObject::!GameObject(void) {
        BaseObjectStorage::Get->DeleteBaseObject(this);
        DELETE_NULL(m_handle);
    }


    // ���g���폜����
    void GameObject::Destroy(void) {   
        GameObjectStorage::Get->DeleteGameObject(this);
    }


    // ���͂����V�[���̃I�u�W�F�N�g�����肷��
    bool GameObject::IsSceneObject(Scene scene) {
        return NGameObject.GetData().GetScene() == scene.GetSceneID();
    }


    // �R���|�[�l���g��ǉ�����
    generic <typename ComponentType>
    ComponentType GameObject::AddComponent(void) {
        //----- �R���|�[�l���g��ǉ�����
        auto ret = safe_cast<ComponentType>(System::Activator::CreateInstance(ComponentType::typeid));
        ret->ParentGameObject = this;
        m_componentList->Add(ret);
        return ret;
    }
    // �R���|�[�l���g���擾����
    generic <typename ComponentType>
    ComponentType GameObject::GetComponent(void) {
        //----- �R���|�[�l���g���Ȃ�
        for each (auto it in m_componentList) {
            if (it->GetType() == ComponentType::typeid) {
                return safe_cast<ComponentType>(it);
            }
        }

        //----- �Ȃ��B
        return ComponentType();
    }
    // �R���|�[�l���g���擾����
    generic <typename ComponentType>
    System::Collections::Generic::List<ComponentType>^ GameObject::GetComponents(void) {
        //----- �ԋp�ϐ��錾
        System::Collections::Generic::List<ComponentType>^ ret = gcnew System::Collections::Generic::List<ComponentType>(0);

        //----- �R���|�[�l���g���Ȃ�
        for each (auto it in m_componentList) {
            if (it->GetType() == ComponentType::typeid) {
                ret->Add(safe_cast<ComponentType>(it));
            }
        }

        //----- �ԋp
        return ret;
    }
    // �R���|�[�l���g���폜����
    generic <typename ComponentType>
    bool GameObject::DeleteComponent(void) {
        //----- �R���|�[�l���g���Ȃ�
        for (int i = 0; i < m_componentList->Count; i++) {
            if (m_componentList[i]->GetType() == ComponentType::typeid) {
                m_componentList->RemoveAt(i);
            }
        }

        return false;
    }
}
