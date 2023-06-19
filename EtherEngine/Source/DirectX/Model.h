#ifndef I_MODEL_H
#define I_MODEL_H
#include <Base/GraphicDefines.h>
#include <DirectX/Mesh.h>
#include <DirectX/MeshBuffer.h>
#include <DirectX/Texture.h>
#include <DirectX/ShaderClass.h>


//----- Model宣言
namespace EtherEngine {
    // モデルを表現するクラス
    class Model {
    public:
        // コンストラクタ
        // @ Arg1 : 読み込みファイル名
        // @ Arg2 : DirectX
        // @ Arg3 : 頂点シェーダー
        // @ Arg4 : ピクセルシェーダー
        // @ Arg5 : 拡縮(Default : 1.0f)
        // @ Arg6 : 頂点反転(Default : 行わない)
        Model(const std::string& file, const BaseHandle<DirectXRender>& directX, VertexShader* const vertexShader, PixelShader* const pixelShader,
            const float scale = 1.0f, const bool isFlip = false);
        // デストラクタ
        ~Model(void);


        // 描画テクスチャースロットゲッター
        uint GetTextureSlot(void) const { return m_textureSlot; }
        // 描画テクスチャースロットセッター
        void SetTextureSlot(const uint in) { m_textureSlot = in; }


        // 描画
        void DrawModel(void);

    protected:
        // モデルを読み込む
        // @ Arg1 : 読み込みファイル名
        // @ Arg2 : DirectX
        // @ Arg3 : 拡縮(Default : 1.0f)
        // @ Arg4 : 頂点反転(Default : 行わない)
        void Load(const std::string& file, const BaseHandle<DirectXRender>& directX, const float scale = 1.0f, const bool isFlip = false);


        uint m_textureSlot; // 描画テクスチャースロット
        std::vector<Mesh>     m_meshes;      // メッシュ情報
        std::vector<Material> m_materials;   // マテリアル情報
        VertexShader*         m_vertexShader;   // 頂点シェーダー
        PixelShader*          m_pixelShader;    // 頂点シェーダー
    };
}


#endif // !I_MODEL_H
