#ifndef I_HANDLESYSTEM_H
#define I_HANDLESYSTEM_H
#include <Base/Singleton.h>
#include <Base/Random.h>
#include <Base/Atomic.h>


//----- Handle宣言
namespace EtherEngine {
    using HandleNumberType = unsigned long long;


    // クラスのみ制約
    template <typename T>
    concept HandleSystemConcept = std::is_class_v<T>;


    // Handle
    // @ Temp : 管理対象型
    template <HandleSystemConcept Type>
    class Handle {
    public:
        // コンストラクタ
        // @ Arg1 : 生成番号
        Handle(HandleNumberType handleNumber);
        // デストラクタ
        ~Handle(void);
        // コピーコンストラクタ
        Handle(const Handle<Type>& copy);
        // 代入演算子(Copy)
        Handle<Type>& operator=(const Handle<Type>& copy);


        // コンストラクタ処理セッター
        // @ Memo : 初期化のみ可
        void SetConstructor(std::function<void(void)> in) { if (m_constructor == nullptr) m_constructor = in; }
        // デストラクタ処理セッター
        // @ Memo : 初期化のみ可
        void SetDestructor(std::function<void(void)> in) { if (m_destructor == nullptr) m_destructor = in; }


        // Handleから要素を取得、排他制御を行う
        // @ Memo : Handleが無効化されている、存在しない場合に例外を吐きます
        // @ Ret  : 取得した要素
        AtomicData<Type> GetAtomicItem(void) const;
        // Handleから要素を取得
        // @ Memo : Handleが無効化されている、存在しない場合に例外を吐きます
        // @ Ret  : 取得した要素
        NonAtomicData<Type> GetNonAtomicItem(void) const;
        // Handleから読み取り専用要素を取得する
        // @ Memo : Handleが無効化されている、存在しない場合に例外を吐きます
        // @ Ret  : 取得した要素
        AtomicData<Type> GetAtomicItem(void) const;
        // Handleがロックを行えるか
        // @ Ret  : ロックが行える(= ロックされていない)か
        // @ Memo : 読み取りロックか(Default : false)
        bool IsLock(const bool& isReadLock) const;


        // このHandleが有効か
        // @ Ret  : このHandle自体、Handleの参照先が有効かをそれぞれ判別
        bool IsEnable(void) const;
        // このHandleが有効か
        // @ Ret  : このHandle自体、Handleの参照先が有効かをそれぞれ判別
        explicit operator bool(void) const;


        // 参照を無効化する
        void Destroy(void);


        // 比較
        bool operator ==(const Handle<Type>& handle) const;

    private:
        std::optional<HandleNumberType> m_handle;      // 自身が保持しているHandle
        std::function<void(void)>       m_constructor; // 初期化処理
        std::function<void(void)>       m_destructor;  // 終了時処理
    };
}




//----- HandleSystem 定義
namespace EtherEngine {
    // Handleで対象物を管理するクラス
    // @ Temp : 管理対象型
    template <HandleSystemConcept Type>
    class HandleSystem : public Singleton<HandleSystem<Type>> {
    public:
        // 要素を追加、Handleを取得する
        // @ Ret  : 作成された要素へのHandle
        // @ Arg1 : 追加する要素（右辺値）
        Handle<Type> AddItem(Type&& item);


        // 指定した要素が存在するか
        // @ Ret  : 存在しない若しくは、カウンターが0以下なら false それ以外なら true
        // @ Arg1 : Handle
        bool IsItemEnable(const Handle<Type>& handle) const;


        // Handleから排他制御されていない要素を取得する
        // @ Ret  : 取得した要素（optional）
        // @ Arg1 : Handle
        std::optional<NonAtomicData<Type>> GetNoAtomicItem(const Handle<Type>& handle);
        // Handleから排他制御された要素を取得する
        // @ Ret  : 取得した要素（optional）
        // @ Arg1 : Handle
        std::optional<AtomicData<Type>> GetAtomicItem(const Handle<Type>& handle);
        // Handleから排他制御された読み取り専用要素を取得する
        // @ Ret  : 取得した要素（optional）
        // @ Arg1 : Handle
        std::optional<AtomicReadData<Type>> GetAtomicReadItem(const Handle<Type>& handle);

    private:
        // コンストラクタ
        HandleSystem(void) {}


        // 参照数が0以下の要素を削除する
        void Delete0ReferenceCounter(const Handle<Type>& handle);


        std::unordered_map<Handle<Type>, Atomic<Type>> m_item; // 保持している要素の連想配列
        std::unordered_map<Handle<Type>, int> m_referenceCounter;  // そのHandleの参照数

        friend class Singleton<HandleSystem<Type>>;
    };


    // HandleClass ショートカット
    template <HandleSystemConcept Type>
    using UseHandle = HandleSystem<Type>::Handle<Type>;
}




//----- Handle実装
namespace EtherEngine {
    // コンストラクタ
    // @ Arg1 : 生成番号
    template<HandleSystemConcept Type>
    Handle<Type>::Handle(HandleNumberType handleNumber)
        : m_handle(handleNumber)
        , m_constructor(nullptr)
        , m_destructor(nullptr) {
    }
    // デストラクタ
    template<HandleSystemConcept Type>
    Handle<Type>::~Handle(void) {
        if (m_destructor != nullptr) m_destructor();
    }
    // コピーコンストラクタ
    template<HandleSystemConcept Type>
    Handle<Type>::Handle(const Handle<Type>& copy)
        : m_handle(copy.m_handle)
        , m_constructor(copy.m_constructor)
        , m_destructor(copy.m_destructor) {
        if (m_constructor != nullptr) m_constructor();
    }
    // 代入演算子(Copy)
    template<HandleSystemConcept Type>
    Handle<Type>& Handle<Type>::operator=(const Handle<Type>& copy) {
        m_handle = copy.m_handle;
        m_constructor = copy.m_constructor;
        m_destructor = copy.m_destructor;

        if (m_constructor != nullptr) m_constructor();
    }


