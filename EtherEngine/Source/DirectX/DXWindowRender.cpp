#include <DirectX/DXWindowRender.h>
#include <Base/CameraStorage.h>
#include <Base/EditorException.h>
#include <Base/NativeGameObjectUpdater.h>
#include <DirectX/DirectX.h>


//----- DXWindowRender ��`
namespace EtherEngine {
	// �R���X�g���N�^
	DXWindowRender::DXWindowRender(DirectXRender* directX, const Eigen::Vector2i size, const HWND& hWnd, const bool fullScreen, IDXGIAdapter1* adapter, IDXGIFactory1* factory)
		: m_directX(directX)
		, m_rtv(nullptr)
		, m_dsv(nullptr) 
		, m_dss(nullptr)
		, m_backColor(0.7f, 0.9f, 0.9f, 1.0f) {
		//----- Null�`�F�b�N
		if (directX == nullptr) throw EditorException("Error! directX is Null");

		//----- �����m�F�p�̃L�[���擾
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
		hr = factory->CreateSwapChain(directX->GetDevice(), &sd, m_swapChain.GetEditable());
		if (FAILED(hr)) throw EditorException(std::to_string(hr).c_str());

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
		if (FAILED(hr)) throw EditorException(std::to_string(hr).c_str());

		//----- �[�x�o�b�t�@���쐬
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = dsvTexDesc.Format;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		hr = m_directX->GetDevice()->CreateDepthStencilView(pDSVTex, &dsvDesc, &m_dsv);
		if (FAILED(hr)) throw EditorException(std::to_string(hr).c_str());

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


	// �`��O����
	void DXWindowRender::BeginDraw(void) {
		if (this->GetIsDirectXEnable() == false) return;

		//----- �N���A
		m_directX->GetContext()->ClearRenderTargetView(m_rtv, m_backColor.array().data());
		m_directX->GetContext()->ClearDepthStencilView(m_dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	// �`��㏈��
	void DXWindowRender::EndDraw(void) {
		if (this->GetIsDirectXEnable() == false) return;

		m_swapChain.Get()->Present(0, 0);
	}
}