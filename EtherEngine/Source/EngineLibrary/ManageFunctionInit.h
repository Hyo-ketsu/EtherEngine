#ifndef I_MANAGEFUNCTIONINIT_H
#define I_MANAGEFUNCTIONINIT_H


//----- 初期化・終了処理定義
namespace EtherEngine {
    class  ManageFunctionInit {
    public:
        // デストラクタ
        ~ManageFunctionInit(void) {}


        void ENGINELIBRARY_API Init(void);
        void ENGINELIBRARY_API Uninit(void);
        
    private:
        // コンストラクタ
        ManageFunctionInit(void) {}
    };
}


#endif // !I_CPPCLIINIT_H
