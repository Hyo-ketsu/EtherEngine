#include <EngineLibrary/GameObject.h>
#include <Base/BaseUtility.h>
#include <Base/NativeGameObjectStorage.h>
#include <EngineLibrary/BaseObjectStorage.h>
#include <EngineLibrary/GameObjectStorage.h>
#include <EngineLibrary/DrawComponent.h>


#pragma managed
//----- GameObject ��`
namespace EtherEngine {
    // �R���X�g���N�^
    GameObject::GameObject(void)
        : m_components(gcnew System::Collections::Generic::List<Component^>(0)) 
        , m_deleteComponents(gcnew System::Collections::Generic::List<Component^>(0)) {
        m_handle = new std::remove_pointer_t<decltype(m_handle)>(NativeGameObjectStorage::Get()->CreateGameObject());
        GameObjectStorage::Get->AddGameObject(this);
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
    bool GameObject::IsSceneObject(Scene^ scene) {
        return NGameObject.GetData().GetScene() == scene->GetSceneID();
    }


    // �X�V�������s��
    void GameObject::Update(void) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->Update();
        }

        DeleteComponents();
    }
    // �X�V�㏈�����s��
    void GameObject::LateUpdate(void) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->LateUpdate();
        }

        DeleteComponents();
    }
    // �����X�V�������s��
    void GameObject::FixedUpdate(void) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->Update();
        }

        DeleteComponents();
    }
    // �`�揈�����s��
    void GameObject::Draw(UnmanageMaintainer<Eigen::Matrix4f> view, UnmanageMaintainer<Eigen::Matrix4f> projection) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            auto drawComponent = dynamic_cast<DrawComponent^>(it);

            if (drawComponent != nullptr) {
                drawComponent->SetView(view.GetUnmanageMaintainer());
                drawComponent->SetProjection(projection.GetUnmanageMaintainer());

                drawComponent->Draw();
            }
        }

        DeleteComponents();
    }
    // �폜���������s��
    void GameObject::Delete(void) {

        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->Delete();
        }

        DeleteComponents();
    }
    // �ՓˊJ�n�������s��
    void GameObject::CollisionStart(void) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->CollisionStart();
        }

        DeleteComponents();
    }
    // �ՓˏI���������s��
    void GameObject::CollisionEnd(void) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->CollisionEnd();
        }

        DeleteComponents();
    }
    // �Փˏ������s��
    void GameObject::CollisionHit(void) {
        for each (auto it in m_components) {
            if (it->IsUnvalidObject()) continue;

            it->CollisionHit();
        }

        DeleteComponents();
    }


    // �R���|�[�l���g��ǉ�����
    generic <typename ComponentType>
    ComponentType GameObject::AddComponent(void) {
        //----- �R���|�[�l���g��ǉ�����
        auto ret = safe_cast<ComponentType>(System::Activator::CreateInstance(ComponentType::typeid));
        ret->ParentGameObject = this;
        m_components->Add(ret);

        //----- �ǉ����������s
        ret->Create();

        //----- �ԋp
        return ret;
    }
    // �R���|�[�l���g���擾����
    generic <typename ComponentType>
    ComponentType GameObject::GetComponent(void) {
        //----- �R���|�[�l���g���Ȃ�
        for each (auto it in m_components) {
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
        for each (auto it in m_components) {
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
        for each (auto it in m_components) {
            if (it->GetType() == ComponentType::typeid) {
                m_deleteComponents->Add(it);
                return true;
            }
        }

        return false;
    }


    // �폜�ς݂̃R���|�[�l���g���폜����
    void GameObject::DeleteComponents(void) {
        for each (auto it in m_deleteComponents) {
            m_components->Remove(it);
        }

        m_deleteComponents->Clear();
    }
}