    // Handleから要素を取得、排他制御を行う
    // @ Memo : Handleが無効化されている、存在しない場合に例外を吐きます
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    AtomicData<Type> Handle<Type>::GetAtomicItem(void) const {
        if (IsEnable() == false) throw std::runtime_error("A Handle does not hold an element");
        // TODO : もれなく循環参照かまして死ぬ。やっぱHandleSystem.hに統合する？
    }
    // Handleから要素を取得
    // @ Memo : Handleが無効化されている、存在しない場合に例外を吐きます
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    NonAtomicData<Type> Handle<Type>::GetNonAtomicItem(void) const {
        if (IsEnable() == false) throw std::runtime_error("A Handle does not hold an element");
        // TODO : もれなく循環参照かまして死ぬ。やっぱHandleSystem.hに統合する？
    }
    // Handleから読み取り専用要素を取得する
    // @ Memo : Handleが無効化されている、存在しない場合に例外を吐きます
    // @ Ret  : 取得した要素
    template<HandleSystemConcept Type>
    AtomicData<Type> Handle<Type>::GetAtomicItem(void) const {
        if (IsEnable() == false) throw std::runtime_error("A Handle does not hold an element");
        // TODO : もれなく循環参照かまして死ぬ。やっぱHandleSystem.hに統合する？
    }
    // Handleがロックを行えるか
    // @ Ret  : ロックが行える(= ロックされていない)か
    // @ Memo : 読み取りロックか(Default : false)
    template<HandleSystemConcept Type>
    bool Handle<Type>::IsLock(const bool& isReadLock) const {
        // TODO : もれなく循環参照かまして死ぬ。やっぱHandleSystem.hに統合する？
    }


    // このHandleが有効か
    // @ Ret  : このHandle自体、Handleの参照先が有効かをそれぞれ判別
    template<HandleSystemConcept Type>
    bool Handle<Type>::IsEnable(void) const {
        
        return m_handle.has_value() && HandleSystem<Type>:: IsItemEnable(*this);
    }
    // このHandleが有効か
    // @ Ret  : このHandle自体、Handleの参照先が有効かをそれぞれ判別
    template<HandleSystemConcept Type>
    Handle<Type>::operator bool(void) const {
        return IsEnable();
    }
    // 参照を無効化する
    template<HandleSystemConcept Type>
    void Handle<Type>::Destroy(void) {
        m_handle.reset();
    }


    // 比較
    template<HandleSystemConcept Type>
    bool Handle<Type>::operator ==(const Handle<Type>& handle) const {
        //----- 無効値判定
        if (this->IsEnable() == false) return false;
        if (handle.IsEnable() == false) return false;

        //----- Handleの比較
        return m_handle.value() == handle.m_handle.value();
    }
}




//----- HandleSystem実装
namespace EtherEngine {
    // 要素を追加、Handleを取得する
    // @ Ret  : 作成された要素へのHandle
    // @ Arg1 : 追加する要素（右辺値）
    template <HandleSystemConcept Type>
    Handle<Type> HandleSystem<Type>::AddItem(Type&& item) {
        //----- ロック
        std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

        //----- Handle生成
        Handle<Type> handle = Handle<Type>(EtherEngine::Random::GetRandom<HandleNumberType>());
        while (true) {
            //----- 存在しているか
            // @ Memo : 単なる番号チェック
            Delete0ReferenceCounter(handle);
            auto item = m_item.find(handle);
            if (item == m_item.end()) break;

            //----- 生成
            handle = Handle<Type>(EtherEngine::Random::GetRandom<HandleNumberType>());
        }

        //----- 参照を連想配列に格納
        m_item.emplace(handle, item);
        
        //----- 参照カウンタ追加
        m_referenceCounter.emplace(handle, 1);

        //----- コールバック登録
        handle.SetConstructor();

        //----- 返却
        return handle;
    }


    // 指定した要素が存在するか
    // @ Ret  : 存在しない若しくは、カウンターが0以下なら false それ以外なら true
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    bool HandleSystem<Type>::IsItemEnable(const Handle<Type>& handle) const {
        if (m_item.find(handle) == m_item.end()) return false;
        if (m_referenceCounter.find(handle) == m_referenceCounter.end()) return false;
        if (m_referenceCounter.find(handle)->second > 0) return false;
        return true;
    }


    // Handleから排他制御されていない要素を取得する
    // @ Ret  : 取得した要素（optional）
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    std::optional<NonAtomicData<Type>> HandleSystem<Type>::GetNoAtomicItem(const Handle<Type>& handle) {
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
    std::optional<AtomicData<Type>> HandleSystem<Type>::GetAtomicItem(const Handle<Type>& handle) {
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
    std::optional<AtomicReadData<Type>> HandleSystem<Type>::GetAtomicReadItem(const Handle<Type>& handle) {
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
    void HandleSystem<Type>::Delete0ReferenceCounter(const Handle<Type>& handle) {
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
