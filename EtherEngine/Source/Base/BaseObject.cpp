#include <Base/BaseObject.h>


//----- BaseObject 定義
namespace EtherEngine {
    // コンストラクタ
    BaseObject::BaseObject(const std::string& name) 
        : m_isActive(true) 
        , m_isDelete(false) {
    }


    // このオブジェクトを削除する
    void BaseObject::DeleteObject(void) {
        m_isActive = false;
        m_isDelete = true;
    }
    // このオブジェクトがアクティブか判定する
    bool BaseObject::IsUnvalidObject(void) const {
        return m_isActive == false && m_isDelete;
    }
}
