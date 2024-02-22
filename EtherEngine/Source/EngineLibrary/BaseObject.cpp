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
        , m_isDelete(false)
        , m_id(id) {
    }


    // このオブジェクトを削除する
    void BaseObject::DeleteObject(void) {
        m_isDelete = true;
    }
    // このオブジェクトが使えないか判定する
    bool BaseObject::IsUnvalidObject(void) {
        return m_isActive && (m_isDelete == false);
    }
}
