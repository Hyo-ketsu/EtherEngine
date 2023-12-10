#include <Base/RAIIClass.h>


namespace EtherEngine {

    // �R���X�g���N�^
    RAIIClass::RAIIClass(std::function<void(void)> unInit)
        : m_unInit(unInit) {
    }
    // �f�X�g���N�^
    RAIIClass::~RAIIClass(void) {
        m_unInit();
    }
}
