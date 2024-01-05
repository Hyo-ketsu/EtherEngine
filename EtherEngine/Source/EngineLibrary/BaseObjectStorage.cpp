#include <EngineLibrary/BaseObjectStorage.h>


//----- BaseObjectStorage 定義
namespace EtherEngine {
    // コンストラクタ
    BaseObjectStorage::BaseObjectStorage(void) 
        : m_baseObjects(gcnew System::Collections::Generic::List<BaseObject^>(0)) {
    }


    // BaseObjectを追加する
    void BaseObjectStorage::AddBaseObject(BaseObject^ baseObject) {
        m_baseObjects->Add(baseObject);
    }
    // BaseObjectを削除する
    void BaseObjectStorage::DeleteBaseObject(BaseObject^ baseObject) {
        for (int i = 0; i < m_baseObjects->Count; i++) {
            if (baseObject->ReferenceEquals(baseObject, m_baseObjects[i])) {
                m_baseObjects[i]->~BaseObject();
                m_baseObjects->RemoveAt(i);
                return;
            }
        }
    }
    // BaseObjectを削除する
    void BaseObjectStorage::DeleteBaseObject(IDClass^ id) {
        for (int i = 0; i < m_baseObjects->Count; i++) {
            if (m_baseObjects[i]->ID == id) {
                m_baseObjects[i]->~BaseObject();
                m_baseObjects->RemoveAt(i);
                return;
            }
        }
    }


    // IDでBaseObjectを取得する
    BaseObject^ BaseObjectStorage::GetBaseObject(IDClass^ id) {
        //----- IDで検索
        for each (auto baseObject in m_baseObjects) {
            if (baseObject->ID == id){
                return baseObject;
            }
        }

        return nullptr;
    }
}
