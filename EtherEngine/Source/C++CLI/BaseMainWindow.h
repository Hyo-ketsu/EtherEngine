#ifndef I_BASEMAINWINDOW_H
#define I_BASEMAINWINDOW_H
#include <Base/Singleton.h>
#include <Base/InitUninitPerformer.h>
#include <DirectX/Window.h>
#include <DirectX/DirectX.h>


//----- BaseMainWindow宣言
namespace EtherEngine {
    // 起動から終了まで存在しているウィンドウ
    class BaseMainWindow : public Window {
    public:
        // コンストラクタ
        // @ Arg1 : ウィンドウの名前
        BaseMainWindow(const std::string& name);


        // HInstanceゲッター
        const HINSTANCE& GetHInstance(void) const { return m_hInstance.value(); }
        // IpCmdLineゲッター
        const LPSTR& GetIpCmdLine(void) const { return m_ipCmdLine.value(); }
        // CmdShowゲッター
        const int& GetCmdShow(void) const { return m_cmdShow.value(); }
        // Procセッター
        void SetProc(WNDPROC* in) { m_proc = in; }

        // DirectXゲッター
        const BaseHandle<DirectXRender>& GetDirectX(void) const { return m_dxRender; }


        // 初期化関数
        void BaseInitFunction(void);
        // 終了関数
        void BaseUninitFunction(void);
        // メイン関数
        void BaseMainFunction(void);

        // 初期化前関数
        virtual void InitFirstFunction(void) {}
        // 初期化後関数
        virtual void InitLateFunction(void) {}
        // 初期化処理完了後関数
        virtual void EndInitLateFunction(void) {}
        // 終了前関数
        virtual void UninitFirstFunction(void) {}
        // 終了後関数
        virtual void UninitLateFunction(void) {}
        // 終了処理完了後関数
        virtual void EndUninitLateFunction(void) {}


        // WinMain の引数を保持する
        void SetApplicationData(const HINSTANCE hInstace, const LPSTR ipCmdLine, const int& cmdShow);

    protected:
        // メイン関数
        virtual void MainFunction(void) = 0;


        std::optional<HINSTANCE> m_hInstance;  // インスタンスハンドル
        std::optional<LPSTR>     m_ipCmdLine;  // コマンドライン
        std::optional<int>       m_cmdShow;    // アプリケーションの初期表示方法
        WNDPROC*                 m_proc;
        InitUninitPerformer m_initUninitPerformer;  // 初期化・終了処理実行クラス
    };
}


#endif // !I_BASEMAINWINDOW_H
