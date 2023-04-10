#include <Base/SpinLock.h>


namespace EtherEngine {
    // コンストラクタ
    SpinLock::SpinLock(void) 
        : m_isAtomicBool(ATOMIC_FLAG_INIT) {
    }
    // デストラクタ
    SpinLock::~SpinLock(void) {
        DoSpinLock();
    }


    // スピンロックを試行する
    void SpinLock::DoSpinLock(void) const noexcept {
        while (m_isAtomicBool) {}
    }


    // ロックを行う（RAII）
    SpinLock::SpinLockKey SpinLock::KeyLock(void) {
        return std::move(SpinLockKey([=]() { Lock(); }, [=]() {UnLock(); }));
    }
    // 手動ロックを行う
    void SpinLock::Lock(void) {
        m_isAtomicBool = true;
    }
    // 手動アンロックを行う
    void SpinLock::UnLock(void) {
        m_isAtomicBool = false;
    }
}


namespace EtherEngine {
    // コンストラクタ
    // @ Arg1 : コンストラクタで行う処理
    // @ Arg2 : デストラクタで行う処理
    SpinLock::SpinLockKey::SpinLockKey(std::function<void(void)> constructor, std::function<void(void)> destructor) 
        : m_destructor(destructor) {
        constructor();
    }
    // デストラクタ
    SpinLock::SpinLockKey::~SpinLockKey(void) {
        m_destructor();
    }
}
