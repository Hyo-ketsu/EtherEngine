#ifndef I_DXDRAWCOMPONENT_H
#define I_DXDRAWCOMPONENT_H
#include <Base/GraphicDefines.h>
#include <Base/DrawComponent.h>
#include <DirectX/ShaderClass.h>


//----- DXDrawComponent宣言
namespace EtherEngine {
    class DXDrawComponent : public DrawComponent {
    public:
        // コンストラクタ
        // @ Arg1 : ゲームオブジェクト
        // @ Arg2 : 頂点シェーダー
        // @ Arg3 : ピクセルシェーダー
        DXDrawComponent(GameObject* gameObject, const VertexShader& vertexShader, const PixelShader& pixelShader);


        // DX用描画関数
        void DrawPlatformFunction(void) override final;


        // 頂点シェーダーセッター
        void SetVertexShader(const VertexShader& in) { m_vertexShader = in; }
        // ピクセルシェーダーセッター
        void SetPixelShader(const PixelShader& in) { m_pixelShader = in; }

    private:
        VertexShader m_vertexShader;    // 頂点シェーダー
        PixelShader  m_pixelShader;     // ピクセルシェーダー
    };
}


#endif // !I_DXDRAWCOMPONENT_H
