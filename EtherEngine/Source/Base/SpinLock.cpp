#include <Base/SpinLock.h>


//----- SpinLockKey 定義
namespace EtherEngine {
    // コンストラクタ
    SpinLock::SpinLockKey::SpinLockKey(SpinLock& lock)
        : m_spinlock(lock) {
    }
    // デストラクタ
    SpinLock::SpinLockKey::~SpinLockKey(void) {
        m_spinlock.UnLock();
    }
}


//----- SpinLock 定義
namespace EtherEngine {
    // コンストラクタ
    SpinLock::SpinLock(void) {
    }
    // デストラクタ
    SpinLock::~SpinLock(void) {
    }


    // スピンロックを試行する
    void SpinLock::DoSpinLock(void) {
        while (m_mutex.try_lock()) {}
        UnLock();
    }


    // ロックを行う（RAII）
    SpinLock::SpinLockKey SpinLock::KeyLock(void) {
        Lock();
        return SpinLockKey(*this);
    }
    // 手動ロックを行う
    void SpinLock::Lock(void) {
        m_mutex.lock();
    }
    // 手動アンロックを行う
    void SpinLock::UnLock(void) {
        m_mutex.unlock();
    }
}
