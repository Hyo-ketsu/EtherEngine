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
        // デフォルトコンストラクタ
        ExclusionObject(void);
        // コンストラクタ
        // @ Arg1 : 排他を行う情報
        ExclusionObject(AtomicType&& data);
        // デストラクタ
        ~ExclusionObject(void) noexcept;
        // コピーコンストラクタ
        ExclusionObject(const ExclusionObject& copy) = delete;
        // ムーブコンストラクタ
        ExclusionObject(ExclusionObject&& move) = default;
        // コピー代入
        ExclusionObject& operator =(const ExclusionObject& copy) = delete;
        // ムーブ代入
        ExclusionObject& operator =(ExclusionObject&& move) = default;


        // データを取得する
        // @ Ret  : 排他制御されたデータ
        ExclusionData<AtomicType> GetData(void) const;
        // データを取得する
        // @ Ret  : 排他制御されていないデータ
        NonExclusionData<AtomicType> GetNonExclusionData(void) const;


        // ロックを取得できるか
        // @ Ret  : ロックを取得できる（= ロックされていない）なら true
        bool TryLock(void) const;
        // ロックする
        void Look(void) const;
        // アンロックする
        void UnLock(void) const;

    private:
        std::shared_ptr<AtomicType> m_lock;  // 保持しているデータ
        Mutex m_mutex; // 排他用ミューテックス
    };
}




//----- ExclusionObject 実装
namespace EtherEngine {
    // デフォルトコンストラクタ
    template <class AtomicType>
    ExclusionObject<AtomicType>::ExclusionObject(void)
        : m_lock(nullptr) {
    }
    // コンストラクタ
    // @ Arg1 : 排他を行う情報
    template <class AtomicType>
    ExclusionObject<AtomicType>::ExclusionObject(AtomicType&& data) 
        : m_lock(std::make_shared<AtomicType>(data)) {
    }
    // デストラクタ
    template <class AtomicType>
    ExclusionObject<AtomicType>::~ExclusionObject(void) noexcept {
    }


    // データを取得する
    // @ Ret  : 排他制御されたデータ
    template <class AtomicType>
    ExclusionData<AtomicType> ExclusionObject<AtomicType>::GetData(void) const {
        //----- 排他データの作成と返却
        return std::move(ExclusionData<AtomicType>(*m_lock,
            [this](void) -> void { m_mutex.Lock(); }, [this](void) -> void { m_mutex.UnLock(); }));
    }
    // データを取得する
    // @ Ret  : 排他制御されていないデータ
    template <class AtomicType>
    NonExclusionData<AtomicType> ExclusionObject<AtomicType>::GetNonExclusionData(void) const {
        //----- 排他データの作成と返却
        return std::move(NonExclusionData<AtomicType>(*m_lock));
    }


    // ロックを取得できるか
    // @ Ret  : ロックを取得できる（= ロックされていない）なら true
    template <class AtomicType>
    bool ExclusionObject<AtomicType>::TryLock(void) const {
        bool lock = m_mutex.IsCanLock();
        return lock;
    }
    // ロックする
    template <class AtomicType>
    void ExclusionObject<AtomicType>::Look(void) const {
        m_mutex.Lock();
    }
    template <class AtomicType>
    // アンロックする
    void ExclusionObject<AtomicType>::UnLock(void) const {
        m_mutex.UnLock();
    }
}

#endif // !I_EXCLUSIONOBJECT_H
