#include <Base/SpinLock.h>


//----- SpinLockKey ��`
namespace EtherEngine {
    // �R���X�g���N�^
    SpinLock::SpinLockKey::SpinLockKey(SpinLock& lock)
        : m_spinlock(lock) {
    }
    // �f�X�g���N�^
    SpinLock::SpinLockKey::~SpinLockKey(void) {
        m_spinlock.UnLock();
    }
}


//----- SpinLock ��`
namespace EtherEngine {
    // �R���X�g���N�^
    SpinLock::SpinLock(void) {
    }
    // �f�X�g���N�^
    SpinLock::~SpinLock(void) {
    }


    // �X�s�����b�N�����s����
    void SpinLock::DoSpinLock(void) {
        while (m_mutex.try_lock()) {}
        UnLock();
    }


    // ���b�N���s���iRAII�j
    SpinLock::SpinLockKey SpinLock::KeyLock(void) {
        Lock();
        return SpinLockKey(*this);
    }
    // �蓮���b�N���s��
    void SpinLock::Lock(void) {
        m_mutex.lock();
    }
    // �蓮�A�����b�N���s��
    void SpinLock::UnLock(void) {
        m_mutex.unlock();
    }
}
