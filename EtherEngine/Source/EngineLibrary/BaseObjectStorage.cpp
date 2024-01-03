#include <EngineLibrary/BaseObjectStorage.h>


//----- BaseObjectStorage ��`
namespace EtherEngine {
    // �R���X�g���N�^
    BaseObjectStorage::BaseObjectStorage(void) 
        : m_baseObjects(gcnew System::Collections::Generic::List<BaseObject^>(0)) {
    }

    // BaseObject��ǉ�����
    void BaseObjectStorage::AddBaseObject(BaseObject^ baseObject) {
        m_baseObjects->Add(baseObject);
    }
    // ID��BaseObject���擾����
    BaseObject^ BaseObjectStorage::GetBaseObject(IDClass^ id) {
        //----- ID�Ō���
        for each (auto baseObject in m_baseObjects) {
            if (baseObject->ID == id){
                return baseObject;
            }
        }

        return nullptr;
    }
}
