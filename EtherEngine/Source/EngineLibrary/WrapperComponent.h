#ifndef I_GAMECOMPONENT_H
#define I_GAMECOMPONENT_H
#include <Base/NativeGameObject.h>
#include <EngineLibrary/Component.h>


//----- GameCompnent �錾
namespace EtherEngine {
    // 
    class WrapperComponent : public ComponentBase {
    public:
        // �R���X�g���N�^
        // @ Memo : �R���|�[�l���g�������ł��Ȃ���Η�O�𑗏o���܂�
        // @ Arg1 : �e�Q�[���I�u�W�F�N�g
        // @ Arg2 : �����R���|�[�l���g��
        WrapperComponent(NativeGameObject* gameObject, const std::string& componentName);


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

    protected:
        msclr::gcroot<Component^> m_component;  // �ێ����Ă���R���|�[�l���g
    };
}


#endif // !I_GAMECOMPONENT_H
