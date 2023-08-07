#ifndef I_CAMERABASE_H
#define I_CAMERABASE_H
#include <Base/IDClass.h>
#include <Base/StorageSystem.h>
#include <Base/EtherEngineUtility.h>


//----- CameraData �錾
namespace EtherEngine {
    // ����p���̃J��������ێ����Ă���N���X
    class CameraData : public IInOuter {
    public:
        // �R���X�g���N�^
        // @ Arg1 : ���W
        // @ Arg2 : �����_
        CameraData(const Eigen::Vector3f& pos, const Eigen::Vector3f& look);
        // Json�R���X�g���N�^
        // @ Arg1 : Json������
        CameraData(const std::string& json);
        // �f�X�g���N�^
        ~CameraData(void) {}


        // ���W�Q�b�^�[
        Eigen::Vector3f GetPos(void) const { return m_pos; }
        // ���W�Z�b�^�[
        void SetPos(const Eigen::Vector3f& in);
        // �����_�Q�b�^�[
        Eigen::Vector3f GetLook(void) const { return m_look; }
        // �����_�Z�b�^�[
        void SetLook(const Eigen::Vector3f& in);
        // ������Q�b�^�[
        Eigen::Vector3f GetUp(void) const { return m_up; }
        // ������Z�b�^�[
        void SetUp(const Eigen::Vector3f& in) { m_up = in; }
        // �D��x�Q�b�^�[
        int GetPriority(void) const { return m_priority; }
        // �D��x�Z�b�^�[
        void SetPriority(const int in) { m_priority = in; }
        // ����p�Q�b�^�[
        float GetFovy(void) const { return m_fovy; }
        // ����p�Z�b�^�[
        void SetFovy(const float in);
        // ��ʃA�X�y�N�g�䗦�Q�b�^�[
        float GetAspect(void) const { return m_aspect; }
        // ��ʃA�X�y�N�g�䗦�Z�b�^�[
        void SetAspect(const float in);
        // �ŒZ�N���b�v�����Q�b�^�[
        float GetNear(void) const { return m_near; }
        // �ŒZ�N���b�v�����Z�b�^�[
        void SetNear(const float in);
        // �Œ��N���b�v�����Q�b�^�[
        float GetFar(void) const { return m_far; }
        // �Œ��N���b�v�����Z�b�^�[
        void SetFar(const float in);


        // �O���o�͂���
        std::string Output(void) override;
        // �O�����͂���
        void Input(const std::string& input) override;

    private:
        // ���W�ƒ����_�������W�̏ꍇ�ɗ�O���o�͂��܂�
        void CheckPosLookPosition(void) const;

        Eigen::Vector3f m_pos;  // ���W
        Eigen::Vector3f m_look; // �����_
        Eigen::Vector3f m_up;   // �����
        int   m_priority;   // �D��x
        float m_fovy;   // ����p
        float m_aspect; // ��ʃA�X�y�N�g�䗦
        float m_near;   // �ŒZ�N���b�v����
        float m_far;    // �Œ��N���b�v����
    };
}


//----- CameraBase �錾
namespace EtherEngine {
    // �J������\������N���X
    class CameraBase : public IInOuter {
    public:
        // �R���X�g���N�^
        // @ Arg1 : ���W
        // @ Arg2 : �����_
        CameraBase(const Eigen::Vector3f& pos, const Eigen::Vector3f& look);
        // �R���X�g���N�^
        // @ Arg1 : �J�������
        CameraBase(const CameraData& data);

        // �f�X�g���N�^
        virtual ~CameraBase(void);


        // �J�������A�N�Z�T�[
        CameraData& AccessCameraData(void) { return m_cameraData; }

        // ID�Q�b�^�[
        const StorageID<CameraBase>& GetID(void) { return m_id; }


        // �r���[�s����擾����
        // @ Ret  : �擾�����r���[�s��
        // @ Arg1 : �]�u���s����(Default : ture)
        Eigen::Matrix4f GetView(const bool isTranspose = true) const;
        // �v���W�F�N�V�����s����擾����
        // @ Ret  : �擾�����v���W�F�N�V�����s��
        // @ Arg1 : �]�u���s����(Default : ture)
        Eigen::Matrix4f GetProjection(const bool isTranspose = true) const;


        // �O���o�͂���
        std::string Output(void) override;
        // ���͂���
        void Input(const std::string& input) override;

    private:
        CameraData m_cameraData;        // �J�������
        StorageID<CameraBase> m_id;    // ����object��ID
    };
}


#endif // !I_CAMERABASE_H
