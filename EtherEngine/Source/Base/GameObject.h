#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/Transform.h>
#include <Base/ComponentBase.h>
#include <Base/HandleHelper.h>
#include <Base/Handle.h>
#include <Base/Scene.h>


namespace EtherEngine {
    // �R���|�[�l���g����p������Ă��邩���肷��R���Z�v�g
    template <typename T>
    concept ComponentConcept = std::is_base_of_v<ComponentBase, T>;
}


//----- GameObject�錾
namespace EtherEngine {
    // �V�[����̃Q�[�����\������I�u�W�F�N�g��\������
    class GameObject {
    public:
        // �R���X�g���N�^
        // @ Arg1 : ���W
        GameObject(const Transform& transform);


        // �X�V�������s��
        void Update(void);
        // �`�揈�����s��
        void Draw(void);


        // �R���|�[�l���g�ǉ�
        // @ Temp : �ǉ�����ʏ�R���|�[�l���g
        template <ComponentConcept ComponentType>
        RefHandle<ComponentType> AddConponent(void);


    private:
        Transform m_transform;  // ���W

        std::vector<Handle<ComponentBase>> m_component; // �ʏ�̃R���|�[�l���g
    };
}




//----- GameObject��`
namespace EtherEngine {
    // �R���|�[�l���g�ǉ�
    // @ Temp : �ǉ�����ʏ�R���|�[�l���g
    template <ComponentConcept ComponentType>
    RefHandle<ComponentType> GameObject::AddConponent(void) {
        ComponentType component;
        auto handle = HandleHelper::AddItem(std::move(component), HandleCountType::Count);
        m_component.push_back(std::move(handle));
        return HandleHelper::GetRefHandle(handle);
    }
    // �R���|�[�l���g�ǉ�
    // @ Temp : �ǉ�����`��p�R���|�[�l���g
    template <DrawComponentConcept ComponentType>
    RefHandle<ComponentType> GameObject::AddConponent(void) {
        ComponentType component;
        auto handle = HandleHelper::AddItem(std::move(component), HandleCountType::Count);
        m_drawComponent.push_back(std::move(handle));
        return HandleHelper::GetRefHandle(handle);
    }
}

#endif
