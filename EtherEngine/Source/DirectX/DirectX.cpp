#include <DirectX/DirectX.h>
#include <Base/GameObjectUpdater.h>


namespace EtherEngine {
	// �R���X�g���N�^
	DirectXRender::DirectXRender(void) 
		: m_rtv(nullptr)
		, m_dsv(nullptr) {
	}
	// �f�X�g���N�^
	DirectXRender::~DirectXRender(void) {
		Uninit();
	}


	// �������֐�
	HRESULT DirectXRender::Init(const UINT width, const UINT height, const HWND hWnd,
		const bool fullScreen, IDXGIAdapter1* adapter, IDXGIFactory1* factory) {
		//----- �ϐ��錾
		HRESULT	hr = E_FAIL;	// ����������

		//----- �X���b�v�`�F�C���̐ݒ�
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));					    // �[���N���A
		sd.BufferDesc.Width = width;						// �o�b�N�o�b�t�@�̕�
		sd.BufferDesc.Height = height;						// �o�b�N�o�b�t�@�̍���
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// �o�b�N�o�b�t�@�t�H�[�}�b�g(R,G,B,A)
		sd.SampleDesc.Count = 1;		// �}���`�T���v���̐�
		sd.BufferDesc.RefreshRate.Numerator = 1000;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// �o�b�N�o�b�t�@�̎g�p���@
		sd.BufferCount = 1;									// �o�b�N�o�b�t�@�̐�
		sd.OutputWindow = hWnd;			// �֘A�t����E�C���h�E
		sd.Windowed = fullScreen ? FALSE : TRUE;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


		//----- �h���C�o�̎�ޑI��
		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,	// GPU�ŕ`��
			D3D_DRIVER_TYPE_WARP,		// �����x(�ᑬ
			D3D_DRIVER_TYPE_REFERENCE,	// CPU�ŕ`��
		};
		UINT numDriverTypes = ARRAYSIZE(driverTypes);

		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		//----- �@�\���x��
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,		// DirectX11.1�Ή�GPU���x��
			D3D_FEATURE_LEVEL_11_0,		// DirectX11�Ή�GPU���x��
			D3D_FEATURE_LEVEL_10_1,		// DirectX10.1�Ή�GPU���x��
			D3D_FEATURE_LEVEL_10_0,		// DirectX10�Ή�GPU���x��
			D3D_FEATURE_LEVEL_9_3,		// DirectX9.3�Ή�GPU���x��
			D3D_FEATURE_LEVEL_9_2,		// DirectX9.2�Ή�GPU���x��
			D3D_FEATURE_LEVEL_9_1		// Direct9.1�Ή�GPU���x��
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		D3D_DRIVER_TYPE driverType;
		D3D_FEATURE_LEVEL featureLevel;

		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex) {
			driverType = driverTypes[driverTypeIndex];
			hr = D3D11CreateDeviceAndSwapChain(
				NULL,					// �f�B�X�v���C�f�o�C�X�̃A�_�v�^�iNULL�̏ꍇ�ŏ��Ɍ��������A�_�v�^�j
				driverType,				// �f�o�C�X�h���C�o�̃^�C�v
				NULL,					// �\�t�g�E�F�A���X�^���C�U���g�p����ꍇ�Ɏw�肷��
				createDeviceFlags,		// �f�o�C�X�t���O
				featureLevels,			// �@�\���x��
				numFeatureLevels,		// �@�\���x����
				D3D11_SDK_VERSION,		// 
				&sd,					// �X���b�v�`�F�C���̐ݒ�
				m_swapChain.GetEditable(),			// IDXGIDwapChain�C���^�t�F�[�X	
				m_device.GetEditable(),				// ID3D11Device�C���^�t�F�[�X
				&featureLevel,		// �T�|�[�g����Ă���@�\���x��
				m_context.GetEditable());		// �f�o�C�X�R���e�L�X�g
			if (SUCCEEDED(hr)) {
				break;
			}
		}
		if (FAILED(hr)) {
			return hr;
		}

		//--- �����_�[�^�[�Q�b�g�쐬
		// �o�b�N�o�b�t�@�̃|�C���^���擾
		ID3D11Texture2D* pBackBuffer = nullptr;
		hr = m_swapChain.Get()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		// �o�b�N�o�b�t�@�ւ̃|�C���^���w�肵�ă����_�[�^�[�Q�b�g�r���[���쐬
		if (SUCCEEDED(hr)) {
			hr = m_device.Get()->CreateRenderTargetView(pBackBuffer, NULL, &m_rtv);
			m_context.Get()->OMSetRenderTargets(1, &m_rtv, nullptr);
		}

		//----- �[�x�o�b�t�@�p�̃e�N�X�`���쐬
		D3D11_TEXTURE2D_DESC dsvTexDesc = {};
		pBackBuffer->GetDesc(&dsvTexDesc);
		dsvTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		ID3D11Texture2D* pDSVTex;
		hr = m_device.Get()->CreateTexture2D(&dsvTexDesc, nullptr, &pDSVTex);
		if (FAILED(hr)) { return hr; }

		//----- �[�x�o�b�t�@���쐬
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = dsvTexDesc.Format;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		hr = m_device.Get()->CreateDepthStencilView(pDSVTex, &dsvDesc, &m_dsv);
		if (FAILED(hr)) { return hr; }

		//----- �`���i�����_�[�^�[�Q�b�g�j�Ɛ[�x�o�b�t�@��ݒ�
		m_context.Get()->OMSetRenderTargets(1, &m_rtv, m_dsv);

		//----- �r���[�|�[�g
		D3D11_VIEWPORT viewPort;
		viewPort.TopLeftX = 0.0f;
		viewPort.TopLeftY = 0.0f;
		viewPort.Width    = width;
		viewPort.Height   = height;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		m_context.Get()->RSSetViewports(1, &viewPort);

		return S_OK;
	}
	// �I������
	void DirectXRender::Uninit(void) {
		if (m_context.Get()   != nullptr) m_context.Get()->ClearState();
		if (m_swapChain.Get() != nullptr) m_swapChain.Get()->SetFullscreenState(false, nullptr);

		m_context = nullptr;
		m_swapChain = nullptr;
		m_device = nullptr;
	}


	// �`��O����
	void DirectXRender::BeginDraw(void) {
		static float color[4] = { 0.3f,0.8f,0.3f,1.f }; // MEMO : ��
		m_context.Get()->ClearRenderTargetView(m_rtv, color);
		m_context.Get()->ClearDepthStencilView(m_dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	// �`�揈��
	void DirectXRender::Draw() {
		GameObjectUpdater::Get()->Draw();
	}
	// �`��㏈��
	void DirectXRender::EndDraw(void) {
		m_swapChain.Get()->Present(0, 0);
	}
}
