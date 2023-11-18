#include <DirectX/DirectX.h>
#include <Base/GameObjectUpdater.h>


namespace EtherEngine {
	// �R���X�g���N�^
	DirectXRender::DirectXRender(void) {
	}
	// �f�X�g���N�^
	DirectXRender::~DirectXRender(void) {
		Uninit();
	}


	// �������֐�
	void DirectXRender::Init(const Eigen::Vector2i size, const HWND hWnd, const bool fullScreen) {
		//----- �쐬
		DrawFunctionLambda func = [](Eigen::Matrix4f view, Eigen::Matrix4f projection) { GameObjectUpdater::Get()->Draw(view, projection); };
        CreateDrawWindow(size, hWnd, fullScreen, func, []() -> bool {return true; }, WindowFunctionLambda());
	}
	// �I������
	void DirectXRender::Uninit(void) {
		m_windowRenders.clear();

		if (m_context.Get() != nullptr) m_context.Get()->ClearState();

		m_context = nullptr;
		m_device = nullptr;
	}


    // �E�B���h�E���쐬����
    IDClass DirectXRender::CreateDrawWindow(const Eigen::Vector2i size, const HWND hWnd, const bool fullScreen, 
        const DrawFunctionLambda& drwaFunction, const WindowEnableLambda& enableFunction, const WindowFunctionLambda& windowFunction) {
        //----- �r�f�I�J�[�h�̌���
        IDXGIFactory1* factory;
        IDXGIAdapter1* adapter;
        IDXGIAdapter1* adapterMax;
        DXGI_ADAPTER_DESC descMax; // ���݂̍ő又�����x�̃r�f�I�J�[�h
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

        //----- �쐬
        m_windowRenders.emplace_back(this, size, hWnd, fullScreen, adapter, factory, drwaFunction, enableFunction, windowFunction);
        auto& ret = m_windowRenders.back().GetId();

        if (adapter) adapter->Release();
        if (adapterMax) adapterMax->Release();
        if (factory) factory->Release();

        return ret;
    }


    // �E�B���h�E��ID�Ŏ擾����
    DXWindowRender* const DirectXRender::GetWindowRender(IDClass id) {
        for (auto&& it : m_windowRenders) {
            if (it.GetId() == id) {
                return &it;
            }
        }

        return nullptr;
    }
}
