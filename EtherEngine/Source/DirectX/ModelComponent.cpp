#include <DirectX/ModelComponent.h>


namespace EtherEngine {
    // コンストラクタ
    ModelComponent::ModelComponent(GameObject* gameObject, const std::string& file, const BaseHandle<DirectXRender>& directX, VertexShader& vertexShader, PixelShader& pixelShader,
        const float scale, const bool isFlip) 
        : DXDrawComponent(gameObject, vertexShader, pixelShader)
        , Model(file, directX, &vertexShader, &pixelShader,scale, isFlip) {
        SetVertexShader(vertexShader);
        SetPixelShader(pixelShader);
    }


    // 描画処理
    void ModelComponent::Draw(void) {
        DrawModel();
    }
}
