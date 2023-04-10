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
            // @ Arg1 : コンストラクタで行う処理
            // @ Arg2 : デストラクタで行う処理
            SpinLockKey(std::function<void(void)> constructor, std::function<void(void)> destructor);
            // デストラクタ
            ~SpinLockKey(void);

        private:

            std::function<void(void)> m_destructor; // デストラクタで行う処理
        };

    public:


        // コンストラクタ
        SpinLock(void);
        // デストラクタ
        ~SpinLock(void);


        // スピンロックを試行する
        void DoSpinLock(void) const noexcept;


        // ロックを行う（RAII）
        // @ Ret  : RAIIロック・アンロッククラス
        SpinLockKey KeyLock(void);
        // 手動ロックを行う
        void Lock(void);
        // 手動アンロックを行う
        void UnLock(void);

    private:
        std::atomic_bool m_isAtomicBool;  // スピンロックに用いる排他bool
    };
}


#endif // !I_SPINLOCK_H
