#ifndef I_SHADERCLASS_H
#define I_SHADERCLASS_H
#include <Base/Handle.h>
#include <DirectX/ComPointer.h>
#include <DirectX/Texture.h>
#include <DirectX/DirectX.h>


//----- ShaderBase�錾
namespace EtherEngine {
    // �ǂ̎�ނ̃V�F�[�_���̗񋓑�
    enum class ShaderType {
        Vertex = 0,
        Pixel,
    };


    // �V�F�[�_�̊�{���ۃN���X
    class ShaderBase {
    public:
        // �f�X�g���N�^
        virtual ~ShaderBase(void);


        // �V�F�[�_�t�@�C��(.cso)�ǂݍ��ݏ���
        // @ Ret  : �ǂݍ��݂ɐ���������
        // @ Arg1 : �ǂݍ��݂���cso�t�@�C����
        HRESULT LoadFile(const char* fileName);
        // �����񂩂�V�F�[�_���R���p�C�����鏈��
        HRESULT LoadCompile(const char* code);


        // �萔�̏������݂��s��
        // @ Arg1 : �������ރV�F�[�_�̃X���b�g
        // @ Arg2 : �������ރf�[�^
        void WriteBuffer(uint slot, void* data);
        // �e�N�X�`���[�̐ݒ���s��
        // @ Arg1 : �������ރV�F�[�_�̃X���b�g
        // @ Arg2 : �������ރe�N�X�`���[���
        void SetTexture(uint slot, Texture* texture);
        // �V�F�[�_��`��Ɏg�p����
        virtual void Bind(void) = 0;

    protected:
        // �R���X�g���N�^
        // @ Arg1 : DirectX
        // @ Arg2 : �V�F�[�_�̎��
        ShaderBase(const BaseHandle<DirectXRender>& directxRender, ShaderType shaderType);


        // �V�F�[�_�t�@�C���̓ǂݍ��݌�A�V�F�[�_�̎�ޕʂɏ������s��
        virtual HRESULT MakeShader(void* data, uint size) = 0;


        std::vector<ID3D11Buffer*> m_buffers;   // �ێ����Ă���o�b�t�@�[

    protected:
        //
        HRESULT Make(void* data, uint size);


        BaseHandle<DirectXRender> m_directxRender;  // �ێ����Ă���DirectX
        ShaderType m_shaderType;  // ���̃V�F�[�_�[�̎��
    };
}


//----- VertexShader�錾
namespace EtherEngine {
    // ���_�V�F�[�_
    class VertexShader : public ShaderBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : DirectX
        VertexShader(const BaseHandle<DirectXRender>& directxRender);
        // �f�X�g���N�^
        ~VertexShader(void) override;


        // �V�F�[�_���g�p����
        void Bind(void) override;

    protected:
        HRESULT MakeShader(void* data, uint size) override;

    private:
        ID3D11VertexShader* m_vertexShader; // �ێ����Ă��钸�_�V�F�[�_
        ID3D11InputLayout* m_inputLayout;   //
    };
}


//----- PixelShader�錾
namespace EtherEngine {
    // �s�N�Z���V�F�[�_
    class PixelShader : public ShaderBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : DirectX
        PixelShader(const BaseHandle<DirectXRender>& directxRender);
        // �f�X�g���N�^
        ~PixelShader(void) override;


        // �V�F�[�_���g�p����
        void Bind(void) override;

    protected:
        HRESULT MakeShader(void* data, uint size);

    private:
        ID3D11PixelShader* m_pixelShader;   // �ێ����Ă���s�N�Z���V�F�[�_
    };
}


#endif // !I_SHADERCLASS_H
