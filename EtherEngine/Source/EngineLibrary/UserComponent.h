#ifndef I_USERCOMPONENT_H
#define I_USERCOMPONENT_H
// @ MEMO : ���ۂɃ��[�U�[���L�q���邽�߂̂��ƂƂȂ�N���X
#include <EngineLibrary/ComponentInterface.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <ImGUI/ImGUIWrapFunction.h>
#include <Base/GameObject.h>


//----- UseBaseComponent �錾
namespace EtherEngine {
#ifdef _ENGINELIBRARY
    public ref class UserBaseComponent : public Serializer, public IInspectorDrawer {
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


        // Inspector�\��
        void DrawInspector(void) override; 

    private:
        GameObject* m_gameObject; // ���g��ێ����Ă���Q�[���I�u�W�F�N�g
    };
#endif
}


#endif // !I_USERCOMPONENT_H
