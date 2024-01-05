#ifndef I_BASEOBJECTSTORAGE_H
#define I_BASEOBJECTSTORAGE_H
#include <EngineLibrary/ManageSingleton.h>
#include <EngineLibrary/BaseObject.h>


//----- BaseObjectStorage ��`
namespace EtherEngine {
    // BaseObject���Ǘ�����N���X
    public ref class BaseObjectStorage {
        ETHER_ENGINE_MANAGE_SINGLETON(BaseObjectStorage);
    public:
        // BaseObject��ǉ�����
        // @ Arg1 : �ǉ�����BaseObject
        void AddBaseObject(BaseObject^ baseObject);
        // BaseObject���폜����
        // @ Ret  : �폜���s��ꂽ��
        // @ Arg1 : �폜����BaseObject
        void DeleteBaseObject(BaseObject^ baseObject);
        // BaseObject���폜����
        // @ Ret  : �폜���s��ꂽ��
        // @ Arg1 : �폜����BaseObject��ID
        void DeleteBaseObject(IDClass^ id);


        // ID��BaseObject���擾����
        // @ Ret  : �擾����BaseObject
        // @ Arg1 : ID
        BaseObject^ GetBaseObject(IDClass^ id);

    private:
        System::Collections::Generic::List<BaseObject^>^ m_baseObjects; // �ێ����Ă���x�[�X�I�u�W�F�N�g�ꗗ
    };
}


#endif // !I_BASEOBJECTSTORAGE_H
