#ifndef I_TRANSFORM_H
#define I_TRANSFORM_H
#include <Base/EtherEngineUtility.h>


namespace EtherEngine {
    // ���W�E��]�E�g�k��ێ�����N���X
    class Transform : public IInOuter {
    public:
        // �R���X�g���N�^
        // @ Arg1 : ���W(�f�t�H���g�F�S��0)
        // @ Arg2 : �g�k(�f�t�H���g�F�S��0)
        // @ Arg3 : ��](�f�t�H���g�F�S��0)
        Transform(Eigen::Vector3f pos = { 0,0,0 }, Eigen::Vector3f sca = { 1,1,1 }, Eigen::Vector3f rot = { 0,0,0 });


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


        // �O���o��
        std::string Output(void) override;
        // �O������
        void Input(const std::string& input) override;

    private:
        Eigen::Vector3f m_postion;  // ���W
        Eigen::Vector3f m_scale;    // �g�k
        Eigen::Vector3f m_rotation; // ��]
    };
}


#endif // !I_TRANSFORM_H
