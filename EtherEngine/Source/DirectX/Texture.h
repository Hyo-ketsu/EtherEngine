#ifndef I_TEXTURE_H
#define I_TEXTURE_H


namespace EtherEngine {
    // テクスチャを表すクラス
    class Texture {
    public:
        // コンストラクタ
        Texture(void) {}
        // デストラクチャ
        ~Texture(void) {}


        // 画像サイズゲッター
        Eigen::Vector2<uint> GetSize(void) const { return m_size; }
        // シェーダーリソース
        ID3D11ShaderResourceView* GetResource(void) const { return m_shaderResourceView; }

    protected:
        // テクスチャー作成
        // @ Ret  : 
        // @ Arg1 :
        // @ Arg2 : サイズ
        D3D11_TEXTURE2D_DESC MakeTextureDesc(DXGI_FORMAT format, Eigen::Vector2<uint> size);
        virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData);

        Eigen::Vector2<uint> m_size;    // 画像サイズ
        ID3D11ShaderResourceView* m_shaderResourceView;
        ID3D11Texture2D*          m_texture;
    };
}


#endif // !I_TEXTURE_H
