#ifndef I_MUTEX_H
#define I_MUTEX_H
#include <Base/RAIIClass.h>


//----- Mutex 宣言
namespace EtherEngine {
    using MutexLockKey = RAIIClass;


    // mutexのラップクラス
    class Mutex {
    public:
        // コンストラクタ
        Mutex(void);
        // デストラクタ
        ~Mutex(void);
        // コピーコンストラクタ
        Mutex(const Mutex& move) = delete;
        // ムーブコンストラクタ
        Mutex(Mutex&& move) = default;
        // コピー代入
        Mutex& operator =(const Mutex& move) = delete;
        // ムーブ代入
        Mutex& operator =(Mutex&& move) = default;


        // ロックを試行する
        // @ Memo : スレッドがロックされます
        bool TryLock(void) const;
        // ロックが施行できるか取得
        // @ Ret  : ロックが施行できるか
        bool IsCanLock(void) const;


        // ロックを行う（RAII）
        // @ Ret  : RAIIロック・アンロッククラス
        MutexLockKey KeyLock(void) const;
        // ロックを行う（RAII）
        // @ Ret  : RAIIロック・アンロッククラス
        MutexLockKey KeySpinLock(void) const;


        // 手動ロックを行う
        void Lock(void) const;
        // 手動スピンロックを行う
        void SpinLock(void) const;
        // 手動アンロックを行う
        void UnLock(void) const;

    protected:
        // ロック開始を通知する
        // @ Ret  : ロックが可能か
        bool LockMessage(void) const;
        // ロック解除を通知する
        // @ Ret  : ロック解除が可能か
        bool UnLockMessage(void) const;


        // 自身のロックを行う
        // @ Memo : 実装自体はスピンロックで行います
        MutexLockKey ThisLock(void) const;


        HANDLE m_mutex;     // ミューテックスのハンドル
        HANDLE m_thisMutex; // 自身に行う排他処理
        static thread_local uint ms_thisThreadLockCount;   // 自身のスレッドのロック数
    };
}


#endif // !I_MUTEX_H
