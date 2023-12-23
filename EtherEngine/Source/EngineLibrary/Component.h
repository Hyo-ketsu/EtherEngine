#ifndef I_COMPONENT_H
#define I_COMPONENT_H
// @ MEMO : ���ۂɃ��[�U�[���L�q���邽�߂̂��ƂƂȂ�N���X
#include <Base/NativeGameObject.h>
#include <EngineLibrary/ComponentInterface.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/BaseObject.h>
ref class GameObject;
#include <EngineLibrary/GameObject.h>


#pragma managed
//----- Component �錾
namespace EtherEngine {
    public ref class Component : public BaseObject {
    public:
        // �R���X�g���N�^
        Component(void);


        // �Q�[���I�u�W�F�N�g
        property GameObject^ ParentGameObject {
            GameObject^ get(void);
        internal: 
            void set(GameObject^ value);
        }


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
        GameObject^ m_gameObject; // ���g��ێ����Ă���Q�[���I�u�W�F�N�g
    };
}


#endif // !I_COMPONENT_H
