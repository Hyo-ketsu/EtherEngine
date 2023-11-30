#include <Base/BaseUtility.h>
#include <chrono>


//----- �����m�F�p�N���X ��`
namespace EtherEngine {
    // �R���X�g���N�^
    EnableCheckClass::EnableCheckClass(void) {
        m_sharedPtr = decltype(m_sharedPtr)();
    }
    // �R�s�[�R���X�g���N�^
    EnableCheckClass::EnableCheckClass(const EnableCheckClass& copy) {
        m_sharedPtr = decltype(m_sharedPtr)();
    }


    // �����m�F�p�̃L�[���擾����
    std::weak_ptr<void> EnableCheckClass::GetEnableKey(void) {
        return std::weak_ptr<void>(m_sharedPtr);
    }
}


//----- �֗��֐� ��`
namespace EtherEngine {
    // ���g�̃X���b�h���w��ms�X���[�v����
    void ThisThreadSleep(uint ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}
