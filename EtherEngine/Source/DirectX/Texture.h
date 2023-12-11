#ifndef I_TEXTURE_H
#define I_TEXTURE_H
#include <DirectX/ComPointer.h>
#include <DirectX/DirectX.h>
#include <Base/Handle.h>


namespace EtherEngine {
    // �e�N�X�`����\���N���X
    class Texture {
    public:
        // �R���X�g���N�^
        Texture(void);
        // �f�X�g���N�`��
        virtual ~Texture(void) {}


        // �摜�T�C�Y�Q�b�^�[
        Eigen::Vector2<uint> GetSize(void) const { return m_size; }
        // �V�F�[�_�[���\�[�X
        ID3D11ShaderResourceView* GetResource(void) const { return m_shaderResourceView.Get(); }


        // �e�N�X�`���[���쐬����
        // @ Arg1 : DirectX
        // @ Arg2 : �ǂݍ��݃t�@�C����
        HRESULT Create(const Handle<DirectXRender>& directX, const std::string& file);
        // �e�N�X�`���[���쐬����
        // @ Arg1 : DirectX
        // @ Arg2 : �摜�t�H�[�}�b�g
        // @ Arg3 : �摜�T�C�Y
        // @ Arg4 : �f�[�^(Default : nullptr)
        HRESULT Create(const Handle<DirectXRender>& directX, DXGI_FORMAT format, Eigen::Vector2<uint> size, const void* data = nullptr);

    protected:
        // �e�N�X�`���[�쐬
        // @ Ret  : 
        // @ Arg1 : DirectX
        // @ Arg2 :
        // @ Arg3 : �T�C�Y
        D3D11_TEXTURE2D_DESC MakeTextureDesc(DXGI_FORMAT format, Eigen::Vector2<uint> size);
        virtual HRESULT CreateResource(const Handle<DirectXRender>& directX, D3D11_TEXTURE2D_DESC& desc, const void* data);

        Eigen::Vector2<uint> m_size;    // �摜�T�C�Y
        ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;
        ComPtr<ID3D11Texture2D>          m_texture;
    };
}


#endif // !I_TEXTURE_H
