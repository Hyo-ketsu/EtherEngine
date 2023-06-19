#include <DirectX/DXDrawComponent.h>


//----- DXDraw定義
namespace EtherEngine {
    // コンストラクタ
    DXDrawComponent::DXDrawComponent(GameObject* gameObject, const VertexShader& vertexShader, const PixelShader& pixelShader)
        : DrawComponent(gameObject)
        , m_vertexShader(vertexShader)
        , m_pixelShader(pixelShader) {
    }


    // DX用描画関数
    void DXDrawComponent::DrawPlatformFunction(void) {
        m_vertexShader.Bind();
        m_pixelShader.Bind();
    }
}
