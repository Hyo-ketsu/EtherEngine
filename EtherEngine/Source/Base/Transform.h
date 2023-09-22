#ifndef I_TRANSFORM_H
#define I_TRANSFORM_H
#include <Base/EtherEngineUtility.h>


namespace EtherEngine {
    // ���W�E��]�E�g�k��ێ�����N���X
    class Transform : public IInOuter {
    public:
        // �R���X�g���N�^
        // @ Arg1 : ���W(Default : 0,0,0)
        // @ Arg2 : �g�k(Default : 1,1,1)
        // @ Arg3 : ��](Default : 0,0,0)
        Transform(Eigen::Vector3f pos = { 0,0,0 }, Eigen::Vector3f sca = { 1,1,1 }, Eigen::Vector3f rot = { 0,0,0 });
        // �f�X�g���N�^
        ~Transform(void) = default;
        // �R�s�[�R���X�g���N�^
        Transform(const Transform& copy) = default;
        // ���[�u�R���X�g���N�^
        Transform(Transform&& move) = default;


        // ���W���擾����
        const Eigen::Vector3f& GetPostion(void) const noexcept { return m_postion; }
        // ���W���擾����
        Eigen::Vector3f& AccessPostion(void) noexcept { return m_postion; }
        // �g�k���擾����
        const Eigen::Vector3f& GetScale(void) const noexcept { return m_scale; }
        // �g�k���擾����
        Eigen::Vector3f& AccessScale(void) noexcept { return m_scale; }
        // ��]���擾����
        const Eigen::Vector3f& GetRotation(void) const noexcept { return m_rotation; }
        // ��]���擾����
        Eigen::Vector3f& AccessRotation(void) noexcept { return m_rotation; }


        // ���[���h�s����쐬����
        // @ Ret  : ���[���h�s��
        Eigen::Matrix4f CreateWorld(void) const;


        // ���Z
        Transform operator+(const Transform& transform);
        // ���Z
        Transform operator-(const Transform& transform);
        // ���
        Transform& operator=(const Transform& transform);
        // ���Z���
        Transform& operator+=(const Transform& transform);
        // ���Z���
        Transform& operator-=(const Transform& transform);


        // �O���o��
        Json Output(void) override;
        // �O������
        void Input(const Json& input) override;

    private:
        Eigen::Vector3f m_postion;  // ���W
        Eigen::Vector3f m_scale;    // �g�k
        Eigen::Vector3f m_rotation; // ��]
    };
}


#endif // !I_TRANSFORM_H
