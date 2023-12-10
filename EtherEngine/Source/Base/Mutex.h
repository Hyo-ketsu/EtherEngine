#ifndef I_MUTEX_H
#define I_MUTEX_H
#include <Base/RAIIClass.h>
#include <Base/ManageMediation.h>


// @ Memo : 定義自体はここでされていません。


//----- Mutex 宣言
namespace EtherEngine {
    // mutexのラップクラス
    class Mutex {
    protected:
        // ロックをRAIIに則り行うクラス
        class MutexLockKey {
        public:
            // コンストラクタ
            // @ Arg1 : 親元の参照
            MutexLockKey(Mutex& lock);
            // デストラクタ
            ~MutexLockKey(void);

        private:
            Mutex& m_lock;
        };

    public:
        // デストラクタ
        virtual ~Mutex(void) {}
        // コピーコンストラクタ
        Mutex(const Mutex& move) = default;
        // ムーブコンストラクタ
        Mutex(Mutex&& move) = default;


        // ロックを試行する
        // @ Memo : スレッドがロックされます
        virtual bool TryLock(void) = 0;
        // ロックが施行できるか取得
        // @ Ret  : ロックが施行できるか
        virtual bool IsCanLock(void) = 0;


        // ロックを行う（RAII）
        // @ Ret  : RAIIロック・アンロッククラス
        virtual MutexLockKey KeyLock(void) = 0;
        // ロックを行う（RAII）
        // @ Ret  : RAIIロック・アンロッククラス
        virtual MutexLockKey KeySpinLock(void) = 0;


        // 手動ロックを行う
        virtual void Lock(void) = 0;
        // 手動スピンロックを行う
        virtual void SpinLock(void) = 0;
        // 手動アンロックを行う
        virtual void UnLock(void) = 0;

    protected:
        // コンストラクタ
        Mutex(void) {}


        // ロック開始を通知する
        // @ Ret  : ロックが可能か
        bool LockMessage(void);
        // ロック解除を通知する
        // @ Ret  : ロック解除が可能か
        bool UnLockMessage(void);


        // 自身のロックを行う
        // @ Memo : 実装自体はスピンロックで行います
        virtual MutexLockKey ThisLock(void) = 0;


        static thread_local uint ms_thisThreadLockCount;   // 自身のスレッドのロック数
    };
}


#endif // !I_MUTEX_H
