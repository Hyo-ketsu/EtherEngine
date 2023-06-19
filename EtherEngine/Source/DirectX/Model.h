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
        // @ Arg3 : ���_�V�F�[�_�[
        // @ Arg4 : �s�N�Z���V�F�[�_�[
        // @ Arg5 : �g�k(Default : 1.0f)
        // @ Arg6 : ���_���](Default : �s��Ȃ�)
        Model(const std::string& file, const BaseHandle<DirectXRender>& directX, VertexShader* const vertexShader, PixelShader* const pixelShader,
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


        uint m_textureSlot; // �`��e�N�X�`���[�X���b�g
        std::vector<Mesh>     m_meshes;      // ���b�V�����
        std::vector<Material> m_materials;   // �}�e���A�����
        VertexShader*         m_vertexShader;   // ���_�V�F�[�_�[
        PixelShader*          m_pixelShader;    // ���_�V�F�[�_�[
    };
}


#endif // !I_MODEL_H
