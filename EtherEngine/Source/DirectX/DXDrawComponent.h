#ifndef I_DXDRAWCOMPONENT_H
#define I_DXDRAWCOMPONENT_H
#include <Base/GraphicDefines.h>
#include <Base/DrawComponent.h>
#include <DirectX/ShaderClass.h>


//----- DXDrawComponent�錾
namespace EtherEngine {
    class DXDrawComponent : public DrawComponent {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �Q�[���I�u�W�F�N�g
        // @ Arg2 : ���_�V�F�[�_�[
        // @ Arg3 : �s�N�Z���V�F�[�_�[
        DXDrawComponent(GameObject* gameObject, const VertexShader& vertexShader, const PixelShader& pixelShader);


        // DX�p�`��֐�
        void DrawPlatformFunction(void) override final;


        // ���_�V�F�[�_�[�Z�b�^�[
        void SetVertexShader(const VertexShader& in) { m_vertexShader = in; }
        // �s�N�Z���V�F�[�_�[�Z�b�^�[
        void SetPixelShader(const PixelShader& in) { m_pixelShader = in; }

    private:
        VertexShader m_vertexShader;    // ���_�V�F�[�_�[
        PixelShader  m_pixelShader;     // �s�N�Z���V�F�[�_�[
    };
}


#endif // !I_DXDRAWCOMPONENT_H
