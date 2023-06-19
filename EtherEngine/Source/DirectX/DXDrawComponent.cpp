#include <DirectX/DXDrawComponent.h>


//----- DXDraw��`
namespace EtherEngine {
    // �R���X�g���N�^
    DXDrawComponent::DXDrawComponent(GameObject* gameObject, const VertexShader& vertexShader, const PixelShader& pixelShader)
        : DrawComponent(gameObject)
        , m_vertexShader(vertexShader)
        , m_pixelShader(pixelShader) {
    }


    // DX�p�`��֐�
    void DXDrawComponent::DrawPlatformFunction(void) {
        m_vertexShader.Bind();
        m_pixelShader.Bind();
    }
}
