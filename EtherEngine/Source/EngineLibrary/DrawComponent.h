#ifndef I_DRAWCOMPONENT_H
#define I_DRAWCOMPONENT_H
#include <DirectX/ShaderClass.h>
#include <EngineLibrary/Component.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/AttributeDefine.h>


//----- DrawBaseComponent �錾
namespace EtherEngine {
    // �`��R���|�[�l���g
    public ref class DrawComponent : public Component {
    public:
        // �R���X�g���N�^
        DrawComponent(void);
        // �f�X�g���N�^
        ~DrawComponent(void);
        // �t�@�C�i���C�U
        !DrawComponent(void);


        // �`�揈�����s��
        virtual void Draw(void) {}


        // �r���[�s��
        property System::Numerics::Matrix4x4 View {
            System::Numerics::Matrix4x4 get(void);
            void set(System::Numerics::Matrix4x4 value);
        }
        // �v���W�F�N�V�����s��
        property System::Numerics::Matrix4x4 Projection {
            System::Numerics::Matrix4x4 get(void);
            void set(System::Numerics::Matrix4x4 value);
        }
        // �r���[�s��Q�b�^�[
        Eigen::Matrix4f GetView(void) { return m_view.GetValue(); }
        // �r���[�s��Z�b�^�[
        void SetView(Eigen::Matrix4f in) { m_view.SetValue(std::move(in)); }
        // �v���W�F�N�V�����s��Q�b�^�[
        Eigen::Matrix4f GetProjection(void) { return m_projection.GetValue(); }
        // �v���W�F�N�V�����s��Z�b�^�[
        void SetProjection(Eigen::Matrix4f in) { m_projection.SetValue(std::move(in)); }

        // ���_�V�F�[�_�[��
        property System::String^ VertexShaderName {
            System::String^ get(void) { return m_thisVertexShader; }
            void set(System::String^ value);
        }
        // �s�N�Z���V�F�[�_�[��
        property System::String^ PixelShaderName {
            System::String^ get(void) { return m_thisPixelShader; }
            void set(System::String^ value);
        }

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


    protected:
        // DirectX�Q�b�^�[
        Handle<DirectXRender>* GetDirectX(void) { return m_directX; }

    private:
        [Attribute::OutputAttribute] System::String^ m_thisVertexShader; // ���ݕێ����Ă��钸�_�V�F�[�_�[��
        [Attribute::OutputAttribute] System::String^ m_thisPixelShader;  // ���ݕێ����Ă���pixel�V�F�[�_�[��
        VertexShader* m_vertexShader;    // ���_�V�F�[�_�[
        PixelShader* m_pixelShader;      // �s�N�Z���V�F�[�_�[
        UnmanageMaintainer<Eigen::Matrix4f> m_view;         // �r���[�s��
        UnmanageMaintainer<Eigen::Matrix4f> m_projection;   // �v���W�F�N�V�����s��
        Handle<DirectXRender>* m_directX;
    };
}


#endif // !I_DRAWCOMPONENT_H
