#ifndef I_TRANSFORM_H
#define I_TRANSFORM_H


namespace EtherEngine {
    // ���W�E��]�E�g�k��ێ�����N���X
    class Transform {
    public:
        // �R���X�g���N�^
        // @ Arg1 : ���W(�f�t�H���g�F�S��0)
        // @ Arg2 : �g�k(�f�t�H���g�F�S��0)
        // @ Arg3 : ��](�f�t�H���g�F�S��0)
        Transform(Eigen::Vector3f pos = { 0,0,0 }, Eigen::Vector3f sca = { 1,1,1 }, Eigen::Vector3f rot = { 0,0,0 });


        // ���W���擾����
        // @ Arg1 : ���W
        Eigen::Vector3f& AccessPostion(void) noexcept { return m_postion; }
        // �g�k���擾����
        // @ Arg1 : �g�k
        Eigen::Vector3f& AccessScale(void) noexcept { return m_scale; }
        // ��]���擾����
        // @ Arg1 : ��]
        Eigen::Vector3f& AccessRotation(void) noexcept { return m_rotation; }

    private:
        Eigen::Vector3f m_postion;  // ���W
        Eigen::Vector3f m_scale;    // �g�k
        Eigen::Vector3f m_rotation; // ��]
    };
}


#endif // !I_TRANSFORM_H
