#ifndef I_HANDLESYSTEM_H
#define I_HANDLESYSTEM_H
#include <Base/ConceptUtility.h>
#include <Base/Singleton.h>
#include <Base/Random.h>
#include <Base/ExclusionObject.h>
#include <Base/IDClass.h>


//----- 定数等定義
namespace EtherEngine {
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
        [[nodiscard]] std::pair<IDClass, std::weak_ptr<ullint>> AddItem(Type&& item);
        // 要素を削除する
        // @ Arg1 : 削除する番号
        void DeleteItem(const IDClass& handle);


        // 要素数のカウントアップ
        // @ Arg1 : カウントアップする番号
        void CountUpItem(const IDClass& handle);
        // 要素数のカウントダウン
        // @ Arg1 : カウントダウンする番号
        void CountDownItem(const IDClass& handle);


        // 指定した要素が存在するか
        // @ Ret  : 存在しない若しくは、カウンターが0以下なら false それ以外なら true
        // @ Arg1 : Handle
        bool IsItemEnable(const IDClass& handle) const;


        // Handleから排他制御されていない要素を取得する
        // @ Ret  : 取得した要素（optional）
        // @ Arg1 : Handle
        std::optional<NonExclusionData<Type>> GetNoAtomicItem(const IDClass& handle);
        // Handleから排他制御された要素を取得する
        // @ Ret  : 取得した要素（optional）
        // @ Arg1 : Handle
        std::optional<ExclusionData<Type>> GetAtomicItem(const IDClass& handle);


        // IDから参照数を取得する
        // @ Ret  : 取得した参照数
        // @ Arg1 : ID
        std::weak_ptr<ullint> GetReferenceCount(const IDClass& handle);

    private:
        // コンストラクタ
        HandleSystem(void) {}


        // 参照数が0以下の要素を削除する
        void Delete0ReferenceCounter(const IDClass& handle);


        std::unordered_map<IDClass, ExclusionObject<Type>> m_item;     // 保持している要素の連想配列
        std::unordered_map<IDClass, std::shared_ptr<ullint>> m_referenceCounter;    // 参照数

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
    [[nodiscard]] std::pair<IDClass, std::weak_ptr<ullint>> HandleSystem<Type>::AddItem(Type&& item) {
        //----- ロック
        auto lock = this->GetMutex()->KeySpinLock();

        //----- Handle生成
        auto handle = IDClass();

        //----- 連想配列に格納
        ExclusionObject<Type> atomic(std::move(item));
        m_item.emplace(handle, std::move(atomic));

        //----- 参照カウンタ追加
        auto refCounter = std::make_shared<ullint>(1);
        m_referenceCounter.emplace(handle, refCounter);

        //----- 返却
        return std::pair<IDClass, std::weak_ptr<ullint>>(handle, refCounter);
    }
    // 要素を削除する
    // @ Arg1 : 削除する番号
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::DeleteItem(const IDClass& handle) {
        //----- 存在すれば削除
        if (IsItemEnable(handle)) {
            //----- ロック
            auto lock = this->GetMutex()->KeySpinLock();

            //----- カウントを 0 にし、その後カウント 0 要素を削除
            m_referenceCounter.find(handle)->second = 0;
            Delete0ReferenceCounter(handle);
        }
    }


    // 要素数のカウントアップ
    // @ Arg1 : 削除する番号
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::CountUpItem(const IDClass& handle) {
        auto reference = m_referenceCounter.find(handle);
        if (reference != m_referenceCounter.end()) {
            auto& count = reference->second;
            (*count)++;
        }
    }
    // 要素数のカウントダウン
    // @ Arg1 : 削除する番号
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::CountDownItem(const IDClass& handle) {
        auto reference = m_referenceCounter.find(handle);
        if (reference != m_referenceCounter.end()) {
            auto& count = reference->second;
            (*count)--;
            Delete0ReferenceCounter(handle);
        }
    }


    // 指定した要素が存在するか
    // @ Ret  : 存在しない若しくは、カウンターが0以下なら false それ以外なら true
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    bool HandleSystem<Type>::IsItemEnable(const IDClass& handle) const {
        if (m_item.find(handle) == m_item.end()) return false;
        auto ref = m_referenceCounter.find(handle);
        if (  ref == m_referenceCounter.end()) return false;
        if ((*ref->second.get()) < 1) return false;
        return true;
    }


    // Handleから排他制御されていない要素を取得する
    // @ Ret  : 取得した要素（optional）
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    std::optional<NonExclusionData<Type>> HandleSystem<Type>::GetNoAtomicItem(const IDClass& handle) {
        //----- ロック
        auto lock = this->GetMutex()->KeySpinLock();

        //----- 変数宣言
        auto ret = std::optional<NonExclusionData<Type>>();

        if (IsItemEnable(handle)) {
            //----- 存在する
            ret.emplace(m_item.find(handle)->second.GetNonExclusionData());
        }

        //----- 返却
        return ret;
    }
    // Handleから排他制御された要素を取得する
    // @ Ret  : 取得した要素（optional）
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    std::optional<ExclusionData<Type>> HandleSystem<Type>::GetAtomicItem(const IDClass& handle) {
        //----- ロック
        auto lock = this->GetMutex()->KeySpinLock();

        //----- 変数宣言
        auto ret = std::optional<ExclusionData<Type>>();

        if (IsItemEnable(handle)) {
            //----- 存在する
            ret.emplace(m_item.find(handle)->second.GetData());
        }

        //----- 返却
        return ret;
    }


    // 参照数が0以下の要素を削除する
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::Delete0ReferenceCounter(const IDClass& handle) {
        //----- ロック
        auto lock = this->GetMutex()->KeySpinLock();

        //----- 参照カウンタが0か
        auto find = m_referenceCounter.find(handle);
        if (find != m_referenceCounter.end() && (*find->second) < 1) {
            //----- 1未満。参照カウンタ削除
            m_referenceCounter.erase(find);

            //----- 連想配列の削除用イテレーター
            auto item = m_item.find(handle);

            //----- 連想配列の削除
            if (item != m_item.end()) m_item.erase(item);
        }
    }
    // IDから参照数を取得する
    template <HandleSystemConcept Type>
    std::weak_ptr<ullint> HandleSystem<Type>::GetReferenceCount(const IDClass& handle) {
        //----- ロック
        auto lock = this->GetMutex()->KeySpinLock();

        //----- 変数宣言
        std::weak_ptr<ullint> ret;

        //----- 取得する
        auto find = m_referenceCounter.find(handle);
        if (find == m_referenceCounter.end()) {
            ret = decltype(ret)(find->second);
        }

        //----- 返却
        return ret;
    }
}


#endif // !I_HANDLESYSTEM_H
