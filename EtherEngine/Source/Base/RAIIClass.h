#ifndef I_RAIICLASS_H
#define I_RAIICLASS_H


//----- RAIIClass 実装
namespace EtherEngine {
    // コンストラクタ、デストラクタで指定した処理を行うクラス
    class RAIIClass {
    public:
        // コンストラクタ
        // @ Arg1 : コンストラクタ処理
        // @ Arg2 : デストラクタ処理
        RAIIClass(std::function<void(void)> init, std::function<void(void)> unInit);
        // デストラクタ
        ~RAIIClass(void);
        RAIIClass(const RAIIClass& copy) = delete;
        RAIIClass(RAIIClass&& move) = delete;

    private:
        std::function<void(void)> m_unInit; // 終了時に行う処理
    };
}


#endif // !I_RAIICLASS_H
