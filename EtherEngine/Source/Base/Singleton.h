#ifndef I_SINGLETON_H
#define I_SINGLETON_H
#include <Base/Mutex.h>
#include <Base/ExclusionData.h>
#include <Base/ExclusionObject.h>
#include <Base/CentrallySingleton.h>


//----- Singleton宣言
namespace EtherEngine {
    // クラスのみを表現するコンセプト
    template <typename T>
    concept SingletonConcept = std::is_class_v<T>;


    // Singleton抽象クラス
    // @ Memo : このクラスをフレンド宣言してください
    // @ Memo : protected や private でコンストラクタを宣言してください
    // @ Temp : 返却するクラス
    template<SingletonConcept SingletonType>
    class Singleton {
    public:
        // コピーコンストラクタ
        Singleton<SingletonType>(const Singleton<SingletonType>& copy) = delete;
        // ムーブコンストラクタ
        Singleton<SingletonType>(Singleton<SingletonType>&& move) = delete;
        // コピー代入
        Singleton<SingletonType>& operator=(const Singleton<SingletonType>& copy) = delete;
        // ムーブ代入
        Singleton<SingletonType>& operator=(Singleton<SingletonType>&& move) = delete;


        // インスタンスの取得
        // @ Ret  : 一個しか存在しないことが明確なインスタンス
        static SingletonType* const Get(void);

         
        // インスタンスの明示的解放
        static void DeleteInstance(void);


        // ミューテックス取得
        // @ Ret  : ミューテックス
        Mutex* const GetMutex(void);

    protected:
        // コンストラクタ
        Singleton(void) {}
        // デストラクタ
        virtual ~Singleton(void) {}

    private:
        friend class CentrallySingleton;

        Mutex m_mutex;   // サブクラス用ミューテックス
    };
}




//----- Singleton実装
namespace EtherEngine {
    // インスタンスの取得
    template<SingletonConcept SingletonType>
    SingletonType* const Singleton<SingletonType>::Get(void) {
        return CentrallySingleton::Get()->GetSingleton<SingletonType>();
    }


    // インスタンスの明示的解放
    template<SingletonConcept SingletonType>
    void Singleton<SingletonType>::DeleteInstance(void) {
        CentrallySingleton::Get().DeleteSingleton<SingletonType>();
    }


    // ミューテックス取得
    template<SingletonConcept SingletonType>
    Mutex* const Singleton<SingletonType>::GetMutex(void) {
        return &m_mutex;
    }
}


#endif // !I_SINGLETON_H
