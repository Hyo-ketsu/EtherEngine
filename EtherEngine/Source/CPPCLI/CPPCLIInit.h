#ifndef I_CPPCLIINIT_H
#define I_CPPCLIINIT_H


//----- 初期化・終了処理定義
namespace EtherEngine {
    class CPPCLI {
    public:
        // デストラクタ
        ~CPPCLI(void) {}


        static void Init(void);
        static void Uninit(void);

    private:
        // コンストラクタ
        CPPCLI(void) {}
    };
}


#endif // !I_CPPCLIINIT_H
