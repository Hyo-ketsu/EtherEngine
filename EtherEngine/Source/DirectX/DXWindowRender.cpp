#include <DirectX/DXWindowRender.h>
#include <Base/CameraStorage.h>
#include <Base/EditorException.h>
#include <Base/NativeGameObjectUpdater.h>
#include <DirectX/DirectX.h>


//----- DXWindowRender 定義
namespace EtherEngine {
	// コンストラクタ
	DXWindowRender::DXWindowRender(DirectXRender* directX, const Eigen::Vector2i size, const HWND& hWnd, const bool fullScreen, IDXGIAdapter1* adapter, IDXGIFactory1* factory)
		: m_directX(directX)
		, m_rtv(nullptr)
		, m_dsv(nullptr) 
		, m_dss(nullptr)
		, m_backColor(0.7f, 0.9f, 0.9f, 1.0f) {
		//----- Nullチェック
		if (directX == nullptr) throw EditorException("Error! directX is Null");

		//----- 生存確認用のキーを取得
		m_dxEnable = m_directX->GetEnableKey();

		//----- 変数宣言
		HRESULT	hr = E_FAIL;	// 成功したか

		//----- スワップチェインの設定
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));					    // ゼロクリア
		sd.BufferDesc.Width = 0;						    // バックバッファの幅
		sd.BufferDesc.Height = 0;					        // バックバッファの高さ
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// バックバッファフォーマット(R,G,B,A)
		sd.SampleDesc.Count = 1;		// マルチサンプルの数
		sd.BufferDesc.RefreshRate.Numerator = 1000;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// バックバッファの使用方法
		sd.BufferCount = 1;									// バックバッファの数
		sd.OutputWindow = hWnd;			// 関連付けるウインドウ
		sd.Windowed = fullScreen ? FALSE : TRUE;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		hr = factory->CreateSwapChain(directX->GetDevice(), &sd, m_swapChain.GetEditable());
		if (FAILED(hr)) throw EditorException(std::to_string(hr).c_str());

		//--- レンダーターゲット作成
		// バックバッファのポインタを取得
		ID3D11Texture2D* pBackBuffer = nullptr;
		hr = m_swapChain.Get()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		// バックバッファへのポインタを指定してレンダーターゲットビューを作成
		if (SUCCEEDED(hr)) {
			hr = m_directX->GetDevice()->CreateRenderTargetView(pBackBuffer, NULL, &m_rtv);
			m_directX->GetContext()->OMSetRenderTargets(1, &m_rtv, nullptr);
		}

		//----- 深度バッファ用のテクスチャ作成
		D3D11_TEXTURE2D_DESC dsvTexDesc = {};
		pBackBuffer->GetDesc(&dsvTexDesc);
		dsvTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		ID3D11Texture2D* pDSVTex;
		hr = m_directX->GetDevice()->CreateTexture2D(&dsvTexDesc, nullptr, &pDSVTex);
		if (FAILED(hr)) throw EditorException(std::to_string(hr).c_str());

		//----- 深度バッファを作成
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = dsvTexDesc.Format;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		hr = m_directX->GetDevice()->CreateDepthStencilView(pDSVTex, &dsvDesc, &m_dsv);
		if (FAILED(hr)) throw EditorException(std::to_string(hr).c_str());

		//----- 描画先（レンダーターゲット）と深度バッファを設定
		m_directX->GetContext()->OMSetRenderTargets(1, &m_rtv, m_dsv);

		//----- ビューポート
		D3D11_VIEWPORT viewPort;
		viewPort.TopLeftX = 0.0f;
		viewPort.TopLeftY = 0.0f;
		viewPort.Width = size.x();
		viewPort.Height = size.y();
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		m_directX->GetContext()->RSSetViewports(1, &viewPort);

		// デプスステンシルステート設定
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
		depthStencilDesc.DepthEnable = TRUE;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		depthStencilDesc.StencilEnable = FALSE;
		m_directX->GetDevice()->CreateDepthStencilState(&depthStencilDesc, &m_dss);//深度有効ステート
		//depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		//m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateDisable);//深度無効ステート
		m_directX->GetContext()->OMSetDepthStencilState(m_dss, NULL);
	}
	// デストラクタ
	DXWindowRender::DXWindowRender(void) {
		if (m_swapChain.Get() != nullptr) m_swapChain.Get()->SetFullscreenState(false, nullptr);
		m_swapChain = nullptr;
	}


	// 描画前処理
	void DXWindowRender::BeginDraw(void) {
		if (this->GetIsDirectXEnable() == false) return;

		//----- クリア
		m_directX->GetContext()->ClearRenderTargetView(m_rtv, m_backColor.array().data());
		m_directX->GetContext()->ClearDepthStencilView(m_dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	// 描画後処理
	void DXWindowRender::EndDraw(void) {
		if (this->GetIsDirectXEnable() == false) return;

		m_swapChain.Get()->Present(0, 0);
	}
}