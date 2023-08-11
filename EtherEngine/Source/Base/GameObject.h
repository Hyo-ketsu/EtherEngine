#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/BaseDefines.h>
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
#include <Base/ParentAndChildObject.h>
#include <Base/EtherEngineUtility.h>


//----- GameObject �錾
namespace EtherEngine {
    // �V�[����̃Q�[�����\������I�u�W�F�N�g��\������
    class GameObject : public BaseObject, public IInOuter {
    public:
        // �X�V�������s��
        void Update(void);
        // �����X�V�������s��
        void FixedUpdate(void);
        // �`�揈�����s��
        void Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection);
        // �폜���������s��
        void Delete(void);
        // �ՓˊJ�n�������s��
        void CollisionStart(void);
        // �ՓˏI���������s��
        void CollisionEnd(void);
        // �Փˏ������s��
        void CollisionHit(void);


        // ���W�Q�b�^�[
        // @ Ret  : ��΍��W
        const Transform& GetTransform(void) const { return m_transform; }
        // ���W�Z�b�^�[
        // @ Arg1 : ��΍��W
        void SetTransform(const Transform& in) { m_transform = in; }
        // ���W�A�N�Z�T�[
        // @ Ret  : ��΍��W
        Transform& AccessTransform(void) { return m_transform; }

        // ���΍��W�Q�b�^�[
        // @ MEMO : ������
        // @ Ret  : ���΍��W
        const Transform& GetLocalTransform(void) const;
        // ���΍��W�Z�b�^�[
        // @ MEMO : ������
        // @ Arg1 : ���΍��W
        void SetLocalTransform(const Transform& in);


        // �V�[�����Q�b�^�[
        const SceneData& GetScene(void) const { return m_scene; }
        // �V�[�����Z�b�^�[
        void SetScene(const SceneData& in) { m_scene = in; }

        // �e�q�֌W�Q�b�^�[
        const ParentAndChildObject<GameObject> GetParentAndChild(void) const { return m_parentAndChild; }
        // �e�q�֌W�Z�b�^�[
        void SetParentAndChild(const ParentAndChildObject<GameObject>& in) { m_parentAndChild = in; }
        // �e�q�֌W�A�N�Z�T�[
        ParentAndChildObject<GameObject>& AccessParentAndChild(void) { return m_parentAndChild; }


        // �n���h���Q�b�^�[
        const BaseHandle<GameObject>& GetHandle(void) const { return m_handle; }


        // �Փˏ����폜�E�X�^�b�L���O����
        void SidelineCollisionData(void);
        // �Փˏ���ǉ�����
        // @ Arg1 : �ǉ����铖���蔻����
        void AddCollisionData(const CollisionHitData data);


        // �R���|�[�l���g�ǉ�
        // @ Temp1: �ǉ�����R���|�[�l���g�̌^
        // @ Temps: �ǉ��R���|�[�l���g�̃R���X�g���N�^�Ɏg�p�������
        // @ Args : �ǉ��R���|�[�l���g�̃R���X�g���N�^�Ɏg�p�������
        template <Concept::SubClassOnly<ComponentBase> ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddComponent(ArgsType&& ...args);
        // �R���|�[�l���g�폜
        // @ Temp : �폜����R���|�[�l���g�̌^
        // @ Ret  : �폜������
        template <Concept::SubClassOnly<ComponentBase> ComponentType>
        bool DeleteComponent(void);
        // �R���|�[�l���g���擾����
        // @ Temp : �擾����R���|�[�l���g�^(ComponentBase�͎g�p�s��)
        // @ Ret  : �擾�����R���|�[�l���g
        // @ Arg1 : ���Ԗڂ̃R���|�[�l���g���g�p���邩(Default : 0)
        template <Concept::SubClassOnly<ComponentBase> ComponentType>
        std::weak_ptr<ComponentType> GetComponent(uint index = 0);
        // �R���|�[�l���g�𕡐��擾����
        // @ Temp : �擾����R���|�[�l���g�^(ComponentBase�͎g�p�s��)
        // @ Ret  : �擾�����R���|�[�l���g�i�����j
        template <Concept::SubClassOnly<ComponentBase> ComponentType>
        std::vector<std::weak_ptr<ComponentType>> GetComponents(void);


        // �O���o��
        Json Output(void) override;
        // �O������
        void Input(const Json& input) override;

    protected:
        // �R���X�g���N�^
        // @ Arg1 : ���W
        // @ Arg2 : �I�u�W�F�N�g��(Default : GameObject)
        GameObject(const Transform& transform, const std::string& name = "GameObject");

    private:
        // �폜���ꂽ�R���|�[�l���g���폜����
        void DeleteComponentsDelete(void);


        friend class GameObjectStorage;
        friend class CPPCLI;

