#ifndef I_DRAWCOMPONENT_H
#define I_DRAWCOMPONENT_H
#include <Base/ComponentBase.h>


//----- DrawComponent�錾
namespace EtherEngine {
    class DrawComponent : public ComponentBase {
    public:
        using ComponentBase::ComponentBase;

        // �`�揈�����s��
        void DrawFuntion(void);

        // �r���[�s��Q�b�^�[
        Eigen::Matrix4f GetView(void) const { return m_view; }
        // �r���[�s��Z�b�^�[
        void SetView(const Eigen::Matrix4f& in) { m_view = in; }
        // �v���W�F�N�V�����s��Q�b�^�[
        Eigen::Matrix4f GetProjection(void) const { return m_projection; }
        // �v���W�F�N�V�����s��Z�b�^�[
        void SetProjection(const Eigen::Matrix4f& in) { m_projection = in; }


    protected:
        // �e�v���b�g�t�H�[���p�`�揈��
        virtual void DrawPlatformFunction(void) {}
        // �`�揈��
        virtual void Draw(void) {}

    private:
        Eigen::Matrix4f m_view; // �r���[�s��
        Eigen::Matrix4f m_projection;   // �v���W�F�N�V�����s��
    };
}


#endif // !I_DRAWCOMPONENT_H
