#ifndef I_ATOMIC_H
#define I_ATOMIC_H
#include <Base/AtomicData.h>
#include <Base/NonAtomicData.h>
#include <Base/ThreadingUtility.h>
#include <Base/Mutex.h>


namespace EtherEngine {
    // 排他制御を行うクラス
    // @ Temp : 排他を行う型
    template <class AtomicType>
    class Atomic {
    public:
        Atomic(const Atomic&) = delete;


        // デフォルトコンストラクタ
        Atomic(void);
        // コンストラクタ
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


        // ロックを取得できるか
        // @ Ret  : ロックを取得できる（= ロックされていない）なら true
        bool TryLock(void);

    private:
        std::unique_ptr<AtomicType> m_lock;  // 保持しているデータ
        Mutex m_mutex; // 排他用ミューテックス
    };
}




//----- Atomic実装
namespace EtherEngine {
    // デフォルトコンストラクタ
    template <class AtomicType>
    Atomic<AtomicType>::Atomic(void)
        : m_lock(nullptr){
    }
    // コンストラクタ
    // @ Arg1 : 排他を行う情報
    template <class AtomicType>
    Atomic<AtomicType>::Atomic(AtomicType&& data) 
        : m_lock(std::make_unique<AtomicType>(data)){
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
        auto lock = move.m_mutex.KeyLock();

        //----- ムーブ
        m_lock = std::move(move.m_lock);
    }


    // データを取得する
    // @ Ret  : 排他制御されたデータ
    template <class AtomicType>
    AtomicData<AtomicType> Atomic<AtomicType>::GetData(void) {
        //----- 排他データの作成と返却
        return std::move(AtomicData<AtomicType>(*m_lock,
            [this](void) -> void { m_mutex.Lock(); }, [this](void) -> void { m_mutex.UnLock(); }));
    }
    // データを取得する
    // @ Ret  : 排他制御されていないデータ
    template <class AtomicType>
    NonAtomicData<AtomicType> Atomic<AtomicType>::GetNonAtomicData(void) {
        //----- 排他データの作成と返却
        return std::move(NonAtomicData<AtomicType>(*m_lock));
    }


    // ロックを取得できるか
    // @ Ret  : ロックを取得できる（= ロックされていない）なら true
    template <class AtomicType>
    bool Atomic<AtomicType>::TryLock(void) {
        bool lock = m_mutex.IsCanLock();
        return lock;
    }
}

#endif // !I_ATOMIC_H
