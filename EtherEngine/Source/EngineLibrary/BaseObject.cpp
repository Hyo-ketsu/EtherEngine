#include <EngineLibrary/BaseObject.h>


#pragma managed
//----- BaseObject 定義
namespace EtherEngine {
    // コンストラクタ
    BaseObject::BaseObject(void) 
        : BaseObject(gcnew IDClass()) {
    }
    // コンストラクタ
    BaseObject::BaseObject(IDClass^ id) 
        : m_isActive(true) 
        , m_id(id) {
    }
}
