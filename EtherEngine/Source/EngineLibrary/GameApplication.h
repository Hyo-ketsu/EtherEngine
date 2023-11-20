#ifndef I_GAMEAPPLICATION_H
#define I_GAMEAPPLICATION_H
#include <DirectX/DirectX.h>
#include <EngineLibrary/BaseMainWindow.h>


namespace EtherEngine {
    // ゲームアプリケーションを表現するクラス
    class GameApplication : public BaseMainWindow, public Singleton<GameApplication> {
    public:
        // デストラクタ
        ~GameApplication(void);

    protected:
        // メイン関数
        void MainFunction(void) override;

    private:
        // コンストラクタ
        GameApplication(void);
    };
}


#endif // !I_GAMEAPPLICATION_H
