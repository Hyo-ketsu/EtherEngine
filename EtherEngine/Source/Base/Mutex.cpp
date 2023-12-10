#include <Base/Mutex.h>


namespace EtherEngine {
    // コンストラクタ
    Mutex::MutexLockKey::MutexLockKey(Mutex& lock) 
        : m_lock(lock) {
    }
    // デストラクタ
    Mutex::MutexLockKey::~MutexLockKey(void) {
        m_lock.UnLock();
    }


    // ロック開始を通知する
    bool Mutex::LockMessage(void) {
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
