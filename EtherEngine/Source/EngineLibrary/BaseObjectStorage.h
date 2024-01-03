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
        // ID��BaseObject���擾����
        // @ Ret  : �擾����BaseObject
        // @ Arg1 : ID
        BaseObject^ GetBaseObject(IDClass^ id);

    private:
        System::Collections::Generic::List<BaseObject^>^ m_baseObjects; // �ێ����Ă���x�[�X�I�u�W�F�N�g�ꗗ
    };
}


#endif // !I_BASEOBJECTSTORAGE_H
