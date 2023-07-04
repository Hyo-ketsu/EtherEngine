#ifndef I_HANDLESYSTEM_H
#define I_HANDLESYSTEM_H

#include <Base/ConceptUtility.h>
#include <Base/Singleton.h>
#include <Base/Random.h>
#include <Base/Atomic.h>


//----- 定数等定義
namespace EtherEngine {
    using HandleNumberType = ullint;    // ハンドルとして使用する数値型


    const HandleNumberType NO_CREATE_HANDLE_NUMBER = 0; // ハンドルとして使用しない番号


    // ハンドル制約（クラスのみ）
    template <typename T>
    concept HandleSystemConcept = std::is_class_v<T>;
}


//----- HandleSystem 定義
namespace EtherEngine {
    // Handleで対象物を管理するクラス
    template <HandleSystemConcept Type>
    class HandleSystem : public Singleton<HandleSystem<Type>> {
    public:
        // デストラクタ
        ~HandleSystem(void) override;


        // 要素を追加、Handleを取得する
        // @ Memo : 追加の際は若しくはHandleのコンストラクタご使用ください。
        // @ Ret  : 作成された要素へのHandle
        // @ Arg1 : 追加する要素（右辺値）
        [[nodiscard]] std::pair<HandleNumberType, std::weak_ptr<nullptr_t>> AddItem(Type&& item);
        // 要素を削除する
        // @ Arg1 : 削除する番号
        void DeleteItem(const HandleNumberType& handle);


        // 要素数のカウントアップ
        // @ Arg1 : カウントアップする番号
        void CountUpItem(const HandleNumberType& handle);
        // 要素数のカウントダウン
        // @ Arg1 : カウントダウンする番号
        void CountDownItem(const HandleNumberType& handle);


        // 指定した要素が存在するか
        // @ Ret  : 存在しない若しくは、カウンターが0以下なら false それ以外なら true
        // @ Arg1 : Handle
        bool IsItemEnable(const HandleNumberType& handle) const;


        // Handleから排他制御されていない要素を取得する
        // @ Ret  : 取得した要素（optional）
        // @ Arg1 : Handle
        std::optional<NonAtomicData<Type>> GetNoAtomicItem(const HandleNumberType& handle);
        // Handleから排他制御された要素を取得する
        // @ Ret  : 取得した要素（optional）
        // @ Arg1 : Handle
        std::optional<AtomicData<Type>> GetAtomicItem(const HandleNumberType& handle);
        // Handleから排他制御された読み取り専用要素を取得する
        // @ Ret  : 取得した要素（optional）
        // @ Arg1 : Handle
        std::optional<AtomicReadData<Type>> GetAtomicReadItem(const HandleNumberType& handle);


    private:
        // コンストラクタ
        HandleSystem(void) {}


        // 参照数が0以下の要素を削除する
        void Delete0ReferenceCounter(const HandleNumberType& handle);


        std::unordered_map<HandleNumberType, Atomic<Type>> m_item;     // 保持している要素の連想配列
        std::unordered_map<HandleNumberType, int> m_referenceCounter;  // そのHandleの参照数
        std::vector<std::shared_ptr<nullptr_t>> m_deleteHandle;  // 削除時のカウントダウンを行わないフラグ

        friend class Singleton<HandleSystem<Type>>;
    };
}




//----- HandleSystem 実装
namespace EtherEngine {
    // デストラクタ
    template <HandleSystemConcept Type>
    HandleSystem<Type>::~HandleSystem(void) {
    }


