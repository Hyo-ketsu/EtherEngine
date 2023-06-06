#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/Transform.h>
#include <Base/ComponentBase.h>
#include <Base/HandleHelper.h>
#include <Base/Handle.h>
#include <Base/Scene.h>
// @ MEMO : �Q�[���I�u�W�F�N�g���Ƃ��Ă�ComponentBase�̃n���h����ێ����������o�^����ۂ̓T�u�N���X�œo�^����閵��


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
        // @ Args : �R���X�g���N�^�ɓn������
        template <ComponentConcept ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddConponent(ArgsType&& ...args);


    private:
        Transform m_transform;  // ���W

        std::vector<std::shared_ptr<ComponentBase>> m_components; // �ʏ�̃R���|�[�l���g
    };
}




//----- GameObject��`
namespace EtherEngine {
    // �R���|�[�l���g�ǉ�
    // @ Temp : �ǉ�����ʏ�R���|�[�l���g
    template <ComponentConcept ComponentType, typename ...ArgsType>
    std::weak_ptr<ComponentType> GameObject::AddConponent(ArgsType&& ...args) {
        auto ptr = std::make_shared<ComponentType>(args...);
        m_components.push_back(ptr);
        return std::weak_ptr<ComponentType>(ptr);
    }
}

#endif
