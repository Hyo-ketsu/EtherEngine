#ifndef I_HANDLE_H
#define I_HANDLE_H
#include <Base/HandleSystem.h>


//----- Handle宣言
namespace EtherEngine {
    enum class HandleCountType {
        Count = 0,      // 参照カウントを行う
        UnCount = 1,    // 参照カウントを行わない
    };


    // 対象への参照を数値（ハンドル）として持った型
    // @ Temp1: 管理対象型
    // @ Temp2: 参照カウントアップを行うか(デフォルト : 行う)
    template <HandleSystemConcept Type, HandleCountType Count = HandleCountType::Count>
    class Handle {
    public:
        // コンストラクタ
        // @ Arg1 : 生成番号
        Handle(const HandleNumberType& handleNumber);
        // コンストラクタ
        Handle(void);
        // デストラクタ
        ~Handle(void);
        // コピーコンストラクタ
        Handle(const Handle<Type, Count>& copy);
        // 代入演算子(Copy)
        Handle<Type, Count>& operator=(const Handle<Type, Count>& copy);
        // 代入演算子(Move)
        Handle<Type, Count>& operator=(Handle<Type, Count>&& move);


        // このハンドルが指すものを削除する
        void Delete(void);
        // このハンドルの参照を削除する
        void DeleteRef(void);


        // Handleから排他制御されていない要素を取得する
        // @ Ret  : 取得した要素（optional）
        NonAtomicData<Type> GetNoAtomicItem(void) const;
        // Handleから排他制御された要素を取得する
        // @ Ret  : 取得した要素（optional）
        AtomicData<Type> GetAtomicItem(void) const;
        // Handleから排他制御された読み取り専用要素を取得する
        // @ Ret  : 取得した要素（optional）
        AtomicReadData<Type> GetAtomicReadItem(void) const;

        // Handleから排他制御されていない要素を直接取得する
        // @ Ret  : 取得した要素（optional）
        Type& GetNoAtomicData(void) const;
        // Handleから排他制御された要素を直接取得する
        // @ Ret  : 取得した要素（optional）
        Type& GetAtomicData(void) const;
        // Handleから排他制御された読み取り専用要素を直接取得する
        // @ Ret  : 取得した要素（optional）
        Type& GetAtomicReadData(void) const;


        // このHandleの保持している番号は有効か
        // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
        bool GetEnable(void) const;
        // このHandleの保持している番号は有効か
        // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
        operator bool(void) const;


        // 同じものを指しているハンドルか
        bool operator ==(const Handle<Type, Count>& comparison);
        // 同じものを指していないハンドルか
        bool operator !=(const Handle<Type, Count>& comparison);


        // HandleNumber取得
        HandleNumberType GetHandleNumberType(void) const;
        // HandleNumber取得
        operator HandleNumberType(void) const;

    private:
        // 参照のカウントアップを行う
        void CountUp(void);

        HandleNumberType m_handle; // 自身が保持しているHandle
    };


    // 参照ハンドル
    // @ Memo : 参照カウントを行わない
    template <typename T>
    using RefHandle = Handle<T, HandleCountType::UnCount>;

    // ハンドルクラスか判定するコンセプト
    // @ Memo : ハンドルクラスであれば true
    template <typename T, typename Type> 
    concept HandleConcept = std::is_same_v<T, Handle<Type, HandleCountType::Count>> || std::is_same_v<T, Handle<Type, HandleCountType::UnCount>>;
    // ハンドルが参照カウントを行うか判別するコンセプト
    // @ Memo : ハンドルクラス、かつカウントタイプが同じであれば true
    template <typename T, typename Type, HandleCountType Count>
    concept HandleCountTypeConcept = HandleConcept<T, Type>&& std::is_same_v<T, Handle<Type, Count>>;
}




//----- Handle実装
namespace EtherEngine {
    // コンストラクタ
    // @ Arg1 : 生成番号
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>::Handle(const HandleNumberType& handleNumber)
        : m_handle(handleNumber) {
        
    }
    // コンストラクタ
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>::Handle(void)
        : Handle(0) {
        if constexpr (HandleCountType::Count == Count) {
            HandleSystem<Type>::Get()->CountDownItem(m_handle);
        }
    }
    // デストラクタ
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>::~Handle(void) {
        HandleSystem<Type>::Get()->CountDownItem(m_handle);
    }
    // コピーコンストラクタ
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>::Handle(const Handle<Type, Count>& copy)
        : m_handle(copy.m_handle){
        HandleSystem<Type>::Get()->CountUpItem(m_handle);
    }
    // 代入演算子(Copy)
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>& Handle<Type, Count>::operator=(const Handle<Type, Count>& copy) {
        m_handle = copy.m_handle;

    }
    // 代入演算子(Move)
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>& Handle<Type, Count>::operator=(Handle<Type, Count>&& move) {
        m_handle = move.m_handle;

        HandleSystem<Type>::Get()->CountUpItem(m_handle);
        return *this;
    }


