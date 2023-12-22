#ifndef I_EXCLUSIONOBJECT_H
#define I_EXCLUSIONOBJECT_H
#include <Base/ExclusionData.h>
#include <Base/NonExclusionData.h>
#include <Base/Mutex.h>


//----- ExclusionObject 宣言
namespace EtherEngine {
    // 排他制御を行うクラス
    // @ Temp : 排他を行う型
    template <class AtomicType>
    class ExclusionObject {
    public:
        ExclusionObject(const ExclusionObject&) = delete;


        // デフォルトコンストラクタ
        ExclusionObject(void);
        // コンストラクタ
        // @ Arg1 : 排他を行う情報
        ExclusionObject(AtomicType&& data);
        // デストラクタ
        ~ExclusionObject(void) noexcept;
        // ムーブコンストラクタ
        // @ Memo : 所有権の移動を表現しています
        ExclusionObject(ExclusionObject&& move) noexcept;


        // データを取得する
        // @ Ret  : 排他制御されたデータ
        ExclusionData<AtomicType> GetData(void);
        // データを取得する
        // @ Ret  : 排他制御されていないデータ
        NonExclusionData<AtomicType> GetNonExclusionData(void);


        // ロックを取得できるか
        // @ Ret  : ロックを取得できる（= ロックされていない）なら true
        bool TryLock(void);

    private:
        std::unique_ptr<AtomicType> m_lock;  // 保持しているデータ
        Mutex m_mutex; // 排他用ミューテックス
    };
}




//----- ExclusionObject 実装
namespace EtherEngine {
    // デフォルトコンストラクタ
    template <class AtomicType>
    ExclusionObject<AtomicType>::ExclusionObject(void)
        : m_lock(nullptr){
    }
    // コンストラクタ
    // @ Arg1 : 排他を行う情報
    template <class AtomicType>
    ExclusionObject<AtomicType>::ExclusionObject(AtomicType&& data) 
        : m_lock(std::make_unique<AtomicType>(data)){
    }
    // デストラクタ
    template <class AtomicType>
    ExclusionObject<AtomicType>::~ExclusionObject(void) noexcept {
    }
    // ムーブコンストラクタ
    // @ Memo : 所有権の移動を表現しています
    template <class AtomicType>
    ExclusionObject<AtomicType>::ExclusionObject(ExclusionObject&& move) noexcept {
        //----- ロックを行う
        auto lock = move.m_mutex.KeyLock();

        //----- ムーブ
        m_lock = std::move(move.m_lock);
    }


    // データを取得する
    // @ Ret  : 排他制御されたデータ
    template <class AtomicType>
    ExclusionData<AtomicType> ExclusionObject<AtomicType>::GetData(void) {
        //----- 排他データの作成と返却
        return std::move(ExclusionData<AtomicType>(*m_lock,
            [this](void) -> void { m_mutex.Lock(); }, [this](void) -> void { m_mutex.UnLock(); }));
    }
    // データを取得する
    // @ Ret  : 排他制御されていないデータ
    template <class AtomicType>
    NonExclusionData<AtomicType> ExclusionObject<AtomicType>::GetNonExclusionData(void) {
        //----- 排他データの作成と返却
        return std::move(NonExclusionData<AtomicType>(*m_lock));
    }


    // ロックを取得できるか
    // @ Ret  : ロックを取得できる（= ロックされていない）なら true
    template <class AtomicType>
    bool ExclusionObject<AtomicType>::TryLock(void) {
        bool lock = m_mutex.IsCanLock();
        return lock;
    }
}

#endif // !I_EXCLUSIONOBJECT_H
