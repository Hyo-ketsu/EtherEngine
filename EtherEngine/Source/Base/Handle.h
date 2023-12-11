#ifndef I_HANDLE_H
#define I_HANDLE_H
#include <Base/HandleSystem.h>
#include <Base/EditorException.h>
#include <Base/IDClass.h>


namespace EtherEngine {
    enum class HandleCountType : bool {
        Count = 0,      // 参照カウントを行う
        UnCount,    // 参照カウントを行わない
    };


    // ハンドルとして使用できるか判定するコンセプト
    // @ Memo : 数値型でない、かつHandleNumberTypeに変換できるか
    template <typename T>
    concept UseHandleConcept = std::is_arithmetic_v<T> && std::is_convertible_v<T, IDClass>;
}


//----- Handle宣言
namespace EtherEngine {
    // 対象への参照を数値（ハンドル）として持った型
    // @ Temp1: 管理対象型
    template <HandleSystemConcept Type>
    class Handle {
    public:
        // コンストラクタ構築
        // @ Arg1 : ハンドルとして追加する要素
        // @ Arg2 : 生成数をカウントするか(Default : カウントする)
        Handle(Type&& item, HandleCountType countType = HandleCountType::Count);
        // ID構築コンストラクタ
        // @ Arg1 : コピーするID
        // @ Arg2 : 生成数をカウントするか(Default : カウントする)
        Handle(IDClass id, HandleCountType countType = HandleCountType::Count);
        // コンストラクタ
        // @ Arg1 : 生成数をカウントするか(Default : カウントする)
        Handle(HandleCountType countType = HandleCountType::Count);
        // デストラクタ
        ~Handle(void);
        // コピーコンストラクタ
        Handle(const Handle<Type>& copy);
        // ムーブコンストラクタ
        Handle(Handle<Type>&& move);
        // コピー代入
        Handle<Type>& operator =(const Handle<Type>& copy);
        // ムーブ代入
        Handle<Type>& operator =(Handle<Type>&& move);


        // 参照カウントを行うかゲッター
        HandleCountType GetIsCountUp(void) const { return m_count; }


        // 参照ハンドルを作成する
        // @ Ret  : 参照ハンドル
        Handle<Type> GetRefHandle(void);


        // このハンドルが指すものを削除する
        void Delete(void);


        // Handleから排他制御されていない要素を取得する
        // @ Ret  : 取得した要素
        NonAtomicData<Type> GetNoAtomicItem(void) const;
        // Handleから排他制御された要素を取得する
        // @ Ret  : 取得した要素
        AtomicData<Type> GetAtomicItem(void) const;

        // Handleから排他制御されていない要素を直接取得する
        // @ Ret  : 取得した要素
        Type& GetData(void) const;
        // Handleから排他制御された要素を直接取得する
        // @ Ret  : 取得した要素
        Type& GetAtomicData(void) const;


        // このHandleの保持している番号は有効か
        // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
        bool IsEnable(void) const;
        // このHandleの保持している番号は有効か
        // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
        operator bool(void) const;


        // 同じものを指しているハンドルか
        bool operator ==(const Handle<Type>& comparison);
        // 同じものを指していないハンドルか
        bool operator !=(const Handle<Type>& comparison);


        // HandleNumber取得
        IDClass GetHandleNumber(void) const;
        // HandleNumber取得
        operator IDClass(void) const;

    protected:
        // 参照のカウントアップを行う
        // @ Memo : 判定も行う
        void CountUp(void);
        // 参照のカウントダウンも行う
        // @ Memo : 判定も行う
        void CountDown(void);

        IDClass m_id; // 自身が保持しているHandle
        HandleCountType m_count;   // カウントアップを行うか
        std::weak_ptr<ullint> m_deleteHandle;    // HandleSystem削除時にHandleSystemを使用するか
    };
}




