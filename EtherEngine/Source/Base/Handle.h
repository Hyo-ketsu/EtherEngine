#ifndef I_HANDLE_H
#define I_HANDLE_H
#include <Base/BaseDefines.h>
#include <Base/EditorException.h>
#include <Base/ExclusionData.h>
#include <Base/ExclusionObject.h>
#include <Base/NonExclusionData.h>
#include <Base/Random.h>


namespace EtherEngine {
    // ハンドル制約（クラスのみ）
    template <typename T>
    concept HandleSystemConcept = std::is_class_v<T>;


    enum class HandleCountType : bool {
        Count = 0,  // 参照カウントを行う
        UnCount,    // 参照カウントを行わない
        None,       // 何も参照がない
    };


    // ハンドルとして使用できるか判定するコンセプト
    // @ Memo : 数値型でない、かつHandleNumberTypeに変換できるか
    template <typename T>
    concept UseHandleConcept = std::is_arithmetic_v<T> && std::is_convertible_v<T, IDNumberType>;
}


//----- Handle宣言
namespace EtherEngine {
    // 対象への参照を数値（ハンドル）として持った型
    // @ Temp1: 管理対象型
    template <HandleSystemConcept Type>
    class Handle {
    public:
        // デフォルトコンストラクタ
        Handle(void);
        // 構築コンストラクタ
        // @ Arg1 : ハンドルとして追加する要素
        Handle(Type&& setItem);
        // デストラクタ
        ~Handle(void);
        // コピーコンストラクタ
        Handle(const Handle<Type>& copy);
        // ムーブコンストラクタ
        // @ Memo : ポインタの移動を行います
        Handle(Handle<Type>&& move);
        // コピー代入
        Handle<Type>& operator =(const Handle<Type>& copy);
        // ムーブ代入
        // @ Memo : ポインタの移動を行います
        Handle<Type>& operator =(Handle<Type>&& move);


        // 参照カウントを行うかゲッター
        HandleCountType GetIsCountUp(void) const { return m_count; }


        // Handleから排他制御されていない要素を取得する
        // @ Ret  : 取得した要素
        NonExclusionData<Type> GetNoAtomicItem(void) const;
        // Handleから排他制御された要素を取得する
        // @ Ret  : 取得した要素
        ExclusionData<Type> GetAtomicItem(void) const;

        // Handleから排他制御されていない要素を直接取得する
        // @ Ret  : 取得した要素
        Type& GetData(void) const;
        // Handleから排他制御された要素を直接取得する
        // @ Ret  : 取得した要素
        Type& GetAtomicData(void) const;


        // 参照ハンドルを取得する
        // @ Ret  : 参照がコピーされたハンドル
        Handle<Type>&& GetHandle(void) const;


        // このHandleはポインタを保持しているか
        bool IsEnable(void) const;
        // このHandleはポインタを保持しているか
        operator bool(void) const;


        // 同じものを指しているハンドルか
        bool operator ==(const Handle<Type>& comparison);
        // 同じものを指していないハンドルか
        bool operator !=(const Handle<Type>& comparison);


        // HandleNumber取得
        IDNumberType GetHandleNumber(void) const;
        // HandleNumber取得
        operator IDNumberType(void) const;

    private:
        IDNumberType m_id; // 自身が保持しているHandle
        HandleCountType m_count;   // カウントアップを行うか
        std::variant<std::shared_ptr<ExclusionObject<std::shared_ptr<Type>>>, std::shared_ptr<ExclusionObject<std::weak_ptr<Type>>>> m_item;    // 保持しているアイテム
    };
}




