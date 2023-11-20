#ifndef I_CPPCLIINIT_H
#define I_CPPCLIINIT_H


//----- 初期化・終了処理定義
namespace EtherEngine {
    class EngineLibrary {
    public:
        // デストラクタ
        ~EngineLibrary(void) {}


        static void Init(void);
        static void Uninit(void);

    private:
        // コンストラクタ
        EngineLibrary(void) {}
    };
}


#endif // !I_CPPCLIINIT_H