//----- Handle実装
namespace EtherEngine {
    // コンストラクタ構築
    // @ Arg1 : ハンドルとして追加する要素
    // @ Arg2 : 生成数をカウントするか
    template <HandleSystemConcept Type>
    Handle<Type>::Handle(Type&& item, HandleCountType countType)
        : Handle(countType) {
        //----- ハンドルとして構築
        auto handle = HandleSystem<Type>::Get()->AddItem(std::move(item));

        //----- メンバ初期化
        m_id = handle.first;
        m_deleteHandle = handle.second;
    }
    // ID構築コンストラクタ
    // @ Arg1 : コピーするID
    // @ Arg2 : 生成数をカウントするか(Default : true)
    template <HandleSystemConcept Type>
    Handle<Type>::Handle(IDClass id, HandleCountType countType) 
        : Handle(countType) {
        //----- メンバ初期化
        m_id = id;
        m_deleteHandle = HandleSystem<Type>::Get()->GetReferenceCount(m_id);
    }
    // コンストラクタ構築
    // @ Arg1 : 生成数をカウントするか
    template <HandleSystemConcept Type>
    Handle<Type>::Handle(HandleCountType countType) 
        : m_count(countType) {
        //----- カウントアップ
        CountUp();
    }
    // デストラクタ
    template<HandleSystemConcept Type>
    Handle<Type>::~Handle(void) {
        CountDown();
    }
    // コピーコンストラクタ
    template<HandleSystemConcept Type>
    Handle<Type>::Handle(const Handle<Type>& copy)
        : m_id(copy.m_id) 
        , m_count(copy.m_count) 
        , m_deleteHandle(copy.m_deleteHandle) {
        CountUp();
    }
    // ムーブコンストラクタ
    template<HandleSystemConcept Type>
    Handle<Type>::Handle(Handle<Type>&& move)
        : m_id(move.m_id)
        , m_count(move.m_count)
        , m_deleteHandle(move.m_deleteHandle) {
        CountUp();
    }
    // コピー代入
    template<HandleSystemConcept Type>
    Handle<Type>& Handle<Type>::operator =(const Handle<Type>& copy) {
        m_id = copy.m_id;
        m_count = copy.m_count;
        m_deleteHandle = copy.m_deleteHandle;
        CountUp();
    }
    // ムーブ代入
    template<HandleSystemConcept Type>
    Handle<Type>& Handle<Type>::operator =(Handle<Type>&& move) {
        m_id = move.m_id;
        m_count = move.m_count;
        m_deleteHandle = move.m_deleteHandle;
        CountUp();
    }


    // 参照ハンドルを作成する
    // @ Ret  : 参照ハンドル
    template<HandleSystemConcept Type>
    Handle<Type> Handle<Type>::GetRefHandle(void) {
        return Handle(m_id, HandleCountType::UnCount);
    }


    // このハンドルが指すものを削除する
    template<HandleSystemConcept Type>
    void Handle<Type>::Delete(void) {
        HandleSystem<Type>::Get()->DeleteItem(m_id);
    }


    // Handleから排他制御されていない要素を取得する
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    NonAtomicData<Type> Handle<Type>::GetNoAtomicItem(void) const {
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");
        return HandleSystem<Type>::Get()->GetNoAtomicItem(m_id).value();
    }
    // Handleから排他制御された要素を取得する
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    AtomicData<Type> Handle<Type>::GetAtomicItem(void) const {
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");
        return HandleSystem<Type>::Get()->GetAtomicItem(m_id).value();
    }


    // Handleから排他制御されていない要素を直接取得する
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    Type& Handle<Type>::GetData(void) const {
        return GetNoAtomicItem().GetData();
    }
    // Handleから排他制御された要素を直接取得する
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    Type& Handle<Type>::GetAtomicData(void) const {
        return GetAtomicItem().GetData();
    }


    // このHandleの保持している番号は有効か
    // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
    template<HandleSystemConcept Type>
    bool Handle<Type>::IsEnable(void) const {
        return HandleSystem<Type>::Get()->IsItemEnable(m_id);
    }
    // このHandleの保持している番号は有効か
    // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
    template<HandleSystemConcept Type>
    Handle<Type>::operator bool(void) const {
        return IsEnable();
    }


    // 同じものを指しているハンドルか
    template<HandleSystemConcept Type>
    bool Handle<Type>::operator ==(const Handle<Type>& comparison) {
        return comparison.GetHandleNumber() == m_id;
    }
    // 同じものを指していないハンドルか
    template<HandleSystemConcept Type>
    bool Handle<Type>::operator !=(const Handle<Type>& comparison) {
        return comparison.GetHandleNumber() != m_id;
    }


    // HandleNumber取得
    template<HandleSystemConcept Type>
    IDClass Handle<Type>::GetHandleNumber(void) const {
        return m_id;
    }
    // HandleNumber取得
    template<HandleSystemConcept Type>
    Handle<Type>::operator IDClass(void) const {
        return GetHandleNumber();
    }


    // 参照のカウントアップを行う
    template<HandleSystemConcept Type>
    void Handle<Type>::CountUp(void) {
        if (m_count == HandleCountType::Count && m_deleteHandle.expired() == false) {
            HandleSystem<Type>::Get()->CountUpItem(m_id);
        }
    }
    // 参照のカウントダウンを行う
    template<HandleSystemConcept Type>
    void Handle<Type>::CountDown(void) {
        if (m_count == HandleCountType::Count && m_deleteHandle.expired() == false) {
            HandleSystem<Type>::Get()->CountDownItem(m_id);
        }
    }
}


#endif // !I_HANDLE_H