    // 要素を追加、Handleを取得する
    // @ Ret  : 作成された要素へのHandle
    // @ Arg1 : 追加する要素（右辺値）
    template <HandleSystemConcept Type>
    [[nodiscard]] std::pair<HandleNumberType, std::weak_ptr<nullptr_t>> HandleSystem<Type>::AddItem(Type&& item) {
        //----- ロック
        std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

        //----- Handle生成
        HandleNumberType handle = EtherEngine::Random::GetRandom<HandleNumberType>();
        while (true) {
            //----- 存在しているか
            // @ Memo : 単なる番号チェック
            Delete0ReferenceCounter(handle);
            auto item = m_item.find(handle);
            if (handle != NO_CREATE_HANDLE_NUMBER && item == m_item.end()) break;

            //----- 生成
            handle = EtherEngine::Random::GetRandom<HandleNumberType>();
        }

        //----- 連想配列に格納
        Atomic<Type> atomic(item);
        m_item.emplace(handle, std::move(atomic));

        //----- 参照カウンタ追加
        m_referenceCounter.emplace(handle, 1);

        //----- 返却用変数宣言
        m_deleteHandle.push_back(std::make_shared<nullptr_t>(nullptr));
        std::pair<HandleNumberType, std::weak_ptr<nullptr_t>> ret = decltype(ret)(handle, m_deleteHandle.back());

        //----- 返却
        return ret;
    }
    // 要素を削除する
    // @ Arg1 : 削除する番号
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::DeleteItem(const HandleNumberType& handle) {
        //----- 存在すれば削除
        if (IsItemEnable(handle)) {
            //----- ロック
            std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

            //----- カウントを 0 にし、その後カウント 0 要素を削除
            m_referenceCounter.find(handle)->second = 0;
            Delete0ReferenceCounter(handle);
        }
    }


    // 要素数のカウントアップ
    // @ Arg1 : 削除する番号
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::CountUpItem(const HandleNumberType& handle) {
        auto reference = m_referenceCounter.find(handle);
        if (reference != m_referenceCounter.end()) {
            reference->second++;
        }
    }
    // 要素数のカウントダウン
    // @ Arg1 : 削除する番号
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::CountDownItem(const HandleNumberType& handle) {
        auto reference = m_referenceCounter.find(handle);
        if (reference != m_referenceCounter.end()) {
            reference->second--;
            Delete0ReferenceCounter(handle);
        }
    }


    // 指定した要素が存在するか
    // @ Ret  : 存在しない若しくは、カウンターが0以下なら false それ以外なら true
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    bool HandleSystem<Type>::IsItemEnable(const HandleNumberType& handle) const {
        if (m_item.find(handle) == m_item.end()) return false;
        if (m_referenceCounter.find(handle) == m_referenceCounter.end()) return false;
        if (m_referenceCounter.find(handle)->second < 1) return false;
        return true;
    }


    // Handleから排他制御されていない要素を取得する
    // @ Ret  : 取得した要素（optional）
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    std::optional<NonAtomicData<Type>> HandleSystem<Type>::GetNoAtomicItem(const HandleNumberType& handle) {
        //----- ロック
        std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

        //----- 変数宣言
        auto ret = std::optional<NonAtomicData<Type>>();

        if (IsItemEnable(handle)) {
            //----- 存在する
            ret.emplace(m_item.find(handle)->second.GetNonAtomicData());
        }

        //----- 返却
        return ret;
    }
    // Handleから排他制御された要素を取得する
    // @ Ret  : 取得した要素（optional）
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    std::optional<AtomicData<Type>> HandleSystem<Type>::GetAtomicItem(const HandleNumberType& handle) {
        //----- ロック
        std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

        //----- 変数宣言
        auto ret = std::optional<AtomicData<Type>>();

        if (IsItemEnable(handle)) {
            //----- 存在する
            ret.emplace(m_item.find(handle)->second.GetData());
        }

        //----- 返却
        return ret;
    }
    // Handleから排他制御された読み取り専用要素を取得する
    // @ Ret  : 取得した要素（optional）
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    std::optional<AtomicReadData<Type>> HandleSystem<Type>::GetAtomicReadItem(const HandleNumberType& handle) {
        //----- ロック
        std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

        //----- 変数宣言
        auto ret = std::optional<AtomicReadData<Type>>();

        if (IsItemEnable(handle)) {
            //----- 存在する
            ret.emplace(m_item.find(handle)->second.GetReadData());
        }

        //----- 返却
        return ret;
    }


    // 参照数が0以下の要素を削除する
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::Delete0ReferenceCounter(const HandleNumberType& handle) {
        //----- ロック
        std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

        //----- 参照カウンタが0か
        if (m_referenceCounter.find(handle) != m_referenceCounter.end() && m_referenceCounter.find(handle)->second < 1) {
            //----- 1未満。参照カウンタ削除
            m_referenceCounter.erase(m_referenceCounter.find(handle));

            //----- 連想配列の削除用イテレーター
            auto item = m_item.find(handle);

            //----- 連想配列の削除
            if (item != m_item.end()) m_item.erase(item);
        }
    }
}


#endif // !I_HANDLESYSTEM_H
