#include <Base/RAIIClass.h>


namespace EtherEngine {

    // コンストラクタ
    RAIIClass::RAIIClass(std::function<void(void)> unInit)
        : m_unInit(unInit) {
    }
    // デストラクタ
    RAIIClass::~RAIIClass(void) {
        m_unInit();
    }
}
