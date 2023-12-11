#ifndef I_TEXTURE_H
#define I_TEXTURE_H
#include <DirectX/ComPointer.h>
#include <DirectX/DirectX.h>
#include <Base/Handle.h>


namespace EtherEngine {
    // テクスチャを表すクラス
    class Texture {
    public:
        // コンストラクタ
        Texture(void);
        // デストラクチャ
        virtual ~Texture(void) {}


        // 画像サイズゲッター
        Eigen::Vector2<uint> GetSize(void) const { return m_size; }
        // シェーダーリソース
        ID3D11ShaderResourceView* GetResource(void) const { return m_shaderResourceView.Get(); }


        // テクスチャーを作成する
        // @ Arg1 : DirectX
        // @ Arg2 : 読み込みファイル名
        HRESULT Create(const Handle<DirectXRender>& directX, const std::string& file);
        // テクスチャーを作成する
        // @ Arg1 : DirectX
        // @ Arg2 : 画像フォーマット
        // @ Arg3 : 画像サイズ
        // @ Arg4 : データ(Default : nullptr)
        HRESULT Create(const Handle<DirectXRender>& directX, DXGI_FORMAT format, Eigen::Vector2<uint> size, const void* data = nullptr);

    protected:
        // テクスチャー作成
        // @ Ret  : 
        // @ Arg1 : DirectX
        // @ Arg2 :
        // @ Arg3 : サイズ
        D3D11_TEXTURE2D_DESC MakeTextureDesc(DXGI_FORMAT format, Eigen::Vector2<uint> size);
        virtual HRESULT CreateResource(const Handle<DirectXRender>& directX, D3D11_TEXTURE2D_DESC& desc, const void* data);

        Eigen::Vector2<uint> m_size;    // 画像サイズ
        ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;
        ComPtr<ID3D11Texture2D>          m_texture;
    };
}


#endif // !I_TEXTURE_H
