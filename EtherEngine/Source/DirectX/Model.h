#ifndef I_MODEL_H
#define I_MODEL_H
#include <Base/GraphicDefines.h>
#include <Base/EtherEngineUtility.h>
#include <DirectX/Mesh.h>
#include <DirectX/MeshBuffer.h>
#include <DirectX/Texture.h>
#include <DirectX/ShaderClass.h>


//----- Model宣言
namespace EtherEngine {
    // モデルを表現するクラス
    class Model : public IInOuter {
    public:
        // コンストラクタ
        Model(void);
        // デストラクタ
        ~Model(void);


        // 読み込みモデル名ゲッター
        const std::string& GetLoadModel(void) const { return m_loadModel; }

        // 描画テクスチャースロットゲッター
        uint GetTextureSlot(void) const { return m_textureSlot; }
        // 描画テクスチャースロットセッター
        void SetTextureSlot(const uint in) { m_textureSlot = in; }


        // 描画
        // @ Ret  : 描画したか
        // @ Arg1 : ワールド行列
        // @ Arg2 : ビュー行列
        // @ Arg3 : プロジェクション行列
        // @ Arg4 : ピクセルシェーダー
        bool DrawModel(const Eigen::Matrix4f& world, const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection, PixelShader* pixelShader);

        // モデルを読み込む
        // @ Arg1 : 読み込みファイル名
        // @ Arg2 : DirectX
        // @ Arg3 : 拡縮(Default : 1.0f)
        // @ Arg4 : 頂点反転(Default : 行わない)
        void Load(const std::string& file, const BaseHandle<DirectXRender>& directX, const float scale = 1.0f, const bool isFlip = false);


        // 外部出力
        std::string Output(void) override;
        // 外部入力
        void Input(const std::string& input) override;

    protected:
        bool m_isLoad;              // 読み込みができたか
        bool m_isFlip;              // 読み込み頂点反転
        float m_scale;              // 読み込みスケール
        std::string m_loadModel;    // 読込モデル名
        uint m_textureSlot;         // 描画テクスチャースロット
        std::vector<Mesh>     m_meshes;      // メッシュ情報
        std::vector<Material> m_materials;   // マテリアル情報
    };
}


#endif // !I_MODEL_H
