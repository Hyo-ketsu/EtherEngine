#ifndef I_SINGLETON_H
#define I_SINGLETON_H
#include <Base/AtomicData.h>
#include <Base/AtomicReadData.h>
#include <Base/Atomic.h>
#include <Base/Mutex.h>
#include <Base/SingletonManager.h>
#include <Base/ThreadingUtility.h>


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
        std::weak_ptr<Mutex> GetMutex(void);

    protected:
        // コンストラクタ
        Singleton(void);
        // デストラクタ
        virtual ~Singleton(void) {}

    private:
        std::shared_ptr<Mutex> m_mutex;   // サブクラス用ミューテックス
        static std::shared_ptr<Mutex> ms_updaetrMutex;     // ミューテックス
        static std::unique_ptr<SingletonType> ms_instance; // シングルトンサブクラス
    };
}




//----- Singleton実装
namespace EtherEngine {
    // コンストラクタ
    template<SingletonConcept SingletonType>
    Singleton<SingletonType>::Singleton(void)
        : m_mutex(ThreadingUtility::GetMutex()) {
    }


    // インスタンスの取得
    template<SingletonConcept SingletonType>
    SingletonType* const Singleton<SingletonType>::Get(void) {
        //----- インスタンスの生成判断
        if (!(ms_instance)) {
            //----- ロック
            auto lock = SingletonManager::Get()->GetMutex().lock()->KeyLock();

            //----- インスタンスの生成判断
            if (!(ms_instance)) {
                //----- インスタンスが存在しないため初期化
                ms_updaetrMutex = ThreadingUtility::GetMutex();
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
            []() -> void { ms_updaetrMutex->Lock(); }, [=]() -> void { ms_updaetrMutex->UnLock(); });
    }


    // インスタンスの明示的解放
    template<SingletonConcept SingletonType>
    void Singleton<SingletonType>::DeleteInstance(void) {
        //----- ロック
        auto lock = ms_updaetrMutex->KeyLock();

        //----- 明示的開放
        ms_instance.reset();
    }


    // ミューテックス取得
    template<SingletonConcept SingletonType>
    std::weak_ptr<Mutex> Singleton<SingletonType>::GetMutex(void) {
        return std::weak_ptr<Mutex>(m_mutex);
    }



    template <SingletonConcept SingletonType>
    std::shared_ptr<Mutex> Singleton<SingletonType>::ms_updaetrMutex; // ミューテックス
    template <SingletonConcept SingletonType>
    std::unique_ptr<SingletonType> Singleton<SingletonType>::ms_instance; // シングルトンサブクラス
}


#endif // !I_SINGLETON_H
