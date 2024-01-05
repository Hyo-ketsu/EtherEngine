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
    // BaseObject���폜����
    void BaseObjectStorage::DeleteBaseObject(BaseObject^ baseObject) {
        for (int i = 0; i < m_baseObjects->Count; i++) {
            if (baseObject->ReferenceEquals(baseObject, m_baseObjects[i])) {
                m_baseObjects[i]->~BaseObject();
                m_baseObjects->RemoveAt(i);
                return;
            }
        }
    }
    // BaseObject���폜����
    void BaseObjectStorage::DeleteBaseObject(IDClass^ id) {
        for (int i = 0; i < m_baseObjects->Count; i++) {
            if (m_baseObjects[i]->ID == id) {
                m_baseObjects[i]->~BaseObject();
                m_baseObjects->RemoveAt(i);
                return;
            }
        }
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
