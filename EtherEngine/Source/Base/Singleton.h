#ifndef I_SINGLETON_H
#define I_SINGLETON_H
#include <Base/AtomicData.h>
#include <Base/AtomicReadData.h>


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
        // インスタンスの取得
        // @ Memo : 取得と同時に読み取りロックを取得する
        // @ Ret  : 一個しか存在しないことが明確なインスタンス
        static AtomicData<SingletonType* const> GetLock(void);

         
        // インスタンスの明示的解放
        static void DeleteInstance(void);


        // ミューテックス取得
        // @ Ret  : ミューテックス
        std::recursive_mutex& GetMutex(void);

    protected:
        // コンストラクタ
        Singleton(void) {}
        // デストラクタ
        virtual ~Singleton(void) {}


        std::recursive_mutex m_mutex;   // サブクラス用ミューテックス

    private:
        static std::mutex ms_updaetrMutex;                 // ミューテックス
        static std::unique_ptr<SingletonType> ms_instance; // シングルトンサブクラス
    };
}




//----- Singleton実装
namespace EtherEngine {
    // インスタンスの取得
    template<SingletonConcept SingletonType>
    SingletonType* const Singleton<SingletonType>::Get(void) {
        //----- インスタンスの生成判断
        if (!(ms_instance)) {
            //----- ロック
            std::lock_guard<decltype(ms_updaetrMutex)> lock(ms_updaetrMutex);

            //----- インスタンスの生成判断
            if (!(ms_instance)) {
                //----- インスタンスが存在しないため生成
                ms_instance = std::unique_ptr<SingletonType>(new SingletonType());
            }
        }

        //----- インスタンスの返却
        return ms_instance.get();
    }
    // インスタンスの取得
    template<SingletonConcept SingletonType>
    AtomicData<SingletonType* const> Singleton<SingletonType>::GetLock(void) {
        return AtomicData<SingletonType *const>(Get(),
            []() -> void { ms_updaetrMutex.lock(); }, [=]() -> void { ms_updaetrMutex.unlock(); });
    }


    // インスタンスの明示的解放
    template<SingletonConcept SingletonType>
    void Singleton<SingletonType>::DeleteInstance(void) {
        //----- ロック
        std::lock_guard<decltype(ms_updaetrMutex)> lock(ms_updaetrMutex);

        //----- 明示的開放
        ms_instance.reset();
    }


    // ミューテックス取得
    template<SingletonConcept SingletonType>
    std::recursive_mutex& Singleton<SingletonType>::GetMutex(void) {
        return m_mutex;
    }



    template <SingletonConcept SingletonType>
    std::mutex Singleton<SingletonType>::ms_updaetrMutex; // ミューテックス
    template <SingletonConcept SingletonType>
    std::unique_ptr<SingletonType> Singleton<SingletonType>::ms_instance; // シングルトンサブクラス
}


#endif // !I_SINGLETON_H
