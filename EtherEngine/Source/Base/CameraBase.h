#ifndef I_CAMERABASE_H
#define I_CAMERABASE_H


//----- CameraBase�錾
namespace EtherEngine {
    // �J������\������N���X
    class CameraBase {
    public:
        // �R���X�g���N�^
        CameraBase(void);
        // �f�X�g���N�^
        virtual ~CameraBase(void);


        // ���W�Q�b�^�[
        Eigen::Vector3f GetPos(void) const { return m_pos; }
        // ���W�Z�b�^�[
        void SetPos(const Eigen::Vector3f& in) { m_pos = in; }
        // �����_�Q�b�^�[
        Eigen::Vector3f GetLook(void) const { return m_look; }
        // �����_�Z�b�^�[
        void SetLook(const Eigen::Vector3f& in) { m_look = in; }
        // ������Q�b�^�[
        Eigen::Vector3f GetUp(void) const { return m_up; }
        // ������Z�b�^�[
        void SetUp(const Eigen::Vector3f& in) { m_up = in; }


        // �r���[�s����擾����
        // @ Ret  : �擾�����r���[�s��
        // @ Arg1 : �]�u���s����(Default : ture)
        Eigen::Matrix4f GetView(const bool isTranspose = true) const;
        // �v���W�F�N�V�����s����擾����
        // @ Ret  : �擾�����v���W�F�N�V�����s��
        // @ Arg1 : �]�u���s����(Default : ture)
        Eigen::Matrix4f GetProjection(const bool isTranspose = true) const;

    protected:
        Eigen::Vector3f m_pos;  // ���W
        Eigen::Vector3f m_look; // �����_
        Eigen::Vector3f m_up;   // �����
        float m_fovy;   // ����p
        float m_aspect; // ��ʔ䗦
        float m_near;   // �ŒZ�N���b�v����
        float m_far;    // �Œ��N���b�v����
    };
}


#endif // !I_CAMERABASE_H
