#ifndef I_SPINLOCK_H
#define I_SPINLOCK_H


namespace EtherEngine {
    // スピンロックを簡潔に実装するクラス
    class SpinLock {
    private:
        // スピンロックをRAIIに則り行うクラス
        class SpinLockKey {
        public:
            // コンストラクタ
            // @ Arg1 : 親元の参照
            SpinLockKey(SpinLock& lock);
            // デストラクタ
            ~SpinLockKey(void);

        private:
            SpinLock& m_spinlock;
        };

    public:
        // コンストラクタ
        SpinLock(void);
        // デストラクタ
        ~SpinLock(void);


        // スピンロックを試行する
        void DoSpinLock(void);


        // ロックを行う（RAII）
        // @ Ret  : RAIIロック・アンロッククラス
        SpinLockKey KeyLock(void);
        // 手動ロックを行う
        void Lock(void);
        // 手動アンロックを行う
        void UnLock(void);

    private:
        std::recursive_mutex m_mutex;  // スピンロックに用いるミューテックス
        std::atomic_bool m_isAtomic;   // スピンロックに用いるAtomicBool
    };
}


#endif // !I_SPINLOCK_H
