#ifndef I_GAMEAPPLICATION_H
#define I_GAMEAPPLICATION_H
#include <DirectX/DirectX.h>
#include <EngineLibrary/BaseMainWindow.h>

#pragma unmanaged

namespace EtherEngine {
    // ゲームアプリケーションを表現するクラス
    class ENGINELIBRARY_API GameApplication : public BaseMainWindow, public Singleton<GameApplication> {
    public:
        // デストラクタ
        ~GameApplication(void);

    protected:
        // メイン関数
        void MainFunction(void) override;

    private:
        // コンストラクタ
        GameApplication(void);

        friend class Singleton<GameApplication>;
    };
}
#pragma managed
//----- Wrapper
namespace EtherEngine {
    namespace Wrapper {
        //----- エディターのアプリケーション
        public ref class GameApplication {
        public:
            // エディターを終了させる
            static property bool IsGameLoop {
                void set(bool value) {
                    EtherEngine::GameApplication::Get()->SetIsGameLoop(value);
                }
            }
        };
    }
}


#endif // !I_GAMEAPPLICATION_H
