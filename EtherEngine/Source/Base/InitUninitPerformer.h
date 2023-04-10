#ifndef I_INITUNINITPERFORMER_H
#define I_INITUNINITPERFORMER_H


namespace EtherEngine {
    // Init,Uninitが存在するかのコンセプト


    // 指定順に初期化処理、終了処理を行う
    class InitUninitPerformer {
    public:
        // 初期化処理、終了処理の追加
        // @ Arg1 : 初期化処理
        // @ Arg2 : 終了処理
        void AddInitUninit(std::function<void(void)> init, std::function<void(void)> uninit);
        // 指定クラスの参照を渡し、自動でInit,Unintiを行う
        // @ Arg1 : Init,Uninitが定義されたクラスの参照
        template <typename InitUninitType>
        requires requires(InitUninitType instans) {
            instans.Init();
            instans.Uninit();
        }
        void AddInitUninit(InitUninitType* classRef);


        // 初期化処理実行
        void Init(void);
        // 終了処理実行
        void UnInit(void);

    private:
        std::deque<std::function<void(void)>> m_init;   // 初期化関数
        std::deque<std::function<void(void)>> m_uninit; // 終了関数
    };
}




//----- InitUninitPerformer実装
namespace EtherEngine {
    // @ Arg1 : Init,Uninitが定義されたクラスの参照
    template <typename InitUninitType>
        requires requires(InitUninitType instans) {
        instans.Init();
        instans.Uninit();
    }
    void InitUninitPerformer::AddInitUninit(InitUninitType* classRef) {
        m_init.push_front([=](void) { classRef->Init(); });
        m_uninit.push_back([=](void) mutable { classRef->Uninit(); });
    }
}



#endif // !I_INITUNINITPERFORMER_H