//----- Handle実装
namespace EtherEngine {
    // デフォルトコンストラクタ
    template <HandleSystemConcept Type>
    Handle<Type>::Handle(void) 
        : m_id(0) 
        , m_count(HandleCountType::None) {
    }
    // コンストラクタ構築
    template <HandleSystemConcept Type>
    Handle<Type>::Handle(Type&& setItem) 
        : m_id(Random::GetRandom<IDNumberType>()) // @ MEMO : 適当に生成している。後で考える
        , m_count(HandleCountType::Count)
        , m_item(std::make_shared<ExclusionObject<std::shared_ptr<Type>>>(std::make_shared<Type>(std::move(setItem)))) {
    }
    // デストラクタ
    template<HandleSystemConcept Type>
    Handle<Type>::~Handle(void) {
    }
    // コピーコンストラクタ
    template<HandleSystemConcept Type>
    Handle<Type>::Handle(const Handle<Type>& copy)
        : m_id(copy.m_id)
        , m_count(copy.m_count)
        , m_item(copy.m_item) {
    }
    // ムーブコンストラクタ
    template<HandleSystemConcept Type>
    Handle<Type>::Handle(Handle<Type>&& move)
        : m_id(move.m_id)
        , m_count(move.m_count)
        , m_item(move.m_item) {
    }
    // コピー代入
    template<HandleSystemConcept Type>
    Handle<Type>& Handle<Type>::operator =(const Handle<Type>& copy) {
        m_id = copy.m_id;
        m_count = copy.m_count;
        m_item = copy.m_item;

        return *this;
    }
    // ムーブ代入
    template<HandleSystemConcept Type>
    Handle<Type>& Handle<Type>::operator =(Handle<Type>&& move) {
        m_id = move.m_id;
        m_count = move.m_count;
        m_item = move.m_item;
        return *this;
    }


    // Handleから排他制御されていない要素を取得する
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    NonExclusionData<Type> Handle<Type>::GetNoAtomicItem(void) const {
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");
        switch (m_item.index()) {
        case 0:
            return NonExclusionData<Type>(*std::get<0>(m_item)->GetNonExclusionData().GetData());
            break;
        case 1:
            return NonExclusionData<Type>(*std::get<1>(m_item)->GetNonExclusionData().GetData().lock());
            break;
        }
    }
    // Handleから排他制御された要素を取得する
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    ExclusionData<Type> Handle<Type>::GetAtomicItem(void) const {
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");
        switch (m_item.index()) {
        case 0: {
            auto&& item = std::get<0>(m_item);
            return ExclusionData<Type>(*item->GetNonExclusionData().GetData(), [&]() { item->Look(); }, [&]() { item->UnLock(); });
            break;
        }
        case 1: {
            auto&& item = std::get<1>(m_item);
            return ExclusionData<Type>(*item->GetNonExclusionData().GetData().lock(), [&]() { item->Look(); }, [&]() { item->UnLock(); });
            break;
        }
        }
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


    // 参照ハンドルを取得する
    template<HandleSystemConcept Type>
    Handle<Type>&& Handle<Type>::GetHandle(void) const {
        //----- 空ハンドルチェック
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");

        //----- 参照を複製して生成
        Handle<Type> ret;
        ret.m_id = this->m_id;
        ret.m_count = HandleCountType::UnCount;
        switch (this->m_item.index()) {
        case 0:
            ret.m_item = std::make_shared<ExclusionObject<std::weak_ptr<Type>>>(std::weak_ptr<Type>(std::get<0>(m_item)->GetNonExclusionData().GetData()));
            break;
        case 1:
            ret.m_item = std::make_shared<ExclusionObject<std::weak_ptr<Type>>>(std::weak_ptr<Type>(std::get<1>(m_item)->GetNonExclusionData().GetData()));
            break;
        }

        //----- 返却
        return std::move(ret);
    }


    // このHandleはポインタを保持しているか
    template<HandleSystemConcept Type>
    bool Handle<Type>::IsEnable(void) const {
        switch (m_item.index()) {
        case std::variant_npos:
            return false;
            break;
        case 0:
            return std::get<0>(m_item)->GetNonExclusionData().GetData() != nullptr;
            break;
        case 1:
            return !(std::get<1>(m_item)->GetNonExclusionData().GetData().expired());
            break;
        } 
    }
    // このHandleはポインタを保持しているか
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
    IDNumberType Handle<Type>::GetHandleNumber(void) const {
        return m_id;
    }
    // HandleNumber取得
    template<HandleSystemConcept Type>
    Handle<Type>::operator IDNumberType(void) const {
        return GetHandleNumber();
    }
}


#endif // !I_HANDLE_H
