#ifndef I_GAMECOMPONENT_H
#define I_GAMECOMPONENT_H
#include <Base/GameObject.h>
#include <C++CLI/UserComponent.h>


//----- GameCompnent �錾
namespace EtherEngine {
    // 
    class GameComponent : public ComponentBase {
    public:
        // �R���X�g���N�^
        // @ Memo : �R���|�[�l���g�������ł��Ȃ���Η�O�𑗏o���܂�
        // @ Arg1 : �e�Q�[���I�u�W�F�N�g
        // @ Arg2 : �����R���|�[�l���g��
        GameComponent(GameObject* gameObject, const std::string& componentName);


        // ���g�̃R���|�[�l���g���̎擾
        std::string GetComponentName(void) const override { return m_componentName; }


        // �J�n����
        void Start(void);
        // �X�V����
        void Update(void);
        // �폜������
        void Delete(void);
        // �ՓˊJ�n����
        void CollisionStart(void);
        // �ՓˏI������
        void CollisionEnd(void);
        // �Փˏ���
        void CollisionHit(void);


        // �O���o��
        Json Output(void) override;
        // �O������
        void Input(const Json& input) override;

        // Inspector�\��
        void ShowInspector(void) override;

    protected:
        std::string m_componentName;    // ���g�̃R���|�[�l���g��
        msclr::gcroot<UserBaseComponent^> m_component;  // �ێ����Ă���R���|�[�l���g
    };
}


#endif // !I_GAMECOMPONENT_H
