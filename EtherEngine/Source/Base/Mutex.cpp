#include <Base/Mutex.h>


namespace EtherEngine {
    // �R���X�g���N�^
    Mutex::MutexLockKey::MutexLockKey(Mutex& lock) 
        : m_lock(lock) {
    }
    // �f�X�g���N�^
    Mutex::MutexLockKey::~MutexLockKey(void) {
        m_lock.UnLock();
    }


    // ���b�N�J�n��ʒm����
    bool Mutex::LockMessage(void) {
        //----- ���b�N���Z
        ms_thisThreadLockCount += 1;

        //----- ���b�N���擾�ł��邩
        if (ms_thisThreadLockCount < 2) {
            //----- 1�ȉ��B���߂Ẵ��b�N�擾�̂��ߎ擾�ł���Ɣ��肷��
            return true;
        }
        else {
            //----- 2�ȏ�B���łɃ��b�N������Ă���Ƃ��Ĕ��肷��
            return false;
        }
    }
    // ���b�N������ʒm����
    bool Mutex::UnLockMessage(void) {
        //----- ���b�N�������ł��邩
        if (ms_thisThreadLockCount > 0) {
            //----- 1�ȏ�B���b�N������Ă���Ɣ���A���b�N�������炷
            ms_thisThreadLockCount -= 1;
            return true;
        }
        else {
            //----- 0�B���b�N������Ă��Ȃ��̂ŉ������s��Ȃ�
            return false;
        }
    }


    thread_local uint Mutex::ms_thisThreadLockCount = 0;   // ���g�̃X���b�h�̃��b�N��
}
