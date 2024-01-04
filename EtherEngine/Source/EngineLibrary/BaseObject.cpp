#include <EngineLibrary/BaseObject.h>
#include <EngineLibrary/BaseObjectStorage.h>


#pragma managed
//----- BaseObject 定義
namespace EtherEngine {
    // コンストラクタ
    BaseObject::BaseObject(void) 
        : BaseObject(gcnew IDClass()) {
        BaseObjectStorage::Get->AddBaseObject(this);
    }
    // コンストラクタ
    BaseObject::BaseObject(IDClass^ id) 
        : m_isActive(true) 
        , m_id(id) {
    }


    // イベントの発火を行う
    void BaseObject::UpdateEventIgnition(System::EventArgs^ e) {
        UpdateEvent(this, e);
    }
}
