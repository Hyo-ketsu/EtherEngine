#ifndef I_GAMEDRAWCOMPONENT_H
#define I_GAMEDRAWCOMPONENT_H
#include <Base/DrawComponent.h>
#include <EngineLibrary/GameComponent.h>
#include <EngineLibrary/UserDrawComponent.h>


//----- �`��R���|�[�l���g
namespace EtherEngine {
    // �`��R���|�[�l���g
    class ENGINELIBRARY_API GameDrawComponent : public GameComponent, public virtual DrawComponent {
    public:
        // �R���X�g���N�^
        // @ Memo : �R���|�[�l���g�������ł��Ȃ���Η�O�𑗏o���܂�
        // @ Arg1 : �e�Q�[���I�u�W�F�N�g
        // @ Arg2 : �����R���|�[�l���g��
        GameDrawComponent(GameObject* gameObject, const std::string& componentName);


        // �J�n����
        void Start(void) override;
        // �X�V����
        void Update(void) override;
        // �폜������
        void Delete(void) override;
        // �ՓˊJ�n����
        void CollisionStart(void) override;
        // �ՓˏI������
        void CollisionEnd(void) override;
        // �Փˏ���
        void CollisionHit(void) override;


        // �`��
        void Draw(void) override;


        // �O���o��
        Json Output(void) override;
        // �O������
        void Input(const Json& input) override;
    };
}


#endif // !I_GAMEDRAWCOMPONENT_H
