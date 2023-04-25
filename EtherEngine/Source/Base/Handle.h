#ifndef I_HANDLE_H
#define I_HANDLE_H
#include <Base/HandleSystem.h>



//----- Handle宣言
namespace EtherEngine {
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
        // 代入演算子(Move)
        Handle<Type>& operator=(Handle<Type>&& move);


        // このハンドルが指すものを削除する
        void Delete(void);


        // コンストラクタ処理セッター
        // @ Memo : 初期化のみ可
        void SetConstructor(std::function<void(void)> in) { if (m_constructor == nullptr) m_constructor = in; }
        // デストラクタ処理セッター
        // @ Memo : 初期化のみ可
        void SetDestructor(std::function<void(void)> in) { if (m_destructor == nullptr) m_destructor = in; }


        // Handleから排他制御されていない要素を取得する
        // @ Ret  : 取得した要素（optional）
        std::optional<NonAtomicData<Type>> GetNoAtomicItem(void) const;
        // Handleから排他制御された要素を取得する
        // @ Ret  : 取得した要素（optional）
        std::optional<AtomicData<Type>> GetAtomicItem(void) const;
        // Handleから排他制御された読み取り専用要素を取得する
        // @ Ret  : 取得した要素（optional）
        std::optional<AtomicReadData<Type>> GetAtomicReadItem(void) const;


        // このHandleの保持している番号は有効か
        // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
        bool GetEnable(void) const;
        // このHandleの保持している番号は有効か
        // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
        operator bool(void) const;


        // HandleNumber取得
        operator HandleNumberType(void) const;

    private:
        std::optional<HandleNumberType> m_handle; // 自身が保持しているHandle
        std::function<void(void)> m_constructor;  // 初期化処理
        std::function<void(void)> m_destructor;   // 終了時処理
    };
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
    // 代入演算子(Move)
    template<HandleSystemConcept Type>
    Handle<Type>& Handle<Type>::operator=(Handle<Type>&& move) {
        m_handle = move.m_handle;
        m_constructor = move.m_constructor;
        m_destructor = move.m_destructor;

        if (m_constructor != nullptr) m_constructor();
    }


    // このハンドルが指すものを削除する
    template<HandleSystemConcept Type>
    void Handle<Type>::Delete(void) {
        HandleSystem<Type>::Get()->DeleteItem(m_handle);
    }


    // Handleから排他制御されていない要素を取得する
    // @ Ret  : 取得した要素（optional）
    template<HandleSystemConcept Type>
    std::optional<NonAtomicData<Type>> Handle<Type>::GetNoAtomicItem(void) const {
        return HandleSystem<Type>::Get()->GetNoAtomicItem(m_handle);
    }
    // Handleから排他制御された要素を取得する
    // @ Ret  : 取得した要素（optional）
    template<HandleSystemConcept Type>
    std::optional<AtomicData<Type>> Handle<Type>::GetAtomicItem(void) const {
        return HandleSystem<Type>::Get()->GetAtomicItem(m_handle);
    }
    // Handleから排他制御された読み取り専用要素を取得する
    // @ Ret  : 取得した要素（optional）
    template<HandleSystemConcept Type>
    std::optional<AtomicReadData<Type>> Handle<Type>::GetAtomicReadItem(void) const {
        return HandleSystem<Type>::Get()->GetAtomicReadItem(m_handle);
    }


    // このHandleの保持している番号は有効か
    // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
    template<HandleSystemConcept Type>
    bool Handle<Type>::GetEnable(void) const {
        return !(m_handle.has_value() && HandleSystem<Type>::Get()->IsItemEnable(m_handle.value()));
    }
    // このHandleの保持している番号は有効か
    // @ Ret  : 既にHandleSystemで削除された値若しくは無効値なら false
    template<HandleSystemConcept Type>
    Handle<Type>::operator bool(void) const {
        GetEnable();
    }


    // HandleNumber取得
    template<HandleSystemConcept Type>
    Handle<Type>::operator HandleNumberType(void) const {
        return m_handle.value();
    }
}


#endif // !I_HANDLE_H
