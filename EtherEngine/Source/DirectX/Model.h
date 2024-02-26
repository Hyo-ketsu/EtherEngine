#ifndef I_MODEL_H
#define I_MODEL_H
#include <Base/GraphicDefines.h>
#include <Base/EtherEngineUtility.h>
#include <Base/Transform.h>
#include <DirectX/Mesh.h>
#include <DirectX/MeshBuffer.h>
#include <DirectX/Texture.h>
#include <DirectX/ShaderClass.h>


//----- ModelData 宣言
namespace EtherEngine {
}


//----- ModelBase 宣言
namespace EtherEngine {
    // モデルを表現するクラス
    class ModelBase {
    public:
        // コンストラクタ
        ModelBase(void);
        // デストラクタ
        ~ModelBase(void);


        // 読み込みができたか
        bool GetIsLoad(void) const { return m_isLoad; }
        // 読み込み頂点反転ゲッター
        const bool GetIsFlip(void) const { return m_isFlip; }
        // 読み込み頂点反転セッター
        void SetIsFlip(const bool in) { m_isFlip = in; }
        // 読み込みスケールゲッター
        const float GetScale(void) const { return m_scale; }
        // 読み込みスケールセッター
        void SetScale(const float in) { m_scale = in; }
        // 読み込みモデル名ゲッター
        const std::string& GetLoadModel(void) const { return m_loadModel; }
        // 読み込みモデル名セッター
        void SetLoadModel(const std::string& in) { m_loadModel = in; }

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
        // 描画
        // @ Ret  : 描画したか
        // @ Arg1 : トランスフォーム
        // @ Arg2 : ビュー行列
        // @ Arg3 : プロジェクション行列
        // @ Arg4 : ピクセルシェーダー
        bool DrawModel(const Transform& transform, const Eigen::Matrix4f* view, const Eigen::Matrix4f* projection, PixelShader* pixelShader);


        // モデルを読み込む
        // @ Ret  : 読み込みエラー内容
        // @ Arg1 : DirectX
        std::string Load(const Handle<DirectXRender>& directX);

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
