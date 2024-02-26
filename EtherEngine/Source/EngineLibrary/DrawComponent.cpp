#include <EngineLibrary/DrawComponent.h>
#include <EngineLibrary/GameApplication.h>


namespace EtherEngine {
    // コンストラクタ
    DrawComponent::DrawComponent(void)
        : Component()
        , m_vertexShader(nullptr)
        , m_pixelShader(nullptr) 
        , m_view(UnmanageMaintainer<Eigen::Matrix4f>())
        , m_projection(UnmanageMaintainer<Eigen::Matrix4f>())
        , m_directX(GameApplication::Get->GetDirectX()) {
    }
    // デストラクタ
    DrawComponent::~DrawComponent(void) {
        this->!DrawComponent();
    }
    // ファイナライザ
    DrawComponent::!DrawComponent(void) {
        m_view.MaintainerClear();
        m_projection.MaintainerClear();
    }


    // ビュー行列
    System::Numerics::Matrix4x4 DrawComponent::View::get(void) {
        System::Numerics::Matrix4x4 ret;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ret[i][j] = m_view.GetValue()(i, j);
            }
        }

        return ret;
    }
    // ビュー行列
    void DrawComponent::View::set(System::Numerics::Matrix4x4 value) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_view.GetValue()(i, j) = value[i][j];
            }
        }
    }
    // プロジェクション行列
    System::Numerics::Matrix4x4 DrawComponent::Projection::get(void) {
        System::Numerics::Matrix4x4 ret;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ret[i][j] = m_projection.GetValue()(i, j);
            }
        }

        return ret;
    }
    // プロジェクション行列
    void DrawComponent::Projection::set(System::Numerics::Matrix4x4 value) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_projection.GetValue()(i, j) = value[i][j];
            }
        }
    }


    // 頂点シェーダー名アクセサー
    void DrawComponent::VertexShaderName::set(System::String^ value) {
        m_thisVertexShader = value;
        // @ MEMO : ここで読み込み処理？
    }
    // ピクセルシェーダー名アクセサー
    void DrawComponent::PixelShaderName::set(System::String^ value) {
        m_thisPixelShader = value;
    }
}
