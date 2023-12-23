#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/NativeGameObject.h>
#include <EngineLibrary/BaseObject.h>
ref class Component;
#include <EngineLibrary/Component.h>


//----- GameObject �錾
namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g
    public ref class GameObject : public BaseObject {
    internal:
        // �R���X�g���N�^
        GameObject(void);

    public:
        // �f�X�g���N�^
        ~GameObject(void);
        // �t�@�C�i���C�U
        !GameObject(void);

        // �R���|�[�l���g��ǉ�����
        // @ Temp : �ǉ�����R���|�[�l���g
        // @ Ret  : �擾�����R���|�[�l���g
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        ComponentType AddComponent(void) {
            //----- �R���|�[�l���g��ǉ�����
            auto ret = gcnew ComponentType();
            ret->ParentGameObject = this;
            m_componentList->Add(ret);
            return ret;
        }
        // �R���|�[�l���g���擾����
        // @ Temp : �擾����R���|�[�l���g
        // @ Ret  : �擾�����R���|�[�l���g
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        ComponentType GetComponent(void) {
            //----- �R���|�[�l���g���Ȃ�
            for each (auto it in m_componentList) {
                auto cast = dynamic_cast<ComponentType>(it);
                if (cast != nullptr) {
                    return cast;
                }
            }

            //----- �Ȃ��B
            return nullptr;
        }
        // �R���|�[�l���g���擾����
        // @ Temp : �擾����R���|�[�l���g
        // @ Ret  : �擾�����R���|�[�l���g
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        System::Collections::Generic::List<ComponentType>^ GetComponents(void) {
            //----- �ԋp�ϐ��錾
            System::Collections::Generic::List<ComponentType>^ ret = gcnew System::Collections::Generic::List<ComponentType>(0);

            //----- �R���|�[�l���g���Ȃ�
            for each (auto it in m_componentList) {
                auto cast = dynamic_cast<ComponentType>(it);
                if (cast != nullptr) {
                    ret->Add(cast);
                }
            }

            //----- �ԋp
            return ret;
        }
        // �R���|�[�l���g���폜����
        // @ Temp : �폜�R���|�[�l���g
        // @ Ret  : �폜���s��ꂽ��
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        bool DeleteComponent(void) {
            //----- �R���|�[�l���g���Ȃ�
            for (int i = 0; i < m_componentList->Count; i++) {
                auto cast = dynamic_cast<ComponentType>(m_componentList[i]);
                if (cast != nullptr) {
                    m_componentList->RemoveAt(i);
                    return true;
                }
            }

            return false;
        }

    private:
        System::Collections::Generic::List<Component^>^ m_componentList;
        Handle<NativeGameObject>* m_handle;
    };
}


#endif // !I_GAMEOBJECT_H
