#ifndef I_HANDLE_H
#define I_HANDLE_H
#include <Base/HandleSystem.h>


namespace EtherEngine {
    enum class HandleCountType {
        Count = 0,      // 参照カウントを行う
        UnCount = 1,    // 参照カウントを行わない
    };


    // ハンドルとして使用できるか判定するコンセプト
    // @ Memo : 数値型でない、かつHandleNumberTypeに変換できるか
    template <typename T>
    concept UseHandleConcept = std::is_arithmetic_v<T> && std::is_convertible_v<T, HandleNumberType>;
}


//----- Handle宣言
namespace EtherEngine {
    // 対象への参照を数値（ハンドル）として持った型
    // @ Temp1: 管理対象型
    template <HandleSystemConcept Type>
    class BaseHandle {
    public:
        // コンストラクタ
        // @ Arg1 : 生成番号
        // @ Arg2 : 生成数をカウントするか
        BaseHandle(const HandleNumberType& handleNumber, HandleCountType countType);
        // コンストラクタ
        BaseHandle(void);
        // デストラクタ
        ~BaseHandle(void);
        // コピーコンストラクタ
        BaseHandle(const BaseHandle<Type>& copy);
        // 代入演算子(Copy)
        BaseHandle<Type>& operator=(const BaseHandle<Type>& copy);
        // 代入演算子(Move)
        BaseHandle<Type>& operator=(BaseHandle<Type>&& move);


        // このハンドルが指すものを削除する
        void Delete(void);
        // このハンドルの参照を削除する
        void DeleteRef(void);


        // Handleから排他制御されていない要素を取得する
        // @ Ret  : 取得した要素
        NonAtomicData<Type> GetNoAtomicItem(void) const;
        // Handleから排他制御された要素を取得する
        // @ Ret  : 取得した要素
        AtomicData<Type> GetAtomicItem(void) const;
        // Handleから排他制御された読み取り専用要素を取得する
        // @ Ret  : 取得した要素
        AtomicReadData<Type> GetAtomicReadItem(void) const;

        // Handleから排他制御されていない要素を直接取得する
        // @ Ret  : 取得した要素
        Type& GetNoAtomicData(void) const;
        // Handleから排他制御された要素を直接取得する
        // @ Ret  : 取得した要素
        Type& GetAtomicData(void) const;
        // Handleから排他制御された読み取り専用要素を直接取得する
        // @ Ret  : 取得した要素
        Type& GetAtomicReadData(void) const;


        // このHandleの保持している番号は有効か
        // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
        bool GetEnable(void) const;
        // このHandleの保持している番号は有効か
        // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
        operator bool(void) const;


        // 同じものを指しているハンドルか
        bool operator ==(const BaseHandle<Type>& comparison);
        // 同じものを指していないハンドルか
        bool operator !=(const BaseHandle<Type>& comparison);


        // HandleNumber取得
        HandleNumberType GetHandleNumberType(void) const;
        // HandleNumber取得
        operator HandleNumberType(void) const;


        // 参照カウントを行うかゲッター
        bool GetIsCountUp(void) const { return m_isCount; }

    protected:
        // 参照のカウントアップを行う
        // @ Memo : 判定も行う
        void CountUp(void);
        // 参照のカウントダウンも行う
        // @ Memo : 判定も行う
        void CountDown(void);

        HandleNumberType m_handle; // 自身が保持しているHandle
        bool m_isCount;          // カウントアップを行うか
    };
}




//----- Handle宣言
namespace EtherEngine {
    // 参照カウントを行うハンドル
    template <HandleSystemConcept Type>
    class Handle : public BaseHandle<Type> {
    public:
        // コンストラクタ
        // @ Arg1 : 生成番号
        Handle(const HandleNumberType& handleNumber);
    };
}
//----- RefHandle宣言
namespace EtherEngine {
    // 参照カウントを行わないハンドル
    template <HandleSystemConcept Type>
    class RefHandle : public BaseHandle<Type> {
    public:
        // コンストラクタ
        // @ Arg1 : 生成番号
        RefHandle(const HandleNumberType& handleNumber);
    };
}




//----- Handle実装
namespace EtherEngine {
    // コンストラクタ
    // @ Arg1 : 生成番号
    // @ Arg2 : 生成数をカウントするか
    template <HandleSystemConcept Type>
    BaseHandle<Type>::BaseHandle(const HandleNumberType& handleNumber, HandleCountType countType)
        : m_handle(handleNumber) {
        switch (countType) {
        case HandleCountType::Count:
            m_isCount = true;
            break;
        case HandleCountType::UnCount:
            m_isCount = false;
            break;
        }

        CountUp();
    }
    // コンストラクタ
    template<HandleSystemConcept Type>
    BaseHandle<Type>::BaseHandle(void)
        : BaseHandle(NO_CREATE_HANDLE_NUMBER, HandleCountType::UnCount) {
    }
    // デストラクタ
    template<HandleSystemConcept Type>
    BaseHandle<Type>::~BaseHandle(void) {
        CountDown();
    }
    // コピーコンストラクタ
    template<HandleSystemConcept Type>
    BaseHandle<Type>::BaseHandle(const BaseHandle<Type>& copy)
        : m_handle(copy.m_handle) 
        , m_isCount(copy.m_isCount) {
        CountUp();
    }
    // 代入演算子(Copy)
    template<HandleSystemConcept Type>
    BaseHandle<Type>& BaseHandle<Type>::operator=(const BaseHandle<Type>& copy) {
        m_handle = copy.m_handle;
        m_isCount = copy.m_isCount; 
        CountUp();
        return *this;
    }
    // 代入演算子(Move)
    template<HandleSystemConcept Type>
    BaseHandle<Type>& BaseHandle<Type>::operator=(BaseHandle<Type>&& move) {
        m_handle = move.m_handle;
        m_isCount = move.m_isCount;

        CountUp();
        return *this;
    }


