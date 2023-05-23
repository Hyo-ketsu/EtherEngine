#ifndef I_GAMEAPPLICATION_H
#define I_GAMEAPPLICATION_H
#include <Base/InitUninitPerformer.h>
#include <DirectX/DirectX.h>
#include <DirectX/Window.h>


namespace EtherEngine {
    const std::string WINDOW_CLASS_NAME = "Game";   // メインウィンドウ名


    // ゲームアプリケーションを表現するクラス
    class GameApplication : public Window {
    public:
        // コンストラクタ
        GameApplication(void);
        // デストラクタ
        ~GameApplication(void);


        // メイン関数
        virtual void MainFunction(void);


        // このクラスの初期化前に追加で行う初期化処理
        virtual void InitFirst(void) {}
        // このクラスの初期化後に追加で行う初期化処理
        virtual void InitLast(void) {}
        // 初期化処理後に追加で行う初期化処理
        virtual void InitLateFuntion(void) {}

        // このクラスの描画処理の前に行う処理
        virtual void DrawFirst(void) {}
        // このクラスの描画処理の後に行う処理
        virtual void DrawLast(void) {}


        // HInstanceゲッター
        const HINSTANCE& GetHInstance(void) const { return m_hInstance.value(); }
        // IpCmdLineゲッター
        const LPSTR& GetIpCmdLine(void) const { return m_ipCmdLine.value(); }
        // CmdShowゲッター
        const int& GetCmdShow(void) const { return m_cmdShow.value(); }

        // DirectXゲッター
        const Handle<DirectXRender>& GetDirectX(void) const { return m_dxRender; }


        // WinMain の引数を保持する
        void SetApplicationData(const HINSTANCE hInstace, const LPSTR ipCmdLine, const int& cmdShow);

    protected:
        std::optional<HINSTANCE> m_hInstance;  // インスタンスハンドル
        std::optional<LPSTR>     m_ipCmdLine;  // コマンドライン
        std::optional<int>       m_cmdShow;    // アプリケーションの初期表示方法
        Handle<DirectXRender>    m_dxRender;

        InitUninitPerformer m_initUninitPerformer;  // 初期化・終了処理実行クラス
    };
}


#endif // !I_GAMEAPPLICATION_H
