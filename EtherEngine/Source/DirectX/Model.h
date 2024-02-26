#ifndef I_MODEL_H
#define I_MODEL_H
#include <Base/GraphicDefines.h>
#include <Base/EtherEngineUtility.h>
#include <Base/Transform.h>
#include <DirectX/Mesh.h>
#include <DirectX/MeshBuffer.h>
#include <DirectX/Texture.h>
#include <DirectX/ShaderClass.h>


//----- ModelData �錾
namespace EtherEngine {
}


//----- ModelBase �錾
namespace EtherEngine {
    // ���f����\������N���X
    class ModelBase {
    public:
        // �R���X�g���N�^
        ModelBase(void);
        // �f�X�g���N�^
        ~ModelBase(void);


        // �ǂݍ��݂��ł�����
        bool GetIsLoad(void) const { return m_isLoad; }
        // �ǂݍ��ݒ��_���]�Q�b�^�[
        const bool GetIsFlip(void) const { return m_isFlip; }
        // �ǂݍ��ݒ��_���]�Z�b�^�[
        void SetIsFlip(const bool in) { m_isFlip = in; }
        // �ǂݍ��݃X�P�[���Q�b�^�[
        const float GetScale(void) const { return m_scale; }
        // �ǂݍ��݃X�P�[���Z�b�^�[
        void SetScale(const float in) { m_scale = in; }
        // �ǂݍ��݃��f�����Q�b�^�[
        const std::string& GetLoadModel(void) const { return m_loadModel; }
        // �ǂݍ��݃��f�����Z�b�^�[
        void SetLoadModel(const std::string& in) { m_loadModel = in; }

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
        // �`��
        // @ Ret  : �`�悵����
        // @ Arg1 : �g�����X�t�H�[��
        // @ Arg2 : �r���[�s��
        // @ Arg3 : �v���W�F�N�V�����s��
        // @ Arg4 : �s�N�Z���V�F�[�_�[
        bool DrawModel(const Transform& transform, const Eigen::Matrix4f* view, const Eigen::Matrix4f* projection, PixelShader* pixelShader);


        // ���f����ǂݍ���
        // @ Ret  : �ǂݍ��݃G���[���e
        // @ Arg1 : DirectX
        std::string Load(const Handle<DirectXRender>& directX);

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