    // このハンドルが指すものを削除する
    template<HandleSystemConcept Type, HandleCountType Count>
    void Handle<Type, Count>::Delete(void) {
        HandleSystem<Type>::Get()->DeleteItem(m_handle);
    }
    // このハンドルの参照を削除する
    template<HandleSystemConcept Type, HandleCountType Count>
    void Handle<Type, Count>::DeleteRef(void) {

    }


    // Handleから排他制御されていない要素を取得する
    // @ Ret  : 取得した要素（optional）
    template<HandleSystemConcept Type, HandleCountType Count>
    NonAtomicData<Type> Handle<Type, Count>::GetNoAtomicItem(void) const {
        return HandleSystem<Type>::Get()->GetNoAtomicItem(m_handle).value();
    }
    // Handleから排他制御された要素を取得する
    // @ Ret  : 取得した要素（optional）
    template<HandleSystemConcept Type, HandleCountType Count>
    AtomicData<Type> Handle<Type, Count>::GetAtomicItem(void) const {
        return HandleSystem<Type>::Get()->GetAtomicItem(m_handle).value();
    }
    // Handleから排他制御された読み取り専用要素を取得する
    // @ Ret  : 取得した要素（optional）
    template<HandleSystemConcept Type, HandleCountType Count>
    AtomicReadData<Type> Handle<Type, Count>::GetAtomicReadItem(void) const {
        return HandleSystem<Type>::Get()->GetAtomicReadItem(m_handle).value();
    }

    // Handleから排他制御されていない要素を直接取得する
    // @ Ret  : 取得した要素（optional）
    template<HandleSystemConcept Type, HandleCountType Count>
    Type& Handle<Type, Count>::GetNoAtomicData(void) const {
        return GetNoAtomicItem().GetData();
    }
    // Handleから排他制御された要素を直接取得する
    // @ Ret  : 取得した要素（optional）
    template<HandleSystemConcept Type, HandleCountType Count>
    Type& Handle<Type, Count>::GetAtomicData(void) const {
        return GetAtomicItem().GetData();
    }
    // Handleから排他制御された読み取り専用要素を直接取得する
    // @ Ret  : 取得した要素（optional）
    template<HandleSystemConcept Type, HandleCountType Count>
    Type& Handle<Type, Count>::GetAtomicReadData(void) const {
        return GetAtomicReadItem().GetData();
    }


    // このHandleの保持している番号は有効か
    // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
    template<HandleSystemConcept Type, HandleCountType Count>
    bool Handle<Type, Count>::GetEnable(void) const {
        return !(HandleSystem<Type>::Get()->IsItemEnable(m_handle));
    }
    // このHandleの保持している番号は有効か
    // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>::operator bool(void) const {
        GetEnable();
    }


    // 同じものを指しているハンドルか
    template<HandleSystemConcept Type, HandleCountType Count>
    bool Handle<Type, Count>::operator ==(const Handle<Type, Count>& comparison) {
        return comparison == m_handle;
    }
    // 同じものを指していないハンドルか
    template<HandleSystemConcept Type, HandleCountType Count>
    bool Handle<Type, Count>::operator !=(const Handle<Type, Count>& comparison) {
        return comparison != m_handle;
    }


    // HandleNumber取得
    template<HandleSystemConcept Type, HandleCountType Count>
    HandleNumberType Handle<Type, Count>::GetHandleNumberType(void) const {
        return m_handle;
    }
    // HandleNumber取得
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>::operator HandleNumberType(void) const {
        return GetHandleNumberType();
    }


    // 参照のカウントアップを行う
    template<HandleSystemConcept Type, HandleCountType Count>
    void Handle<Type, Count>::CountUp(void) {
        if constexpr (HandleCountType::Count == Count) {
            HandleSystem<Type>::Get()->CountUpItem(m_handle);
        }
    }
}


#endif // !I_HANDLE_H
