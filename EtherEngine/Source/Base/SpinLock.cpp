#include <Base/SpinLock.h>


namespace EtherEngine {
    // �R���X�g���N�^
    SpinLock::SpinLock(void) 
        : m_isAtomicBool(ATOMIC_FLAG_INIT) {
    }
    // �f�X�g���N�^
    SpinLock::~SpinLock(void) {
        DoSpinLock();
    }


    // �X�s�����b�N�����s����
    void SpinLock::DoSpinLock(void) const noexcept {
        while (m_isAtomicBool) {}
    }


    // ���b�N���s���iRAII�j
    SpinLock::SpinLockKey SpinLock::KeyLock(void) {
        return std::move(SpinLockKey([=]() { Lock(); }, [=]() {UnLock(); }));
    }
    // �蓮���b�N���s��
    void SpinLock::Lock(void) {
        m_isAtomicBool = true;
    }
    // �蓮�A�����b�N���s��
    void SpinLock::UnLock(void) {
        m_isAtomicBool = false;
    }
}


namespace EtherEngine {
    // �R���X�g���N�^
    // @ Arg1 : �R���X�g���N�^�ōs������
    // @ Arg2 : �f�X�g���N�^�ōs������
    SpinLock::SpinLockKey::SpinLockKey(std::function<void(void)> constructor, std::function<void(void)> destructor) 
        : m_destructor(destructor) {
        constructor();
    }
    // �f�X�g���N�^
    SpinLock::SpinLockKey::~SpinLockKey(void) {
        m_destructor();
    }
}
