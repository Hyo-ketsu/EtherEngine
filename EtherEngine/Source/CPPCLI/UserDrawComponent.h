#ifndef I_USERDRAWCOMPONENT_H
#define I_USERDRAWCOMPONENT_H
#include <DirectX/ShaderClass.h>
#include <CPPCLI/UserComponent.h>
#include <CPPCLI/CPPCLIUtility.h>
#include <CPPCLI/AttributeDefine.h>


//----- UserDrawBaseComponent 宣言
namespace EtherEngine {
    // 描画コンポーネント
    public ref class UserDrawBaseComponent : public UserBaseComponent {
    public:
        // コンストラクタ
        UserDrawBaseComponent(void)
            : UserBaseComponent()
            , m_vertexShader(nullptr)
            , m_pixelShader(nullptr) {
        }
        // 描画処理を行う
        virtual void Draw(void) {}


        // ビュー行列ゲッター
        UnmanageMaintainer<Eigen::Matrix4f> GetView(void) { return m_view; }
        // ビュー行列セッター
        void SetView(UnmanageMaintainer<Eigen::Matrix4f> in) { m_view = in; }
        // プロジェクション行列ゲッター
        UnmanageMaintainer<Eigen::Matrix4f> GetProjection(void) { return m_projection; }
        // プロジェクション行列セッター
        void SetProjection(UnmanageMaintainer<Eigen::Matrix4f> in) { m_projection = in; }

        // 頂点シェーダー名アクセサー
        System::String^ AccessThisVertexShader(void) { return m_thisVertexShader; }
        // ピクセルシェーダー名アクセサー
        System::String^ AccessThisPixelShader(void) { return m_thisPixelShader; }

        // 頂点シェーダーゲッター
        VertexShader* const GetVertexShader(void) { return m_vertexShader; }
        // ピクセルシェーダーセッター
        PixelShader* const GetPixelShader(void) { return m_pixelShader; }


        // シェーダー使用
        void Bind(void) {
            if (m_vertexShader != nullptr) m_vertexShader->Bind();
            if (m_pixelShader != nullptr) m_pixelShader->Bind();
        }
        // シェーダー読み込み
        // @ シェーダー名から読み込みを行いますので事前に読み込みを行ってください
        void Load(void) {
            // @ MEMO : 未実装
        }

    private:
        [Attribute::Serialize] System::String^ m_thisVertexShader; // 現在保持している頂点シェーダー名
        [Attribute::Serialize] System::String^ m_thisPixelShader;  // 現在保持しているpixelシェーダー名
        VertexShader* m_vertexShader;    // 頂点シェーダー
        PixelShader* m_pixelShader;      // ピクセルシェーダー
        UnmanageMaintainer<Eigen::Matrix4f> m_view;         // ビュー行列
        UnmanageMaintainer<Eigen::Matrix4f> m_projection;   // プロジェクション行列
    };
}


#endif // !I_USERDRAWCOMPONENT_H
