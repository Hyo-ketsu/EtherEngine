#ifndef I_HANDLERAPPER_H
#define I_HANDLERAPPER_H
#include <Base/Handle.h>
#include <Base/HandleHelper.h>


//----- HandleRapper宣言
namespace EtherEngine {
    // ラップできる型
    // @ Memo : 同型でない、かつキャストできる
    template <typename T, typename U>
    concept HandleCovertConcept = !(std::is_same_v<U, T>) && std::is_convertible_v<U, T>;


    // キャストして使用したいハンドルをラップするクラス
    // @ Temp : キャスト先
    template <HandleSystemConcept Type>
    class HandleRapper {
    public:
        // コンストラクタ
        // @ Temp : キャスト先の型
        // @ Arg1 : 保持するハンドル
        template <HandleCovertConcept<Type> BaseType>
        HandleRapper(const BaseHandle<BaseType>& handle);
        // コンストラクタ
        // @ Temp : キャスト先の型
        // @ Arg1 : 保持するハンドル
        template <HandleCovertConcept<Type> BaseType>
        HandleRapper(BaseHandle<BaseType>&& handle);
        // デストラクタ
        ~HandleRapper(void);
        // コピーコンストラクタ
        HandleRapper(const HandleRapper& copy) = default;
        // ムーブコンストラクタ
        HandleRapper(HandleRapper&& move) = default;

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

    private:
        Handle<Type> m_handle;  // 保持しているハンドル
    };
}




//----- HandleRapper実装
namespace EtherEngine {
    // コンストラクタ
    // @ Temp : キャスト先の型
    // @ Arg1 : 保持するハンドル
    template <HandleSystemConcept Type>
    template <HandleCovertConcept<Type> BaseType>
    HandleRapper<Type>::HandleRapper(const BaseHandle<BaseType>& handle) {

    }
    // コンストラクタ
    // @ Temp : キャスト先の型
    // @ Arg1 : 保持するハンドル
    template <HandleSystemConcept Type>
    template <HandleCovertConcept<Type> BaseType>
    HandleRapper<Type>::HandleRapper(BaseHandle<BaseType>&& handle) {

    }
    // デストラクタ
    template <HandleSystemConcept Type>
    HandleRapper<Type>::~HandleRapper(void) {

    }


    // Handleから排他制御されていない要素を取得する
    // @ Ret  : 取得した要素
    template <HandleSystemConcept Type>
    NonAtomicData<Type> HandleRapper<Type>::GetNoAtomicItem(void) const {
        NonAtomicData<Type>() m_handle.GetAtomicItem()
    }
    // Handleから排他制御された要素を取得する
    // @ Ret  : 取得した要素
    template <HandleSystemConcept Type>
    AtomicData<Type> HandleRapper<Type>::GetAtomicItem(void) const {
        AtomicData<Type>()
    }
    // Handleから排他制御された読み取り専用要素を取得する
    // @ Ret  : 取得した要素
    template <HandleSystemConcept Type>
    AtomicReadData<Type> HandleRapper<Type>::GetAtomicReadItem(void) const {

    }

    // Handleから排他制御されていない要素を直接取得する
    // @ Ret  : 取得した要素
    template <HandleSystemConcept Type>
    Type& HandleRapper<Type>::GetNoAtomicData(void) const {

    }
    // Handleから排他制御された要素を直接取得する
    // @ Ret  : 取得した要素
    template <HandleSystemConcept Type>
    Type& HandleRapper<Type>::GetAtomicData(void) const {

    }
    // Handleから排他制御された読み取り専用要素を直接取得する
    // @ Ret  : 取得した要素
    template <HandleSystemConcept Type>
    Type& HandleRapper<Type>::GetAtomicReadData(void) const {

    }
}


#endif // !I_HANDLERAPPER_H
