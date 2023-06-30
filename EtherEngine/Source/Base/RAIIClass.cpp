#include <Base/RAIIClass.h>


namespace EtherEngine {

    // �R���X�g���N�^
    RAIIClass::RAIIClass(std::function<void(void)> init, std::function<void(void)> unInit)
        : m_unInit(unInit) {
        init();
    }
    // �f�X�g���N�^
    RAIIClass::~RAIIClass(void) {
        m_unInit();
    }
}