    // このハンドルが指すものを削除する
    template<HandleSystemConcept Type>
    void BaseHandle<Type>::Delete(void) {
        HandleSystem<Type>::Get()->DeleteItem(m_handle);
    }
    // このハンドルの参照を削除する
    template<HandleSystemConcept Type>
    void BaseHandle<Type>::DeleteRef(void) {
        CountDown();
        m_handle = NO_CREATE_HANDLE_NUMBER;
    }


    // Handleから排他制御されていない要素を取得する
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    NonAtomicData<Type> BaseHandle<Type>::GetNoAtomicItem(void) const {
        return HandleSystem<Type>::Get()->GetNoAtomicItem(m_handle).value();
    }
    // Handleから排他制御された要素を取得する
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    AtomicData<Type> BaseHandle<Type>::GetAtomicItem(void) const {
        return HandleSystem<Type>::Get()->GetAtomicItem(m_handle).value();
    }
    // Handleから排他制御された読み取り専用要素を取得する
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    AtomicReadData<Type> BaseHandle<Type>::GetAtomicReadItem(void) const {
        return HandleSystem<Type>::Get()->GetAtomicReadItem(m_handle).value();
    }

    // Handleから排他制御されていない要素を直接取得する
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    Type& BaseHandle<Type>::GetNoAtomicData(void) const {
        return GetNoAtomicItem().GetData();
    }
    // Handleから排他制御された要素を直接取得する
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    Type& BaseHandle<Type>::GetAtomicData(void) const {
        return GetAtomicItem().GetData();
    }
    // Handleから排他制御された読み取り専用要素を直接取得する
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    Type& BaseHandle<Type>::GetAtomicReadData(void) const {
        return GetAtomicReadItem().GetData();
    }


    // このHandleの保持している番号は有効か
    // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
    template<HandleSystemConcept Type>
    bool BaseHandle<Type>::GetEnable(void) const {
        return HandleSystem<Type>::Get()->IsItemEnable(m_handle);
    }
    // このHandleの保持している番号は有効か
    // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
    template<HandleSystemConcept Type>
    BaseHandle<Type>::operator bool(void) const {
        GetEnable();
    }


    // 同じものを指しているハンドルか
    template<HandleSystemConcept Type>
    bool BaseHandle<Type>::operator ==(const BaseHandle<Type>& comparison) {
        return comparison == m_handle;
    }
    // 同じものを指していないハンドルか
    template<HandleSystemConcept Type>
    bool BaseHandle<Type>::operator !=(const BaseHandle<Type>& comparison) {
        return comparison != m_handle;
    }


    // HandleNumber取得
    template<HandleSystemConcept Type>
    HandleNumberType BaseHandle<Type>::GetHandleNumberType(void) const {
        return m_handle;
    }
    // HandleNumber取得
    template<HandleSystemConcept Type>
    BaseHandle<Type>::operator HandleNumberType(void) const {
        return GetHandleNumberType();
    }


    // 参照のカウントアップを行う
    template<HandleSystemConcept Type>
    void BaseHandle<Type>::CountUp(void) {
        if (m_isCount) {
            HandleSystem<Type>::Get()->CountUpItem(m_handle);
        }
    }
    // 参照のカウントダウンを行う
    template<HandleSystemConcept Type>
    void BaseHandle<Type>::CountDown(void) {
        if (m_isCount) {
            HandleSystem<Type>::Get()->CountDownItem(m_handle);
        }
    }
}


//----- Handle実装
namespace EtherEngine {
    // コンストラクタ
    // @ Arg1 : 生成番号
    template <HandleSystemConcept Type>
    Handle<Type>::Handle(const HandleNumberType& handleNumber)   
        : BaseHandle<Type>(handleNumber, HandleCountType::Count) {
    }
}
//----- RefHandle実装
namespace EtherEngine {
    // コンストラクタ
    // @ Arg1 : 生成番号
    template <HandleSystemConcept Type>
    RefHandle<Type>::RefHandle(const HandleNumberType& handleNumber)
        : BaseHandle<Type>(handleNumber, HandleCountType::UnCount) {
    }
}


#endif // !I_HANDLE_H
