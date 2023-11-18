#include <DirectX/DirectX.h>
#include <Base/GameObjectUpdater.h>


namespace EtherEngine {
	// コンストラクタ
	DirectXRender::DirectXRender(void) {
	}
	// デストラクタ
	DirectXRender::~DirectXRender(void) {
		Uninit();
	}


	// 初期化関数
	void DirectXRender::Init(const Eigen::Vector2i size, const HWND hWnd, const bool fullScreen) {
		//----- 作成
		DrawFunctionLambda func = [](Eigen::Matrix4f view, Eigen::Matrix4f projection) { GameObjectUpdater::Get()->Draw(view, projection); };
        CreateDrawWindow(size, hWnd, fullScreen, func, []() -> bool {return true; }, WindowFunctionLambda());
	}
	// 終了処理
	void DirectXRender::Uninit(void) {
		m_windowRenders.clear();

		if (m_context.Get() != nullptr) m_context.Get()->ClearState();

		m_context = nullptr;
		m_device = nullptr;
	}


    // ウィンドウを作成する
    IDClass DirectXRender::CreateDrawWindow(const Eigen::Vector2i size, const HWND hWnd, const bool fullScreen, 
        const DrawFunctionLambda& drwaFunction, const WindowEnableLambda& enableFunction, const WindowFunctionLambda& windowFunction) {
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
        m_windowRenders.emplace_back(this, size, hWnd, fullScreen, adapter, factory, drwaFunction, enableFunction, windowFunction);
        auto& ret = m_windowRenders.back().GetId();

        if (adapter) adapter->Release();
        if (adapterMax) adapterMax->Release();
        if (factory) factory->Release();

        return ret;
    }


    // ウィンドウをIDで取得する
    DXWindowRender* const DirectXRender::GetWindowRender(IDClass id) {
        for (auto&& it : m_windowRenders) {
            if (it.GetId() == id) {
                return &it;
            }
        }

        return nullptr;
    }
}
