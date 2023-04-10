#ifndef I_GAMEAPPLICATION_H
#define I_GAMEAPPLICATION_H
#include <DirectX/DirectX.h>


namespace EtherEngine {
    const std::string WINDOW_CLASS_NAME = "Game";   // メインウィンドウ名


    // ゲームアプリケーションを表現するクラス
    class GameApplication {
    public:
        // コンストラクタ
        GameApplication(void);


        // メイン関数
        virtual void MainFunction(void);


        // ウィンドウハンドルゲッター
        const HWND& GetHWND(void) const { return m_hwnd.value(); }
        // ウィンドウハンドルセッター
        void SetHWND(HWND in) { m_hwnd.emplace(in); }

        // ウィンドウサイズゲッター
        const Eigen::Array2<int>& GetWindSize(void) const { return m_windowSize; }
        // ウィンドウサイズセッター
        void SetWindSize(const Eigen::Array2<int>& in) { m_windowSize = in; }

        // HInstanceゲッター
        const HINSTANCE& GetHInstance(void) const { return m_hInstance.value(); }
        // IpCmdLineゲッター
        const LPSTR& GetIpCmdLine(void) const { return m_ipCmdLine.value(); }
        // CmdShowゲッター
        const int& GetCmdShow(void) const { return m_cmdShow.value(); }

        // DirectXゲッター
        const DirectXRender& GetDirectX(void) const { return m_dxRender; }


        // WinMain の引数を保持する
        void SetApplicationData(const HINSTANCE hInstace, const LPSTR ipCmdLine, const int& cmdShow);



    protected:
        std::optional<HWND> m_hwnd; // ウィンドウハンドル
        Eigen::Array2<int>  m_windowSize; // ウィンドウのサイズ
        std::optional<HINSTANCE> m_hInstance;  // インスタンスハンドル
        std::optional<LPSTR>     m_ipCmdLine;  // コマンドライン
        std::optional<int>       m_cmdShow;    // アプリケーションの初期表示方法
        DirectXRender            m_dxRender;
    };
}


#endif // !I_GAMEAPPLICATION_H
