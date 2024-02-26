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

        UNMANAGE_TO_MANAGE_MATRIX_SET(m_view.GetValue(), ret);

        return ret;
    }
    // ビュー行列
    void DrawComponent::View::set(System::Numerics::Matrix4x4 value) {
        MANAGE_TO_UNMANAGE_MATRIX_SET(value, m_view.GetValue());
    }
    // プロジェクション行列
    System::Numerics::Matrix4x4 DrawComponent::Projection::get(void) {
        System::Numerics::Matrix4x4 ret;

        UNMANAGE_TO_MANAGE_MATRIX_SET(m_projection.GetValue(), ret);

        return ret;
    }
    // プロジェクション行列
    void DrawComponent::Projection::set(System::Numerics::Matrix4x4 value) {
        MANAGE_TO_UNMANAGE_MATRIX_SET(value, m_projection.GetValue());
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
