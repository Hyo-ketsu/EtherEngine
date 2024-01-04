#ifndef I_DRAWCOMPONENT_H
#define I_DRAWCOMPONENT_H
#include <DirectX/ShaderClass.h>
#include <EngineLibrary/Component.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/AttributeDefine.h>


//----- DrawBaseComponent �錾
namespace EtherEngine {
    // �`��R���|�[�l���g
    public ref class DrawBaseComponent : public Component {
    public:
        // �R���X�g���N�^
        DrawBaseComponent(void)
            : Component()
            , m_vertexShader(nullptr)
            , m_pixelShader(nullptr) {
        }
        // �`�揈�����s��
        virtual void Draw(void) {}


        // �r���[�s��Q�b�^�[
        UnmanageMaintainer<Eigen::Matrix4f> GetView(void) { return m_view; }
        // �r���[�s��Z�b�^�[
        void SetView(UnmanageMaintainer<Eigen::Matrix4f> in) { m_view = in; }
        // �v���W�F�N�V�����s��Q�b�^�[
        UnmanageMaintainer<Eigen::Matrix4f> GetProjection(void) { return m_projection; }
        // �v���W�F�N�V�����s��Z�b�^�[
        void SetProjection(UnmanageMaintainer<Eigen::Matrix4f> in) { m_projection = in; }

        // ���_�V�F�[�_�[���A�N�Z�T�[
        System::String^ AccessThisVertexShader(void) { return m_thisVertexShader; }
        // �s�N�Z���V�F�[�_�[���A�N�Z�T�[
        System::String^ AccessThisPixelShader(void) { return m_thisPixelShader; }

        // ���_�V�F�[�_�[�Q�b�^�[
        VertexShader* const GetVertexShader(void) { return m_vertexShader; }
        // �s�N�Z���V�F�[�_�[�Z�b�^�[
        PixelShader* const GetPixelShader(void) { return m_pixelShader; }


        // �V�F�[�_�[�g�p
        void Bind(void) {
            if (m_vertexShader != nullptr) m_vertexShader->Bind();
            if (m_pixelShader != nullptr) m_pixelShader->Bind();
        }
        // �V�F�[�_�[�ǂݍ���
        // @ �V�F�[�_�[������ǂݍ��݂��s���܂��̂Ŏ��O�ɓǂݍ��݂��s���Ă�������
        void Load(void) {
            // @ MEMO : ������
        }

    private:
        [Attribute::OutputAttribute] System::String^ m_thisVertexShader; // ���ݕێ����Ă��钸�_�V�F�[�_�[��
        [Attribute::OutputAttribute] System::String^ m_thisPixelShader;  // ���ݕێ����Ă���pixel�V�F�[�_�[��
        VertexShader* m_vertexShader;    // ���_�V�F�[�_�[
        PixelShader* m_pixelShader;      // �s�N�Z���V�F�[�_�[
        UnmanageMaintainer<Eigen::Matrix4f> m_view;         // �r���[�s��
        UnmanageMaintainer<Eigen::Matrix4f> m_projection;   // �v���W�F�N�V�����s��
    };
}


#endif // !I_DRAWCOMPONENT_H