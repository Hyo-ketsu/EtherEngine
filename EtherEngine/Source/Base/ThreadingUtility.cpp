#include <Base/ThreadingUtility.h>


namespace EtherEngine {
    // �X���b�h�֘A�̏������s��
    namespace ThreadingUtility {
        // ���g�̃X���b�h���w��ms�X���[�v����
        void ThisThreadSleep(uint ms) { Sleep(ms); }
    }
}
