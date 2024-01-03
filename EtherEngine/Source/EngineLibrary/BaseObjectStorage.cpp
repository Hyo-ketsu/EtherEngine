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
