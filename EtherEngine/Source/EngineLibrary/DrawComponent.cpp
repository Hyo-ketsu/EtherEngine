#include <EngineLibrary/DrawComponent.h>
#include <EngineLibrary/GameApplication.h>


namespace EtherEngine {
    // �R���X�g���N�^
    DrawComponent::DrawComponent(void)
        : Component()
        , m_vertexShader(nullptr)
        , m_pixelShader(nullptr) 
        , m_view(UnmanageMaintainer<Eigen::Matrix4f>())
        , m_projection(UnmanageMaintainer<Eigen::Matrix4f>())
        , m_directX(GameApplication::Get->GetDirectX()) {
    }
    // �f�X�g���N�^
    DrawComponent::~DrawComponent(void) {
        this->!DrawComponent();
    }
    // �t�@�C�i���C�U
    DrawComponent::!DrawComponent(void) {
        m_view.MaintainerClear();
        m_projection.MaintainerClear();
    }


    // �r���[�s��
    System::Numerics::Matrix4x4 DrawComponent::View::get(void) {
        System::Numerics::Matrix4x4 ret;

        UNMANAGE_TO_MANAGE_MATRIX_SET(m_view.GetValue(), ret);

        return ret;
    }
    // �r���[�s��
    void DrawComponent::View::set(System::Numerics::Matrix4x4 value) {
        MANAGE_TO_UNMANAGE_MATRIX_SET(value, m_view.GetValue());
    }
    // �v���W�F�N�V�����s��
    System::Numerics::Matrix4x4 DrawComponent::Projection::get(void) {
        System::Numerics::Matrix4x4 ret;

        UNMANAGE_TO_MANAGE_MATRIX_SET(m_projection.GetValue(), ret);

        return ret;
    }
    // �v���W�F�N�V�����s��
    void DrawComponent::Projection::set(System::Numerics::Matrix4x4 value) {
        MANAGE_TO_UNMANAGE_MATRIX_SET(value, m_projection.GetValue());
    }


    // ���_�V�F�[�_�[���A�N�Z�T�[
    void DrawComponent::VertexShaderName::set(System::String^ value) {
        m_thisVertexShader = value;
        // @ MEMO : �����œǂݍ��ݏ����H
    }
    // �s�N�Z���V�F�[�_�[���A�N�Z�T�[
    void DrawComponent::PixelShaderName::set(System::String^ value) {
        m_thisPixelShader = value;
    }
}
