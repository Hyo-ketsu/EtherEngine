#ifndef I_DXWINDOWRENDER_H
#define I_DXWINDOWRENDER_H
#include <Base/IDClass.h>
#include <DirectX/ComPointer.h>


//----- DXWindowRender 宣言
namespace EtherEngine {
    // 前方宣言
    class DirectXRender;


    // 描画関数の型
    using DrawFunctionLambda = std::function<void(Eigen::Matrix4f view, Eigen::Matrix4f projection)>;
    // ウィンドウが生存しているかチェック関数
    using WindowEnableLambda = std::function<bool(void)>;
    // ウィンドウ内で行うその他の処理
    using WindowFunctionLambda = std::function<void(class DXWindowRender* const)>;


    // 1ウィンドウの描画を管理するクラス
    class DXWindowRender {
    public:
        // コンストラクタ
        // @ Exce : 初期化に失敗時
        // @ Arg1 : DirectX
        // @ Arg2 : フレームバッファの幅
        // @ Arg3 : ウィンドウハンドル
        // @ Arg4 : フルスクリーン指定
        // @ Arg5 : ビデオカード指定
        // @ Arg6 : ファクトリ指定
        // @ Arg7 : 描画関数で行う処理
        // @ Arg8 : ウィンドウが生存しているか判定する関数
        // @ Arg9 : その他ウィンドウ処理(Default : 何もしない)
        DXWindowRender(DirectXRender* directX, const Eigen::Vector2i size, const HWND& hWnd, const bool fullScreen, IDXGIAdapter1* adapter, IDXGIFactory1* factory,
            const DrawFunctionLambda& drawFunction, const WindowEnableLambda& windowEnableFunction, const WindowFunctionLambda& windowFunction);
        // デストラクタ
        DXWindowRender(void);


        // IDゲッター
        const IDClass& GetId(void) const { return m_id; }
        // DirectXゲッター
        DirectXRender* const GetDirectX(void) const { return m_directX; }
        // DirectX生存ゲッター
        // @ Ret  : 生存していたら true 
        bool GetIsDirectXEnable(void) const { return m_dxEnable.expired() == false; }
        // SwapChainゲッター
        IDXGISwapChain* const GetSwapChain(void) const { return m_swapChain.Get(); }
        // レンダーターゲットゲッター
        ID3D11RenderTargetView* const GetRenderTargetView(void) const { return m_rtv; }
        // 深度バッファーゲッター
        ID3D11DepthStencilView* const GetDepthStencilView(void) const { return m_dsv; }
        // IDゲッター
        const IDClass& GetCameraID(void) const { return m_mainCameraID; }
        // IDセッター
        void SetCameraID(const IDClass& in) { m_mainCameraID = in; }
        // ウィンドウ生存関数ゲッター
        WindowEnableLambda GetWindowEnableFunction(void) const { return m_enableFunction; }
        // その他ウィンドウ処理ゲッター
        WindowFunctionLambda GetWindowFunction(void) const { return m_windowFunction; }
        // 背景色アクセサー
        Eigen::Vector4f AccessBackColor(void) { return m_backColor; }


        // ウィンドウが生存しているか
        // @ Ret  :  ウィンドウが生存しているか
        bool IsEnableWindow(void) const;


        // 描画前処理
        void BeginDraw(void);
        // 描画処理
        // @ Ret  : 描画したか
        bool Draw(void);
        // 描画後処理
        void EndDraw(void);

    private:
        IDClass m_id;                        // 自身のid
        DirectXRender* m_directX;            // リソース
        std::weak_ptr<void> m_dxEnable;      // リソースの生存確認用
        ComPtr<IDXGISwapChain> m_swapChain;  // スワップチェイン
        ID3D11RenderTargetView* m_rtv;       // レンダーターゲット
        ID3D11DepthStencilView* m_dsv;       // 
        ID3D11DepthStencilState* m_dss;      //
        IDClass m_mainCameraID;              // メインカメラID
        DrawFunctionLambda m_drawFunction;   // 描画で行う処理
        WindowEnableLambda m_enableFunction; // ウィンドウが生存しているか判定する関数
        WindowFunctionLambda m_windowFunction; // その他のウィンドウ処理
        Eigen::Vector4f m_backColor;         // 背景色
    };
}


#endif // !I_DXWINDOWRENDER_H
