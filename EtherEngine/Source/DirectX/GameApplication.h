#ifndef I_GAMEAPPLICATION_H
#define I_GAMEAPPLICATION_H
#include <DirectX/DirectX.h>
#include <DirectX/BaseMainWindow.h>


namespace EtherEngine {
    // ゲームアプリケーションを表現するクラス
    class GameApplication : public BaseMainWindow<GameApplication> {
    public:
        // コンストラクタ
        GameApplication(void);
        // デストラクタ
        ~GameApplication(void);


        // メイン関数
        void MainFunction(void) override;
    };
}


#endif // !I_GAMEAPPLICATION_H
