#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/BaseObject.h>
#include <Base/ComponentBase.h>
#include <Base/ComponentHelper.h>
#include <Base/ConceptUtility.h>
#include <Base/DrawComponent.h> 
#include <Base/HandleHelper.h>
#include <Base/Handle.h>
#include <Base/Transform.h>
#include <Base/Scene.h>


//----- GameObject�錾
namespace EtherEngine {
    // �V�[����̃Q�[�����\������I�u�W�F�N�g��\������
    class GameObject : public BaseObject {
    public:
        // �X�V�������s��
        void Update(void);
        // �`�揈�����s��
        void Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection);


        // �R���|�[�l���g�ǉ�
        // @ Temp : �ǉ�����ʏ�R���|�[�l���g
        // @ Args : �R���X�g���N�^�ɓn������
        template <Concept::BaseOfConcept<ComponentBase> ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddConponent(ArgsType&& ...args);

        // ���W�擾
        Transform& AccessTransform(void) { return m_transform; }

    protected:
        // �R���X�g���N�^
        // @ Arg1 : ���W
        // @ Arg2 : �I�u�W�F�N�g��(Default : GameObject)
        GameObject(const Transform& transform, const std::string& name = "GameObject");


        // �ʏ�R���|�[�l���g�Ƃ��Ēǉ�����
        // @ Temp : �R���|�[�l���g�̎��
        // @ Arg1 : �ǉ�����R���|�[�l���g
        template <Concept::NotBaseOfConcept<DrawComponent> ComponentType>
        void AddConponent(std::shared_ptr<ComponentType>& component);
        // �`��R���|�[�l���g�Ƃ��Ēǉ�����
        // @ Temp : �R���|�[�l���g�̎��
        // @ Arg1 : �ǉ�����R���|�[�l���g
        template <Concept::BaseOfConcept<DrawComponent> ComponentType>
        void AddConponent(std::shared_ptr<ComponentType>& component);


    private:
        friend class GameObjectStorage;

        Transform m_transform;  // ���W
        BaseHandle<GameObject> m_handle;    // ���g�̃n���h��
        std::vector<std::shared_ptr<ComponentBase>> m_components;     // �ʏ�̃R���|�[�l���g
        std::vector<std::shared_ptr<DrawComponent>> m_drawComponents; // �`��R���|�[�l���g
    };
}




//----- GameObject��`
namespace EtherEngine {
    // �R���|�[�l���g�ǉ�
    // @ Temp : �ǉ�����ʏ�R���|�[�l���g
    template <Concept::BaseOfConcept<ComponentBase> ComponentType, typename ...ArgsType>
    std::weak_ptr<ComponentType> GameObject::AddConponent(ArgsType&& ...args) {
        //----- �x���\��
        static_assert((std::is_constructible_v<ComponentType, GameObject*, ArgsType...>), "Error! AddComponent Args");

        //----- ����
        auto ptr = std::make_shared<ComponentType>(this, args...);

        //----- �ǉ�
        AddConponent<ComponentType>(ptr);

        //----- �ԋp
        return std::weak_ptr<ComponentType>(ptr);
    }


    // �ʏ�R���|�[�l���g�Ƃ��Ēǉ�����
    // @ Temp : �R���|�[�l���g�̎��
    // @ Arg1 : �ǉ�����R���|�[�l���g
    template <Concept::NotBaseOfConcept<DrawComponent> ComponentType>
    void GameObject::AddConponent(std::shared_ptr<ComponentType>& component) {
        m_components.push_back(component);
    }
    // �`��R���|�[�l���g�Ƃ��Ēǉ�����
    // @ Temp : �R���|�[�l���g�̎��
    // @ Arg1 : �ǉ�����R���|�[�l���g
    template <Concept::BaseOfConcept<DrawComponent> ComponentType>
    void GameObject::AddConponent(std::shared_ptr<ComponentType>& component) {
        m_drawComponents.push_back(component);
    }
}

#endif
