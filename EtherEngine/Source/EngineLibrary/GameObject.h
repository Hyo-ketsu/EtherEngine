#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/NativeGameObject.h>
#include <Base/Handle.h>
#include <EngineLibrary/BaseObject.h>
namespace EtherEngine {
    ref class Component;
}
#include <EngineLibrary/Component.h>
#include <EngineLibrary/AttributeDefine.h>
#include <EngineLibrary/Scene.h>


// @ MEMO : �]�͂������GetComponent�����������������


#pragma managed
//----- GameObject �錾
namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g
    public ref class GameObject : public BaseObject {
    public:
        // �R���X�g���N�^
        GameObject(void);
        // �f�X�g���N�^
        ~GameObject(void);
        // �t�@�C�i���C�U
        !GameObject(void);


        // ���g���폜����
        void Destroy(void);


        // �l�C�e�B�u�Q�[���I�u�W�F�N�g
        property Handle<NativeGameObject> NGameObject {
            Handle<NativeGameObject> get(void) { return m_handle->GetHandle(); }
        }


        // ���͂����V�[���̃I�u�W�F�N�g�����肷��
        bool IsSceneObject(Scene^ scene);


        // �R���|�[�l���g��ǉ�����
        // @ Temp : �ǉ�����R���|�[�l���g
        // @ Ret  : �擾�����R���|�[�l���g
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        ComponentType AddComponent(void);
        // �R���|�[�l���g���擾����
        // @ Temp : �擾����R���|�[�l���g
        // @ Ret  : �擾�����R���|�[�l���g
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        ComponentType GetComponent(void);
        // �R���|�[�l���g���擾����
        // @ Temp : �擾����R���|�[�l���g
        // @ Ret  : �擾�����R���|�[�l���g
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        System::Collections::Generic::List<ComponentType>^ GetComponents(void);
        // �R���|�[�l���g���폜����
        // @ Temp : �폜�R���|�[�l���g
        // @ Ret  : �폜���s��ꂽ��
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        bool DeleteComponent(void);

    private:
        [Attribute::OutputAttribute] System::Collections::Generic::List<Component^>^ m_componentList;
        Handle<NativeGameObject>* m_handle;
        SceneIDType m_thisObjectScene;
    };
}


#endif // !I_GAMEOBJECT_H
