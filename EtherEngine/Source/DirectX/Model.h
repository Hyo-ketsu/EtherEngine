#ifndef I_MODEL_H
#define I_MODEL_H
#include <Base/GraphicDefines.h>
#include <Base/EtherEngineUtility.h>
#include <DirectX/Mesh.h>
#include <DirectX/MeshBuffer.h>
#include <DirectX/Texture.h>
#include <DirectX/ShaderClass.h>


//----- Model�錾
namespace EtherEngine {
    // ���f����\������N���X
    class Model : public IInOuter {
    public:
        // �R���X�g���N�^
        Model(void);
        // �f�X�g���N�^
        ~Model(void);


        // �ǂݍ��݃��f�����Q�b�^�[
        const std::string& GetLoadModel(void) const { return m_loadModel; }

        // �`��e�N�X�`���[�X���b�g�Q�b�^�[
        uint GetTextureSlot(void) const { return m_textureSlot; }
        // �`��e�N�X�`���[�X���b�g�Z�b�^�[
        void SetTextureSlot(const uint in) { m_textureSlot = in; }


        // �`��
        // @ Ret  : �`�悵����
        // @ Arg1 : ���[���h�s��
        // @ Arg2 : �r���[�s��
        // @ Arg3 : �v���W�F�N�V�����s��
        // @ Arg4 : �s�N�Z���V�F�[�_�[
        bool DrawModel(const Eigen::Matrix4f& world, const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection, PixelShader* pixelShader);

        // ���f����ǂݍ���
        // @ Arg1 : �ǂݍ��݃t�@�C����
        // @ Arg2 : DirectX
        // @ Arg3 : �g�k(Default : 1.0f)
        // @ Arg4 : ���_���](Default : �s��Ȃ�)
        void Load(const std::string& file, const BaseHandle<DirectXRender>& directX, const float scale = 1.0f, const bool isFlip = false);


        // �O���o��
        std::string Output(void) override;
        // �O������
        void Input(const std::string& input) override;

    protected:
        bool m_isLoad;              // �ǂݍ��݂��ł�����
        bool m_isFlip;              // �ǂݍ��ݒ��_���]
        float m_scale;              // �ǂݍ��݃X�P�[��
        std::string m_loadModel;    // �Ǎ����f����
        uint m_textureSlot;         // �`��e�N�X�`���[�X���b�g
        std::vector<Mesh>     m_meshes;      // ���b�V�����
        std::vector<Material> m_materials;   // �}�e���A�����
    };
}


#endif // !I_MODEL_H