        Transform m_transform;  // ���W
        SceneData m_scene;      // ���ݏ����V�[��
        BaseHandle<GameObject> m_handle;    // ���g�̃n���h��
        ParentAndChildObject<GameObject> m_parentAndChild;  // ���̃Q�[���I�u�W�F�N�g�̐e�q�֌W
        std::vector<std::shared_ptr<ComponentBase>> m_components;     // �ʏ�̃R���|�[�l���g
        std::vector<std::shared_ptr<CollisionComponent>> m_collisions;// �����蔻��R���|�[�l���g
        std::vector<std::shared_ptr<DrawComponent>> m_drawComponents; // �`��R���|�[�l���g
        std::vector<CollisionHitData> m_hitData;     // �ێ����Ă��邻�̃t���[���̓����蔻����
        std::vector<CollisionHitData> m_oldHitData;  // �ێ����Ă���O�t���[���̓����蔻����

        static std::function<std::shared_ptr<ComponentBase>&&(GameObject*, const std::string&)> ms_getComponent; // C++CLI��GameComponent�Ȃǂ��擾���邽�߂̃����_
        static std::function<std::shared_ptr<DrawComponent>&&(GameObject*, const std::string&)> ms_getDrawComponent; // C++CLI��GameDrawComponent�Ȃǂ��擾���邽�߂̃����_
    };
}




//----- GameObject ��`
namespace EtherEngine {
    // �R���|�[�l���g�ǉ�
    // @ Temp1: �ǉ�����R���|�[�l���g�̌^
    // @ Temps: �ǉ��R���|�[�l���g�̃R���X�g���N�^�Ɏg�p�������
    // @ Args : �ǉ��R���|�[�l���g�̃R���X�g���N�^�Ɏg�p�������
    template <Concept::SubClassOnly<ComponentBase> ComponentType, typename ...ArgsType>
    std::weak_ptr<ComponentType> GameObject::AddComponent(ArgsType&& ...args) {
        //----- �x���\��
        static_assert((std::is_constructible_v<ComponentType, GameObject*, ArgsType...>), "Error! AddComponent Args");

        //----- ����
        auto ptr = std::make_shared<ComponentType>(this, args...);

        //----- �ǉ�
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            m_drawComponents.push_back(ptr);
        }
        else if constexpr (Concept::BaseOfConcept<ComponentType, CollisionComponent>) {
            m_collisions.push_back(ptr);
        } else {
            m_components.push_back(ptr);
        }

        //----- �ԋp
        return std::weak_ptr<ComponentType>(ptr);
    }
    // �R���|�[�l���g�폜
    // @ Temp : �폜����R���|�[�l���g�̌^
    // @ Ret  : �폜������
    template <Concept::SubClassOnly<ComponentBase> ComponentType>
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
        else if constexpr (Concept::BaseOfConcept<ComponentType, CollisionComponent>) {
            for (auto& component : m_collisions) {
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
    // @ Arg1 : ���Ԗڂ̃R���|�[�l���g���g�p���邩(Default : 0)
    template <Concept::SubClassOnly<ComponentBase> ComponentType>
    std::weak_ptr<ComponentType> GameObject::GetComponent(uint index) {
        //----- �擾
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            for (auto& component : m_drawComponents) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- �w��ԍ���
                    if (index != 0) {
                        //----- �w��̔ԍ��܂ŒB���Ă��Ȃ��B�ԍ���1�팸���Ď擾���p������
                        index--;
                        continue;
                    }

                    //----- �ԋp
                    return std::weak_ptr<ComponentType>(component);
                }
            }
        }
        else if constexpr (Concept::BaseOfConcept<ComponentType, CollisionComponent>) {
            for (auto& component : m_collisions) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- �w��ԍ���
                    if (index != 0) {
                        //----- �w��̔ԍ��܂ŒB���Ă��Ȃ��B�ԍ���1�팸���Ď擾���p������
                        index--;
                        continue;
                    }

                    //----- �ԋp
                    return std::weak_ptr<ComponentType>(component);
                }
            }
        }
        else {
            for (auto& component : m_components) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- �w��ԍ���
                    if (index != 0) {
                        //----- �w��̔ԍ��܂ŒB���Ă��Ȃ��B�ԍ���1�팸���Ď擾���p������
                        index--;
                        continue;
                    }

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
    template <Concept::SubClassOnly<ComponentBase> ComponentType>
    std::vector<std::weak_ptr<ComponentType>> GameObject::GetComponents(void) {
        //----- �ԋp�p�ϐ��錾
        std::vector<std::weak_ptr<ComponentType>> ret;

        //----- �擾
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            for (auto& component : m_drawComponents) {
                if (dynamic_cast<ComponentType*>(component.get()) != nullptr) {
                    //----- �ԋp�p�ϐ��ɒǉ�
                    ret.push_back(std::weak_ptr<ComponentType>(component));
                }
            }
        }
        else if constexpr (Concept::BaseOfConcept<ComponentType, CollisionComponent>) {
            for (auto& component : m_collisions) {
                if (dynamic_cast<ComponentType*>(component.get()) != nullptr) {
                    //----- �ԋp�p�ϐ��ɒǉ�
                    ret.push_back(std::weak_ptr<ComponentType>(component));
                }
            }
        }
        else {
            for (auto& component : m_components) {
                if (dynamic_cast<ComponentType*>(component.get()) != nullptr) {
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
