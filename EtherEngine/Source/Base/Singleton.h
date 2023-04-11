#ifndef I_SINGLETON_H
#define I_SINGLETON_H


namespace EtherEngine {
    // Singleton抽象クラス
    // @ Memo : このクラスをフレンド宣言してください
    // @ Memo : protected や private でコンストラクタを宣言してください
    // @ Temp : 返却するクラス
    template<class SingletonType>
    class Singleton {
    public:
        Singleton<SingletonType>(const Singleton<SingletonType>&) = delete;
        Singleton<SingletonType>(Singleton<SingletonType>&&) = delete;
        Singleton<SingletonType>& operator=(const Singleton<SingletonType>&) = delete;
        Singleton<SingletonType>& operator=(Singleton<SingletonType>&&) = delete;


        // インスタンスの取得
        // @ Ret  : 一個しか存在しないことが明確なインスタンス
        static SingletonType* const Get(void);

         
        // インスタンスの明示的解放
        static void DeleteInstance(void);

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




// Singleton実装
namespace EtherEngine {
    // インスタンスの取得
    template<class SingletonType>
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


    // インスタンスの明示的解放
    template<class SingletonType>
    void Singleton<SingletonType>::DeleteInstance(void) {
        //----- ロック
        std::lock_guard<decltype(ms_updaetrMutex)> lock(ms_updaetrMutex);

        //----- 明示的開放
        ms_instance.reset();
    }




    template <class SingletonType>
    std::mutex Singleton<SingletonType>::ms_updaetrMutex; // ミューテックス
    template <class SingletonType>
    std::unique_ptr<SingletonType> Singleton<SingletonType>::ms_instance; // シングルトンサブクラス
}


#endif // !I_SINGLETON_H
