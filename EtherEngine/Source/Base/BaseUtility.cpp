#include <Base/BaseUtility.h>


//----- 生存確認用クラス 定義
namespace EtherEngine {
    // コンストラクタ
    EnableCheckClass::EnableCheckClass(void) {
        m_sharedPtr = decltype(m_sharedPtr)();
    }
    // コピーコンストラクタ
    EnableCheckClass::EnableCheckClass(const EnableCheckClass& copy) {
        m_sharedPtr = decltype(m_sharedPtr)();
    }


    // 生存確認用のキーを取得する
    std::weak_ptr<void> EnableCheckClass::GetEnableKey(void) {
        return std::weak_ptr<void>(m_sharedPtr);
    }
}
