#include <DirectX/DirectX.h>
#include <Base/GameObjectUpdater.h>


namespace EtherEngine {
	// �R���X�g���N�^
	DirectXRender::DirectXRender(void) {
        //----- �ϐ��錾
        HRESULT hresult = E_FAIL;

        //----- �h���C�o�̎�ޑI��
        D3D_DRIVER_TYPE driverTypes[] = {
            D3D_DRIVER_TYPE_HARDWARE,	// GPU�ŕ`��
            D3D_DRIVER_TYPE_WARP,		// �����x(�ᑬ
            D3D_DRIVER_TYPE_REFERENCE,	// CPU�ŕ`��
        };
        uint numDriverTypes = ARRAYSIZE(driverTypes);

        uint createDeviceFlags = 0;
#ifdef _DEBUG
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
        //----- �@�\���x��
        D3D_FEATURE_LEVEL featureLevels[] = {
            D3D_FEATURE_LEVEL_11_1,		// DirectX11.1�Ή�GPU���x��
            D3D_FEATURE_LEVEL_11_0,		// DirectX11�Ή�GPU���x��
            D3D_FEATURE_LEVEL_10_1,		// DirectX10.1�Ή�GPU���x��
            D3D_FEATURE_LEVEL_10_0,		// DirectX10�Ή�GPU���x��
            D3D_FEATURE_LEVEL_9_3,		// DirectX9.3�Ή�GPU���x��
            D3D_FEATURE_LEVEL_9_2,		// DirectX9.2�Ή�GPU���x��
            D3D_FEATURE_LEVEL_9_1		// Direct9.1�Ή�GPU���x��
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
	// �f�X�g���N�^
	DirectXRender::~DirectXRender(void) {
		Uninit();
	}


	// �������֐�
	void DirectXRender::Init(const Eigen::Vector2i size, const HWND hWnd, const bool fullScreen) {
        CreateDrawWindow(size, hWnd, fullScreen);
	}
	// �I������
	void DirectXRender::Uninit(void) {
		m_windowRenders.clear();

		if (m_context.Get() != nullptr) m_context.Get()->ClearState();

		m_context = nullptr;
		m_device = nullptr;
	}


    // �E�B���h�E���쐬����
    IDNumberType DirectXRender::CreateDrawWindow(const Eigen::Vector2i size, const HWND hWnd, const bool fullScreen) {
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
        m_windowRenders.emplace_back(this, size, hWnd, fullScreen, adapter, factory);
        auto& ret = m_windowRenders.back().GetId();

        if (adapter) adapter->Release();
        if (adapterMax) adapterMax->Release();
        if (factory) factory->Release();

        return ret;
    }


    // �E�B���h�E��ID�Ŏ擾����
    DXWindowRender* const DirectXRender::GetWindowRender(IDNumberType id) {
        for (auto&& it : m_windowRenders) {
            if (it.GetId() == id) {
                return &it;
            }
        }

        return nullptr;
    }
}
