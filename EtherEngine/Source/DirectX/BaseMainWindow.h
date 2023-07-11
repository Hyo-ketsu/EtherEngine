#ifndef I_BASEMAINWINDOW_G
#define I_BASEMAINWINDOW_G
#include <Base/Singleton.h>
#include <Base/InitUninitPerformer.h>
#include <DirectX/Window.h>
#include <DirectX/DirectX.h>


//----- BaseMainWindow宣言
namespace EtherEngine {
    // 起動から終了まで存在しているウィンドウ
    template <typename Type>
    class BaseMainWindow : public Window, public Singleton<Type> {
    public:
        using Window::Window;


        // HInstanceゲッター
        const HINSTANCE& GetHInstance(void) const { return m_hInstance.value(); }
        // IpCmdLineゲッター
        const LPSTR& GetIpCmdLine(void) const { return m_ipCmdLine.value(); }
        // CmdShowゲッター
        const int& GetCmdShow(void) const { return m_cmdShow.value(); }

        // DirectXゲッター
        const BaseHandle<DirectXRender>& GetDirectX(void) const { return m_dxRender; }


        // メイン関数
        virtual void MainFunction(void) = 0;


        // WinMain の引数を保持する
        void SetApplicationData(const HINSTANCE hInstace, const LPSTR ipCmdLine, const int& cmdShow);

    protected:
        std::optional<HINSTANCE> m_hInstance;  // インスタンスハンドル
        std::optional<LPSTR>     m_ipCmdLine;  // コマンドライン
        std::optional<int>       m_cmdShow;    // アプリケーションの初期表示方法
        BaseHandle<DirectXRender> m_dxRender;
        InitUninitPerformer m_initUninitPerformer;  // 初期化・終了処理実行クラス

        friend class Singleton<Type>;
    };
}




//----- BaseMainWindow実装
namespace EtherEngine {
    // Applicationデータセッター
    template <typename Type>
    void BaseMainWindow<Type>::SetApplicationData(const HINSTANCE hInstance, const LPSTR ipCmdLine, const int& cmdShow) {
        m_hInstance = hInstance;
        m_ipCmdLine = ipCmdLine;
        m_cmdShow = cmdShow;
    }
}


#endif // !I_BASEMAINWINDOW_G
