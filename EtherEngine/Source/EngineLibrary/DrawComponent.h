#ifndef I_DRAWCOMPONENT_H
#define I_DRAWCOMPONENT_H
#include <DirectX/ShaderClass.h>
#include <EngineLibrary/Component.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/AttributeDefine.h>


//----- DrawBaseComponent 宣言
namespace EtherEngine {
    // 描画コンポーネント
    public ref class DrawComponent : public Component {
    public:
        // コンストラクタ
        DrawComponent(void);
        // デストラクタ
        ~DrawComponent(void);
        // ファイナライザ
        !DrawComponent(void);


        // 描画処理を行う
        virtual void Draw(void) {}


        // ビュー行列
        property System::Numerics::Matrix4x4 View {
            System::Numerics::Matrix4x4 get(void);
            void set(System::Numerics::Matrix4x4 value);
        }
        // プロジェクション行列
        property System::Numerics::Matrix4x4 Projection {
            System::Numerics::Matrix4x4 get(void);
            void set(System::Numerics::Matrix4x4 value);
        }
        // ビュー行列ゲッター
        Eigen::Matrix4f GetView(void) { return m_view.GetValue(); }
        // ビュー行列セッター
        void SetView(Eigen::Matrix4f in) { m_view.SetValue(std::move(in)); }
        // プロジェクション行列ゲッター
        Eigen::Matrix4f GetProjection(void) { return m_projection.GetValue(); }
        // プロジェクション行列セッター
        void SetProjection(Eigen::Matrix4f in) { m_projection.SetValue(std::move(in)); }

        // 頂点シェーダー名
        property System::String^ VertexShaderName {
            System::String^ get(void) { return m_thisVertexShader; }
            void set(System::String^ value);
        }
        // ピクセルシェーダー名
        property System::String^ PixelShaderName {
            System::String^ get(void) { return m_thisPixelShader; }
            void set(System::String^ value);
        }

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


    protected:
        // DirectXゲッター
        Handle<DirectXRender>* GetDirectX(void) { return m_directX; }

    private:
        [Attribute::OutputAttribute] System::String^ m_thisVertexShader; // 現在保持している頂点シェーダー名
        [Attribute::OutputAttribute] System::String^ m_thisPixelShader;  // 現在保持しているpixelシェーダー名
        VertexShader* m_vertexShader;    // 頂点シェーダー
        PixelShader* m_pixelShader;      // ピクセルシェーダー
        UnmanageMaintainer<Eigen::Matrix4f> m_view;         // ビュー行列
        UnmanageMaintainer<Eigen::Matrix4f> m_projection;   // プロジェクション行列
        Handle<DirectXRender>* m_directX;
    };
}


#endif // !I_DRAWCOMPONENT_H
