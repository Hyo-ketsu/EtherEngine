#ifndef I_USERCOMPONENT_H
#define I_USERCOMPONENT_H
// @ MEMO : ���ۂɃ��[�U�[���L�q���邽�߂̂��ƂƂȂ�N���X
#include <C++CLI/ComponentInterface.h>
#include <C++CLI/C++CLIUtility.h>
#include <Base/GameObject.h>


//----- UseBaseComponent �錾
namespace EtherEngine {
    public ref class UserBaseComponent : Serializer {
    public:
        // �R���X�g���N�^
        // @ MEMO : ���[�u
        UserBaseComponent(void)
            : m_gameObject(nullptr) {
        }


        // �e�Q�[���I�u�W�F�N�g�Q�b�^�[
        GameObject* const GetGameObject(void) { return m_gameObject; }
        // �e�Q�[���I�u�W�F�N�g�Z�b�^�[
        void SetGameObject(GameObject* in) { m_gameObject = in; }


        // �J�n����
        virtual void Start(void) {}
        // �X�V����
        virtual void Update(void) {}
        // �폜������
        virtual void Delete(void) {}
        // �ՓˊJ�n����
        virtual void CollisionStart(void) {}
        // �ՓˏI������
        virtual void CollisionEnd(void) {}
        // �Փˏ���
        virtual void CollisionHit(void) {}

    private:
        GameObject* m_gameObject; // ���g��ێ����Ă���Q�[���I�u�W�F�N�g
    };
}


#endif // !I_USERCOMPONENT_H