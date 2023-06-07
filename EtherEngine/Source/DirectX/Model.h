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
        // @ Arg3 : 拡縮(Default : 1.0f)
        // @ Arg4 : 頂点反転(Default : 行わない)
        // @ Arg5 : 頂点シェーダー(Default : nullptr)
        // @ Arg6 : ピクセルシェーダー(Default : nullptr)
        Model(const std::string& file, const BaseHandle<DirectXRender>& directX, const float scale = 1.0f, const bool isFlip = false, 
            VertexShader* const vertexShader = nullptr, PixelShader* const pixelShader = nullptr);
        // コンストラクタ
        // @ Arg1 : 読み込みファイル名
        // @ Arg2 : DirectX
        // @ Arg3 : 頂点シェーダー(Default : nullptr)
        // @ Arg4 : ピクセルシェーダー(Default : nullptr)
        // @ Arg5 : 拡縮(Default : 1.0f)
        // @ Arg6 : 頂点反転(Default : 行わない)
        Model(const std::string& file, const BaseHandle<DirectXRender>& directX, VertexShader* const vertexShader = nullptr, PixelShader* const pixelShader = nullptr,
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


        // Defaultシェーダーを作成する
        // @ Arg1 : DirectX
        void MakeDefaultShader(const BaseHandle<DirectXRender>& directX);

        uint m_textureSlot; // 描画テクスチャースロット
        std::vector<Mesh>     m_meshes;      // メッシュ情報
        std::vector<Material> m_materials;   // マテリアル情報
        VertexShader*         m_vertexShader;   // 頂点シェーダー
        PixelShader*          m_pixelShader;    // ピクセルシェーダー
        static std::unique_ptr<VertexShader> ms_defaultVertexShader;    // Defaultの頂点シェーダー
        static std::unique_ptr<PixelShader>  ms_defaultPixelShader;     // Defaultのピクセルシェーダー
    };
}


#endif // !I_MODEL_H
