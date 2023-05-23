#ifndef I_TEXTURE_H
#define I_TEXTURE_H


namespace EtherEngine {
    // �e�N�X�`����\���N���X
    class Texture {
    public:
        // �R���X�g���N�^
        Texture(void) {}
        // �f�X�g���N�`��
        ~Texture(void) {}


        // �摜�T�C�Y�Q�b�^�[
        Eigen::Vector2<uint> GetSize(void) const { return m_size; }
        // �V�F�[�_�[���\�[�X
        ID3D11ShaderResourceView* GetResource(void) const { return m_shaderResourceView; }

    protected:
        // �e�N�X�`���[�쐬
        // @ Ret  : 
        // @ Arg1 :
        // @ Arg2 : �T�C�Y
        D3D11_TEXTURE2D_DESC MakeTextureDesc(DXGI_FORMAT format, Eigen::Vector2<uint> size);
        virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData);

        Eigen::Vector2<uint> m_size;    // �摜�T�C�Y
        ID3D11ShaderResourceView* m_shaderResourceView;
        ID3D11Texture2D*          m_texture;
    };
}


#endif // !I_TEXTURE_H
