#ifndef I_DIRECTX_H
#define I_DIRECTX_H
#include <DirectX/ComPointer.h>
#include <Base/Handle.h>


namespace EtherEngine {
    // 1レンダーテクスチャーに対応する描画用クラス
    class DirectXRender {
    public:
        // コンストラクタ
        DirectXRender(void);
        // デストラクタ
        ~DirectXRender(void);


        // SwapChainゲッター
        IDXGISwapChain* const GetSwapChain(void) const { return m_swapChain.Get(); }
        // Deviceゲッター
        ID3D11Device* const GetDevice(void) const { return m_device.Get(); }
        // DeviceContextゲッター
        ID3D11DeviceContext* const GetContext(void) const { return m_context.Get(); }
        // レンダーターゲットゲッター
        ID3D11RenderTargetView* const GetRenderTargetView(void) const { return m_rtv; }
        // 深度バッファーゲッター
        ID3D11DepthStencilView* const GetDepthStencilView(void) const { return m_dsv; }


        // 初期化関数
        // @ Ret  : 初期化を完了したか
        // @ Arg1 : フレームバッファの横幅
        // @ Arg2 : フレームバッファの縦幅
        // @ Arg3 : DirextXを割り当てるウィンドウ
        // @ Arg4 : フルスクリーン指定
        // @ Arg5 : ビデオカード指定
        // @ Arg6 : ファクトリ指定
        HRESULT Init(const UINT width, const UINT height, const HWND hWnd, const bool fullScreen, IDXGIAdapter1* adapter, IDXGIFactory1* factory);
        // 終了処理
        void Uninit(void);


        // 描画前処理
        void BeginDraw(void);
        // 描画処理
        void Draw();
        // 描画後処理
        void EndDraw(void);

    private:
        ComPtr<IDXGISwapChain> m_swapChain; // スワップチェイン
        ComPtr<ID3D11Device>   m_device;
        ComPtr<ID3D11DeviceContext> m_context;
        ID3D11RenderTargetView* m_rtv;
        ID3D11DepthStencilView* m_dsv;
    };
}


#endif // !I_DIRECTX_H
