#include <Base/Mutex.h>


namespace EtherEngine {
    // �R���X�g���N�^
    Mutex::Mutex(void)
        : m_mutex(CreateMutex(NULL, FALSE, NULL))
        , m_thisMutex(CreateMutex(NULL, FALSE, NULL)) {
    }
    // �f�X�g���N�^
    Mutex::~Mutex(void) {
        CloseHandle(m_mutex);
        CloseHandle(m_thisMutex);
    }


    // ���b�N�����s����
    bool Mutex::TryLock(void) {
        //----- ���b�N���擾
        if (LockMessage()) {
            return WaitForSingleObject(m_mutex, 0);
        }
        else {
            return true;
        }
    }
    // ���b�N���{�s�ł��邩�擾
    bool Mutex::IsCanLock(void) {
        //----- ���b�N���擾
        auto ret = TryLock();

        //----- �ԋp
        if (ret) {
            //----- ���b�N���擾����Ă���B����
            UnLock();
        }
        return ret;
    }


    // ���b�N���s���iRAII�j
    MutexLockKey Mutex::KeyLock(void) {
        //----- ���b�N���擾����
        Lock();

        //----- RAII�Ń��b�v���ĕԋp
        return MutexLockKey([this]() { UnLock(); });
    }
    // ���b�N���s���iRAII�j
    MutexLockKey Mutex::KeySpinLock(void) {
        //----- �X�s�����b�N���s��
        SpinLock();

        //----- RAII�Ń��b�v���ĕԋp
        return MutexLockKey([this]() { UnLock(); });
    }


    // �蓮���b�N���s��
    void Mutex::Lock(void) {
        if (LockMessage()) {
            //----- ���b�N���擾����
            WaitForSingleObject(m_mutex, INFINITE);
        }
    }
    // �蓮�X�s�����b�N���s��
    void Mutex::SpinLock(void) {
        if (LockMessage()) {
            //----- �X�s�����b�N
            while (WaitForSingleObject(m_mutex, 0) != WAIT_OBJECT_0) {
            }
        }
    }
    // �蓮�A�����b�N���s��
    void Mutex::UnLock(void) {
        //----- �A�����b�N���s��
        if (UnLockMessage()) {
            ReleaseMutex(m_mutex);
        }
    }
    

    // ���g�̃��b�N���s��
    MutexLockKey Mutex::ThisLock(void) {
        //----- �X�s�����b�N
        while (WaitForSingleObject(m_thisMutex, 0) != WAIT_OBJECT_0) {
        }

        //----- RAII�Ń��b�v���ĕԋp
        return MutexLockKey([this]() { ReleaseMutex(m_thisMutex); });
    }


    // ���b�N�J�n��ʒm����
    bool Mutex::LockMessage(void) {
        //----- ���b�N����
        auto lock = ThisLock();

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
        //----- ���b�N����
        auto lock = ThisLock();

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
