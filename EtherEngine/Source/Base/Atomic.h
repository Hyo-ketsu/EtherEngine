#ifndef I_ATOMIC_H
#define I_ATOMIC_H
#include <Base/AtomicData.h>
#include <Base/AtomicReadData.h>
#include <Base/NonAtomicData.h>


namespace EtherEngine {
    // 排他制御を行うクラス
    // @ Temp : 排他を行う型
    template <class AtomicType>
    class Atomic {
    public:
        Atomic(const Atomic&) = delete;
        Atomic& operator=(const Atomic&) = delete;


        // コンストラクタ
        // @ Memo : 引数は右辺値のみ受け付けます
        // @ Arg1 : 排他を行う情報
        Atomic(AtomicType&& data);
        // デストラクタ
        ~Atomic(void) noexcept;
        // ムーブコンストラクタ
        // @ Memo : 所有権の移動を表現しています
        Atomic(Atomic&& move) noexcept;


        // データを取得する
        // @ Ret  : 排他制御されたデータ
        AtomicData<AtomicType> GetData(void);
        // データを取得する
        // @ Ret  : 排他制御されていないデータ
        NonAtomicData<AtomicType> GetNonAtomicData(void);
        // 読み取り専用データを取得する
        // @ Ret  : 排他制御された読み取り専用データ
        AtomicReadData<AtomicType> GetReadData(void);


        // ロックを取得できるか
        // @ Ret  : ロックを取得できる（= ロックされていない）なら true
        bool TryLock(void);
        // 読み取りロックを取得できるか
        // @ Ret  : ロックを取得できる（= ロックされていない）なら true
        bool TryReadLock(void);


    private:
        std::unique_ptr<AtomicType> m_data;  // 保持しているデータ
        std::recursive_mutex        m_mutex; // 排他用ミューテックス
        std::mutex                m_readMutex;     // 読み取りロック用ミューテックス
        std::condition_variable   m_readCondition; // 読み取りロック用条件変数
        std::atomic<unsigned int> m_readCount;     // 読み取りロック用Read数
    };
}




//----- Atomic実装
namespace EtherEngine {
    // コンストラクタ
    // @ Memo : 引数はムーブされたもののみ受け付けます
    // @ Arg1 : 排他を行う情報
    template <class AtomicType>
    Atomic<AtomicType>::Atomic(AtomicType&& data)
        : m_data(std::make_unique<AtomicType>(data)) {
    }
    // デストラクタ
    template <class AtomicType>
    Atomic<AtomicType>::~Atomic(void) noexcept {
    }
    // ムーブコンストラクタ
    // @ Memo : 所有権の移動を表現しています
    template <class AtomicType>
    Atomic<AtomicType>::Atomic(Atomic&& move) noexcept {
        //----- ロックを行う
        {
            std::lock_guard<std::recursive_mutex> lock(move.m_mutex);

            //----- 読み取りロックがされているか
            if (m_readCount.load() > 0) {
                //----- 読み込み数が1以上。読み取りロック（書き込み側のスレッドを寝かす）を行う
                std::unique_lock<std::mutex> lock(m_readMutex);
                m_readCondition.wait(lock, [this] {return m_readCount.load() > 0; });
            }
        }

        //----- ムーブ
        m_data = std::move(move.m_data);
        m_mutex = std::move(move.m_mutex);
    }


    // データを取得する
    // @ Ret  : 排他制御されたデータ
    template <class AtomicType>
    AtomicData<AtomicType> Atomic<AtomicType>::GetData(void) {
        //----- 書き込みが終了するまで待機する
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        //----- 読み取りロックがされているか
        if (m_readCount.load() > 0) {
            //----- 読み込み数が1以上。読み取りロック（書き込み側のスレッドを寝かす）を行う
            std::unique_lock<std::mutex> lock(m_readMutex);
            m_readCondition.wait(lock, [this] {return m_readCount.load() > 0; });
        }

        //----- 排他データの作成と返却
        return std::move(AtomicData<AtomicType>(*m_data,
            [this](void) -> void { m_mutex.lock(); }, [this](void) -> void { m_mutex.unlock(); }));
    }
    // データを取得する
    // @ Ret  : 排他制御されていないデータ
    template <class AtomicType>
    NonAtomicData<AtomicType> Atomic<AtomicType>::GetNonAtomicData(void) {
        //----- 書き込みが終了するまで待機する
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        //----- 読み取りロックがされているか
        if (m_readCount.load() > 0) {
            //----- 読み込み数が1以上。読み取りロック（書き込み側のスレッドを寝かす）を行う
            std::unique_lock<std::mutex> lock(m_readMutex);
            m_readCondition.wait(lock, [this] {return m_readCount.load() > 0; });
        }

        //----- 排他データの作成と返却
        return std::move(NonAtomicData<AtomicType>(*m_data,
            [this](void) -> void {}, [this](void) -> void {}));
    }
    // 読み取り専用データを取得する
    // @ Ret  : 排他制御された読み取り専用データ
    template <class AtomicType>
    AtomicReadData<AtomicType> Atomic<AtomicType>::GetReadData(void) {
        //----- 書き込みが終了するまで待機する
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        //----- 排他データの作成と返却
        return std::move(AtomicReadData<AtomicType>(*m_data,
            [this](void) -> void { m_readCount.store(m_readCount.load() + 1); }, [this](void) -> void { m_readCount.store(m_readCount.load() - 1); }));
    }


    // ロックを取得できるか
    // @ Ret  : ロックを取得できる（= ロックされていない）なら true
    template <class AtomicType>
    bool Atomic<AtomicType>::TryLock(void) {
        bool lock = m_mutex.try_lock();
        bool read = m_readMutex.try_lock();
        if (lock) m_mutex.unlock();
        if (read) m_readMutex.unlock();
        return lock && read;
    }
    // 読み取りロックを取得できるか
    // @ Ret  : ロックを取得できる（= ロックされていない）なら true
    template <class AtomicType>
    bool Atomic<AtomicType>::TryReadLock(void) {
        bool lock = m_mutex.try_lock();
        if (lock) m_mutex.unlock();
        return lock;
    }
}

#endif // !I_ATOMIC_H
