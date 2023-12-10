#include <Base/Mutex.h>


namespace EtherEngine {
    // コンストラクタ
    Mutex::Mutex(void)
        : m_mutex(CreateMutex(NULL, FALSE, NULL))
        , m_thisMutex(CreateMutex(NULL, FALSE, NULL)) {
    }
    // デストラクタ
    Mutex::~Mutex(void) {
        CloseHandle(m_mutex);
        CloseHandle(m_thisMutex);
    }


    // ロックを試行する
    bool Mutex::TryLock(void) {
        //----- ロックを取得
        if (LockMessage()) {
            return WaitForSingleObject(m_mutex, 0);
        }
        else {
            return true;
        }
    }
    // ロックが施行できるか取得
    bool Mutex::IsCanLock(void) {
        //----- ロックを取得
        auto ret = TryLock();

        //----- 返却
        if (ret) {
            //----- ロックが取得されている。解除
            UnLock();
        }
        return ret;
    }


    // ロックを行う（RAII）
    MutexLockKey Mutex::KeyLock(void) {
        //----- ロックを取得する
        Lock();

        //----- RAIIでラップして返却
        return MutexLockKey([this]() { UnLock(); });
    }
    // ロックを行う（RAII）
    MutexLockKey Mutex::KeySpinLock(void) {
        //----- スピンロックを行う
        SpinLock();

        //----- RAIIでラップして返却
        return MutexLockKey([this]() { UnLock(); });
    }


    // 手動ロックを行う
    void Mutex::Lock(void) {
        if (LockMessage()) {
            //----- ロックを取得する
            WaitForSingleObject(m_mutex, INFINITE);
        }
    }
    // 手動スピンロックを行う
    void Mutex::SpinLock(void) {
        if (LockMessage()) {
            //----- スピンロック
            while (WaitForSingleObject(m_mutex, 0) != WAIT_OBJECT_0) {
            }
        }
    }
    // 手動アンロックを行う
    void Mutex::UnLock(void) {
        //----- アンロックを行う
        if (UnLockMessage()) {
            ReleaseMutex(m_mutex);
        }
    }
    

    // 自身のロックを行う
    MutexLockKey Mutex::ThisLock(void) {
        //----- スピンロック
        while (WaitForSingleObject(m_thisMutex, 0) != WAIT_OBJECT_0) {
        }

        //----- RAIIでラップして返却
        return MutexLockKey([this]() { ReleaseMutex(m_thisMutex); });
    }


    // ロック開始を通知する
    bool Mutex::LockMessage(void) {
        //----- ロックする
        auto lock = ThisLock();

        //----- ロック加算
        ms_thisThreadLockCount += 1;

        //----- ロックが取得できるか
        if (ms_thisThreadLockCount < 2) {
            //----- 1以下。初めてのロック取得のため取得できると判定する
            return true;
        }
        else {
            //----- 2以上。すでにロックがされているとして判定する
            return false;
        }
    }
    // ロック解除を通知する
    bool Mutex::UnLockMessage(void) {
        //----- ロックする
        auto lock = ThisLock();

        //----- ロックが解除できるか
        if (ms_thisThreadLockCount > 0) {
            //----- 1以上。ロックがされていると判定、ロック数を減らす
            ms_thisThreadLockCount -= 1;
            return true;
        }
        else {
            //----- 0。ロックがされていないので解除も行わない
            return false;
        }
    }


    thread_local uint Mutex::ms_thisThreadLockCount = 0;   // 自身のスレッドのロック数
}
