#include <DirectX/Texture.h>


//----- Texture実装
namespace EtherEngine {
    // コンストラクタ
    Texture::Texture(void)
        : m_size({ 0,0 })
        , m_shaderResourceView(nullptr)
        , m_texture(nullptr) {
    }


    // テクスチャーを作成する
    HRESULT Texture::Create(const BaseHandle<DirectXRender>& directX, const std::string& file) {
		//----- 変数宣言
		HRESULT hr = S_OK;

		//----- 文字変換
		wchar_t wPath[MAX_PATH];
		size_t wLen = 0;
		MultiByteToWideChar(0, 0, file.c_str(), -1, wPath, MAX_PATH);

		//----- ファイル別読み込み
		DirectX::TexMetadata mdata;
		DirectX::ScratchImage image;
		hr = DirectX::LoadFromWICFile(wPath, DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &mdata, image);
		if (FAILED(hr)) {
			return E_FAIL;
		}

		//----- シェーダリソース生成
		hr = CreateShaderResourceView(directX.GetAtomicData().GetDevice(), image.GetImages(), image.GetImageCount(), mdata, m_shaderResourceView.GetEditable());
		if (SUCCEEDED(hr)) {
			m_size = { mdata.width, mdata.height };
		}
		return hr;
    }
    // テクスチャーを作成する
    HRESULT Texture::Create(const BaseHandle<DirectXRender>& directX, DXGI_FORMAT format, Eigen::Vector2<uint> size, const void* data) {
		D3D11_TEXTURE2D_DESC desc = MakeTextureDesc(format, size);
		return CreateResource(directX, desc, data);
    }

    // テクスチャー作成
	D3D11_TEXTURE2D_DESC Texture::MakeTextureDesc(DXGI_FORMAT format, Eigen::Vector2<uint> size) {
		D3D11_TEXTURE2D_DESC desc = {};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.Format = format;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.Width = size.x();
		desc.Height = size.y();
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		return desc;
	}


	HRESULT Texture::CreateResource(const BaseHandle<DirectXRender>& directX, D3D11_TEXTURE2D_DESC& desc, const void* data) {
		//----- 変数宣言
		HRESULT hr = E_FAIL;

		//----- テクスチャ作成
		D3D11_SUBRESOURCE_DATA subresourceData = {};
		subresourceData.pSysMem = data;
		subresourceData.SysMemPitch = desc.Width * 4;
		hr = directX.GetAtomicData().GetDevice()->CreateTexture2D(&desc, data ? &subresourceData : nullptr, m_texture.GetEditable());
		if (FAILED(hr)) { return hr; }

		//----- 設定
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		switch (desc.Format) {
		default:						srvDesc.Format = desc.Format;			break;
		case DXGI_FORMAT_R32_TYPELESS: 	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;	break;
		}
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		//----- 生成
		hr = directX.GetAtomicData().GetDevice()->CreateShaderResourceView(m_texture.Get(), &srvDesc, m_shaderResourceView.GetEditable());
		if (SUCCEEDED(hr)) {
			m_size = { desc.Width, desc.Height };
		}
		return hr;
	}
}
