#include <DirectX/DirectX.h>
#include <Base/GameObjectUpdater.h>


namespace EtherEngine {
	// コンストラクタ
	DirectXRender::DirectXRender(void) {
        //----- 変数宣言
        HRESULT hresult = E_FAIL;

        //----- ドライバの種類選択
        D3D_DRIVER_TYPE driverTypes[] = {
            D3D_DRIVER_TYPE_HARDWARE,	// GPUで描画
            D3D_DRIVER_TYPE_WARP,		// 高精度(低速
            D3D_DRIVER_TYPE_REFERENCE,	// CPUで描画
        };
        uint numDriverTypes = ARRAYSIZE(driverTypes);

        uint createDeviceFlags = 0;
#ifdef _DEBUG
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
        //----- 機能レベル
        D3D_FEATURE_LEVEL featureLevels[] = {
            D3D_FEATURE_LEVEL_11_1,		// DirectX11.1対応GPUレベル
            D3D_FEATURE_LEVEL_11_0,		// DirectX11対応GPUレベル
            D3D_FEATURE_LEVEL_10_1,		// DirectX10.1対応GPUレベル
            D3D_FEATURE_LEVEL_10_0,		// DirectX10対応GPUレベル
            D3D_FEATURE_LEVEL_9_3,		// DirectX9.3対応GPUレベル
            D3D_FEATURE_LEVEL_9_2,		// DirectX9.2対応GPUレベル
            D3D_FEATURE_LEVEL_9_1		// Direct9.1対応GPUレベル
        };
        uint numFeatureLevels = ARRAYSIZE(featureLevels);

        D3D_DRIVER_TYPE driverType;
        D3D_FEATURE_LEVEL featureLevel;

        for (uint driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex) {
            driverType = driverTypes[driverTypeIndex];
            hresult = D3D11CreateDevice(NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                D3D11_SDK_VERSION, m_device.GetEditable(), &featureLevel, m_context.GetEditable());

            if (SUCCEEDED(hresult)) {
                break; 
            }
        }

        if (FAILED(hresult)) {
            throw EditorException("DirectX Init");
        }
	}
	// デストラクタ
	DirectXRender::~DirectXRender(void) {
		Uninit();
	}


	// 初期化関数
	void DirectXRender::Init(const Eigen::Vector2i size, const HWND hWnd, const bool fullScreen) {
        CreateDrawWindow(size, hWnd, fullScreen);
	}
	// 終了処理
	void DirectXRender::Uninit(void) {
		m_windowRenders.clear();

		if (m_context.Get() != nullptr) m_context.Get()->ClearState();

		m_context = nullptr;
		m_device = nullptr;
	}


    // ウィンドウを作成する
    IDNumberType DirectXRender::CreateDrawWindow(const Eigen::Vector2i size, const HWND hWnd, const bool fullScreen) {
        //----- ビデオカードの検索
        IDXGIFactory1* factory;
        IDXGIAdapter1* adapter;
        IDXGIAdapter1* adapterMax;
        DXGI_ADAPTER_DESC descMax; // 現在の最大処理速度のビデオカード
        UINT i = 0;
        CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory);
        factory->EnumAdapters1(i, &adapter); i++;
        adapterMax = adapter;
        adapterMax->GetDesc(&descMax);
        for (; factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i) {
            DXGI_ADAPTER_DESC desc;
            adapter->GetDesc(&desc);

            bool isHighPerformanceGPU = (desc.DedicatedVideoMemory > descMax.DedicatedVideoMemory);
            if (isHighPerformanceGPU) {
                adapterMax = adapter;
                adapterMax->GetDesc(&descMax);
            }
        }

        //----- 作成
        m_windowRenders.emplace_back(this, size, hWnd, fullScreen, adapter, factory);
        auto& ret = m_windowRenders.back().GetId();

        if (adapter) adapter->Release();
        if (adapterMax) adapterMax->Release();
        if (factory) factory->Release();

        return ret;
    }


    // ウィンドウをIDで取得する
    DXWindowRender* const DirectXRender::GetWindowRender(IDNumberType id) {
        for (auto&& it : m_windowRenders) {
            if (it.GetId() == id) {
                return &it;
            }
        }

        return nullptr;
    }
}
