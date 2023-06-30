#include <Base/RAIIClass.h>


namespace EtherEngine {

    // コンストラクタ
    RAIIClass::RAIIClass(std::function<void(void)> init, std::function<void(void)> unInit)
        : m_unInit(unInit) {
        init();
    }
    // デストラクタ
    RAIIClass::~RAIIClass(void) {
        m_unInit();
    }
}
