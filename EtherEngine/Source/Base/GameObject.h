#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/BaseObject.h>
#include <Base/ComponentBase.h>
#include <Base/ComponentHelper.h>
#include <Base/CollisionComponent.h>
#include <Base/ConceptUtility.h>
#include <Base/DrawComponent.h> 
#include <Base/HandleHelper.h>
#include <Base/Handle.h>
#include <Base/Transform.h>
#include <Base/Scene.h>


//----- GameObject �錾
namespace EtherEngine {
    // �V�[����̃Q�[�����\������I�u�W�F�N�g��\������
    class GameObject : public BaseObject {
    public:
        // �X�V�������s��
        void Update(void);
        // �`�揈�����s��
        void Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection);
        // �폜���������s��
        void Delete(void);


        // ���W�Q�b�^�[
        const Transform& GetTransform(void) const { return m_transform; }
        // ���W�Z�b�^�[
        void SetTransform(const Transform& in) { m_transform = in; }
        // ���W�A�N�Z�T�[
        Transform& AccessTransform(void) { return m_transform; }


        // �n���h���Q�b�^�[
        const BaseHandle<GameObject>& GetHandle(void) const { return m_handle; }


        // �R���|�[�l���g�ǉ�
        // @ Temp1: �ǉ�����R���|�[�l���g�̌^
        // @ Temps: �ǉ��R���|�[�l���g�̃R���X�g���N�^�Ɏg�p�������
        // @ Args : �ǉ��R���|�[�l���g�̃R���X�g���N�^�Ɏg�p�������
        template <Concept::BaseOfConcept<ComponentBase> ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddConponent(ArgsType&& ...args);
        // �R���|�[�l���g�폜
        // @ Temp : �폜����R���|�[�l���g�̌^
        // @ Ret  : �폜������
        template <Concept::BaseOfConcept<ComponentBase> ComponentType>
        bool DeleteComponent(void);
        // �R���|�[�l���g���擾����
        // @ Temp : �擾����R���|�[�l���g�^(ComponentBase�͎g�p�s��)
        // @ Ret  : �擾�����R���|�[�l���g
        template <typename ComponentType>
            requires Concept::BaseOfConcept<ComponentType, ComponentBase> && Concept::NotSameConcept<ComponentBase, ComponentType>
        std::weak_ptr<ComponentBase> GetComponent(void);
        // �R���|�[�l���g�𕡐��擾����
        // @ Temp : �擾����R���|�[�l���g�^(ComponentBase�͎g�p�s��)
        // @ Ret  : �擾�����R���|�[�l���g�i�����j
        template <typename ComponentType>
            requires Concept::BaseOfConcept<ComponentType, ComponentBase> && Concept::NotSameConcept<ComponentBase, ComponentType>
        std::vector<std::weak_ptr<ComponentBase>> GetComponents(void);

    protected:
        // �R���X�g���N�^
        // @ Arg1 : ���W
        // @ Arg2 : �I�u�W�F�N�g��(Default : GameObject)
        GameObject(const Transform& transform, const std::string& name = "GameObject");

    private:
        // �폜���ꂽ�R���|�[�l���g���폜����
        void DeleteComponentsDelete(void);


        friend class GameObjectStorage;

        Transform m_transform;  // ���W
        BaseHandle<GameObject> m_handle;    // ���g�̃n���h��
        std::vector<std::shared_ptr<ComponentBase>> m_components;     // �ʏ�̃R���|�[�l���g
        std::vector<std::shared_ptr<CollisionComponent>> m_collision; // �����蔻��R���|�[�l���g
        std::vector<std::shared_ptr<DrawComponent>> m_drawComponents; // �`��R���|�[�l���g
    };
}




//----- GameObject ��`
namespace EtherEngine {
    // �R���|�[�l���g�ǉ�
    // @ Temp1: �ǉ�����R���|�[�l���g�̌^
    // @ Temps: �ǉ��R���|�[�l���g�̃R���X�g���N�^�Ɏg�p�������
    // @ Args : �ǉ��R���|�[�l���g�̃R���X�g���N�^�Ɏg�p�������
    template <Concept::BaseOfConcept<ComponentBase> ComponentType, typename ...ArgsType>
    std::weak_ptr<ComponentType> GameObject::AddConponent(ArgsType&& ...args) {
        //----- �x���\��
        static_assert((std::is_constructible_v<ComponentType, GameObject*, ArgsType...>), "Error! AddComponent Args");

        //----- ����
        auto ptr = std::make_shared<ComponentType>(this, args...);

        //----- �ǉ�
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            m_drawComponents.push_back(ptr);
        }
        else {
            m_components.push_back(ptr);
        }

        //----- �ԋp
        return std::weak_ptr<ComponentType>(ptr);
    }
    // �R���|�[�l���g�폜
    // @ Temp : �폜����R���|�[�l���g�̌^
    // @ Ret  : �폜������
    template <Concept::BaseOfConcept<ComponentBase> ComponentType>
    bool GameObject::DeleteComponent(void) {
        //------ �{��
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            for (auto& component : m_drawComponents) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- �폜
                    component->DeleteFuntion();
                    component->SetDelete(true);
                }
            }
        }
        else {
            for (auto& component : m_components) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- �폜
                    component->DeleteFuntion();
                    component->SetDelete(true);
                }
            }
        }
    }
    // �R���|�[�l���g���擾����
    // @ Temp : �擾����R���|�[�l���g�^(ComponentBase�͎g�p�s��)
    // @ Ret  : �擾�����R���|�[�l���g
    template <typename ComponentType>
        requires Concept::BaseOfConcept<ComponentType, ComponentBase>&& Concept::NotSameConcept<ComponentBase, ComponentType>
    std::weak_ptr<ComponentBase> GameObject::GetComponent(void) {
        //----- �擾
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            for (auto& component : m_drawComponents) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- �ԋp
                    return std::weak_ptr<ComponentType>(component);
                }
            }
        }
        else {
            for (auto& component : m_components) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- �ԋp
                    return std::weak_ptr<ComponentType>(component);
                }
            }
        }

        //----- �����l�ԋp
        return std::weak_ptr<ComponentType>();
    }
    // �R���|�[�l���g�𕡐��擾����
    // @ Temp : �擾����R���|�[�l���g�^(ComponentBase�͎g�p�s��)
    // @ Ret  : �擾�����R���|�[�l���g�i�����j
    template <typename ComponentType>
        requires Concept::BaseOfConcept<ComponentType, ComponentBase>&& Concept::NotSameConcept<ComponentBase, ComponentType>
    std::vector<std::weak_ptr<ComponentBase>> GameObject::GetComponents(void) {
        //----- �ԋp�p�ϐ��錾
        std::vector<std::weak_ptr<ComponentBase>> ret;

        //----- �擾
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            for (auto& component : m_drawComponents) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- �ԋp�p�ϐ��ɒǉ�
                    ret.push_back(std::weak_ptr<ComponentType>(component));
                }
            }
        }
        else {
            for (auto& component : m_components) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- �ԋp�p�ϐ��ɒǉ�
                    ret.push_back(std::weak_ptr<ComponentType>(component));
                }
            }
        }

        //----- �ԋp
        return ret;
    }
}

#endif
