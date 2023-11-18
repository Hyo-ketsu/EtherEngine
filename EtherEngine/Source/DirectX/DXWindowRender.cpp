#include <DirectX/DXWindowRender.h>
#include <Base/CameraStorage.h>
#include <DirectX/DirectX.h>


//----- DXWindowRender ��`
namespace EtherEngine {
	// �R���X�g���N�^
	DXWindowRender::DXWindowRender(DirectXRender* directX, const Eigen::Vector2i size, const HWND& hWnd, const bool fullScreen, IDXGIAdapter1* adapter, IDXGIFactory1* factory,
		const DrawFunctionLambda& drawFunction, const WindowEnableLambda& windowEnableFunction, const WindowFunctionLambda& windowFunction)
		: m_directX(directX)
		, m_rtv(nullptr)
		, m_dsv(nullptr) 
		, m_dss(nullptr)
		, m_drawFunction(drawFunction)
		, m_enableFunction(windowEnableFunction)
		, m_windowFunction(windowFunction)
		, m_backColor(0.7f, 0.9f, 0.9f, 1.0f) {
		//----- Null�`�F�b�N
		if (directX == nullptr) throw std::exception("Error! directX is Null");

		//----- �����m�F
		m_dxEnable = m_directX->GetEnableKey();

		//----- �ϐ��錾
		HRESULT	hr = E_FAIL;	// ����������

		//----- �X���b�v�`�F�C���̐ݒ�
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));					    // �[���N���A
		sd.BufferDesc.Width = 0;						    // �o�b�N�o�b�t�@�̕�
		sd.BufferDesc.Height = 0;					        // �o�b�N�o�b�t�@�̍���
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
				m_directX->GetEditableDevice(),		// ID3D11Device�C���^�t�F�[�X
				&featureLevel,		// �T�|�[�g����Ă���@�\���x��
				m_directX->GetEditableContext());	// �f�o�C�X�R���e�L�X�g
			if (SUCCEEDED(hr)) break;
		}
		if (FAILED(hr)) throw std::exception(std::to_string(hr).c_str());

		//--- �����_�[�^�[�Q�b�g�쐬
		// �o�b�N�o�b�t�@�̃|�C���^���擾
		ID3D11Texture2D* pBackBuffer = nullptr;
		hr = m_swapChain.Get()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		// �o�b�N�o�b�t�@�ւ̃|�C���^���w�肵�ă����_�[�^�[�Q�b�g�r���[���쐬
		if (SUCCEEDED(hr)) {
			hr = m_directX->GetDevice()->CreateRenderTargetView(pBackBuffer, NULL, &m_rtv);
			m_directX->GetContext()->OMSetRenderTargets(1, &m_rtv, nullptr);
		}

		//----- �[�x�o�b�t�@�p�̃e�N�X�`���쐬
		D3D11_TEXTURE2D_DESC dsvTexDesc = {};
		pBackBuffer->GetDesc(&dsvTexDesc);
		dsvTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		ID3D11Texture2D* pDSVTex;
		hr = m_directX->GetDevice()->CreateTexture2D(&dsvTexDesc, nullptr, &pDSVTex);
		if (FAILED(hr)) throw std::exception(std::to_string(hr).c_str());

		//----- �[�x�o�b�t�@���쐬
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = dsvTexDesc.Format;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		hr = m_directX->GetDevice()->CreateDepthStencilView(pDSVTex, &dsvDesc, &m_dsv);
		if (FAILED(hr)) throw std::exception(std::to_string(hr).c_str());

		//----- �`���i�����_�[�^�[�Q�b�g�j�Ɛ[�x�o�b�t�@��ݒ�
		m_directX->GetContext()->OMSetRenderTargets(1, &m_rtv, m_dsv);

		//----- �r���[�|�[�g
		D3D11_VIEWPORT viewPort;
		viewPort.TopLeftX = 0.0f;
		viewPort.TopLeftY = 0.0f;
		viewPort.Width = size.x();
		viewPort.Height = size.y();
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		m_directX->GetContext()->RSSetViewports(1, &viewPort);

		// �f�v�X�X�e���V���X�e�[�g�ݒ�
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
		depthStencilDesc.DepthEnable = TRUE;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		depthStencilDesc.StencilEnable = FALSE;
		m_directX->GetDevice()->CreateDepthStencilState(&depthStencilDesc, &m_dss);//�[�x�L���X�e�[�g
		//depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		//m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateDisable);//�[�x�����X�e�[�g
		m_directX->GetContext()->OMSetDepthStencilState(m_dss, NULL);
	}
	// �f�X�g���N�^
	DXWindowRender::DXWindowRender(void) {
		if (m_swapChain.Get() != nullptr) m_swapChain.Get()->SetFullscreenState(false, nullptr);
		m_swapChain = nullptr;
	}


	// �E�B���h�E���������Ă��邩
	bool DXWindowRender::IsEnableWindow(void) const {
		return GetIsDirectXEnable() && m_enableFunction();
	}


	// �`��O����
	void DXWindowRender::BeginDraw(void) {
		if (this->GetIsDirectXEnable() == false) return;

		//----- �F�쐬
		float color[4];
		for (int i = 0; i < 4; i++) {
			color[i] = m_backColor[i];
		}

		//----- �N���A
		m_directX->GetContext()->ClearRenderTargetView(m_rtv, color);
		m_directX->GetContext()->ClearDepthStencilView(m_dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	// �`�揈��
	bool DXWindowRender::Draw() {
		if (this->GetIsDirectXEnable() == false) return false;

		//----- �`�悷��
		if (CameraStorage::Get()->IsIDToData(m_mainCameraID)) {
			//----- �J�����擾
			auto camera = CameraStorage::Get()->GetData(m_mainCameraID);

			//----- �`��
			m_drawFunction(camera->GetView(), camera->GetProjection());

			return true;
		}

		return false;
	}
	// �`��㏈��
	void DXWindowRender::EndDraw(void) {
		if (this->GetIsDirectXEnable() == false) return;

		m_swapChain.Get()->Present(0, 0);
	}
}