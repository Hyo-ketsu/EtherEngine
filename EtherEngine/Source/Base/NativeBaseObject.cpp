#include <Base/NativeBaseObject.h>


//----- NativeBaseObject 定義
namespace EtherEngine {
    // コンストラクタ
    NativeBaseObject::NativeBaseObject(const std::string& name) 
        : m_isActive(true) 
        , m_isDelete(false) {
    }


    // このオブジェクトを削除する
    void NativeBaseObject::DeleteObject(void) {
        m_isActive = false;
        m_isDelete = true;
    }
    // このオブジェクトがアクティブか判定する
    bool NativeBaseObject::IsUnvalidObject(void) const {
        return m_isActive == false && m_isDelete;
    }
}
