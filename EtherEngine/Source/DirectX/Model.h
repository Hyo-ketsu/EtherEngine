#ifndef I_MODEL_H
#define I_MODEL_H
#include <Base/GraphicDefines.h>
#include <DirectX/Mesh.h>
#include <DirectX/MeshBuffer.h>
#include <DirectX/Texture.h>
#include <DirectX/ShaderClass.h>


//----- Model�錾
namespace EtherEngine {
    // ���f����\������N���X
    class Model {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �ǂݍ��݃t�@�C����
        // @ Arg2 : DirectX
        // @ Arg3 : �g�k(Default : 1.0f)
        // @ Arg4 : ���_���](Default : �s��Ȃ�)
        // @ Arg5 : ���_�V�F�[�_�[(Default : nullptr)
        // @ Arg6 : �s�N�Z���V�F�[�_�[(Default : nullptr)
        Model(const std::string& file, const BaseHandle<DirectXRender>& directX, const float scale = 1.0f, const bool isFlip = false, 
            VertexShader* const vertexShader = nullptr, PixelShader* const pixelShader = nullptr);
        // �R���X�g���N�^
        // @ Arg1 : �ǂݍ��݃t�@�C����
        // @ Arg2 : DirectX
        // @ Arg3 : ���_�V�F�[�_�[(Default : nullptr)
        // @ Arg4 : �s�N�Z���V�F�[�_�[(Default : nullptr)
        // @ Arg5 : �g�k(Default : 1.0f)
        // @ Arg6 : ���_���](Default : �s��Ȃ�)
        Model(const std::string& file, const BaseHandle<DirectXRender>& directX, VertexShader* const vertexShader = nullptr, PixelShader* const pixelShader = nullptr,
            const float scale = 1.0f, const bool isFlip = false);
        // �f�X�g���N�^
        ~Model(void);


        // �`��e�N�X�`���[�X���b�g�Q�b�^�[
        uint GetTextureSlot(void) const { return m_textureSlot; }
        // �`��e�N�X�`���[�X���b�g�Z�b�^�[
        void SetTextureSlot(const uint in) { m_textureSlot = in; }


        // �`��
        void DrawModel(void);

    protected:
        // ���f����ǂݍ���
        // @ Arg1 : �ǂݍ��݃t�@�C����
        // @ Arg2 : DirectX
        // @ Arg3 : �g�k(Default : 1.0f)
        // @ Arg4 : ���_���](Default : �s��Ȃ�)
        void Load(const std::string& file, const BaseHandle<DirectXRender>& directX, const float scale = 1.0f, const bool isFlip = false);


        // Default�V�F�[�_�[���쐬����
        // @ Arg1 : DirectX
        void MakeDefaultShader(const BaseHandle<DirectXRender>& directX);

        uint m_textureSlot; // �`��e�N�X�`���[�X���b�g
        std::vector<Mesh>     m_meshes;      // ���b�V�����
        std::vector<Material> m_materials;   // �}�e���A�����
        VertexShader*         m_vertexShader;   // ���_�V�F�[�_�[
        PixelShader*          m_pixelShader;    // �s�N�Z���V�F�[�_�[
        static std::unique_ptr<VertexShader> ms_defaultVertexShader;    // Default�̒��_�V�F�[�_�[
        static std::unique_ptr<PixelShader>  ms_defaultPixelShader;     // Default�̃s�N�Z���V�F�[�_�[
    };
}


#endif // !I_MODEL_H
