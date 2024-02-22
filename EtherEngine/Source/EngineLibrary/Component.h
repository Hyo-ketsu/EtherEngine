#ifndef I_COMPONENT_H
#define I_COMPONENT_H
// @ MEMO : ���ۂɃ��[�U�[���L�q���邽�߂̂��ƂƂȂ�N���X
#include <Base/NativeGameObject.h>
#include <EngineLibrary/AttributeDefine.h>
#include <EngineLibrary/ComponentInterface.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/BaseObject.h>


//----- �O���錾
namespace EtherEngine {
    ref class GameObject;
}


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
            void set(GameObject^ value);
        }


        // �ǉ�������
        virtual void Create(void) {}
        // �J�n����
        virtual void Start(void) {}
        // �X�V����
        virtual void Update(void) {}
        // �X�V�㏈��
        virtual void LateUpdate(void) {}
        // �폜������
        virtual void Delete(void) {}
        // �ՓˊJ�n����
        virtual void CollisionStart(void) {}
        // �ՓˏI������
        virtual void CollisionEnd(void) {}
        // �Փˏ���
        virtual void CollisionHit(void) {}
        
    private:
        [Attribute::OutputAttribute]
        GameObject^ m_gameObject;  // �e�Q�[���I�u�W�F�N�g��ID
    };
}


#endif // !I_COMPONENT_H
