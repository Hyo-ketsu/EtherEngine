#ifndef I_COLLISIONSPHERE_H
#define I_COLLISIONSPHERE_H
#include <Base/CollisionBase.h>
#include <Base/GameObject.h>


//----- CollisionSphere �錾
namespace EtherEngine {
    class CollisionSphere : public CollisionBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �����蔻��̎��
        // @ Arg2 : ���̔��a
        // @ Arg3 : �����蔻��ʒu(�f�t�H���g : �S��0.0f)
        CollisionSphere(const CollisionType& type, const float& radius, const Eigen::Vector3f& offset = Eigen::Vector3f::Zero());


        // ���̔��a�Q�b�^�[
        const float GetRadius(void) const { return m_radius; }
        // ���̔��a�Z�b�^�[
        void SetRadius(const float in) { m_radius = in; }
        // ���̔��a�A�N�Z�T�[
        float& AccessRadius(void) { return m_radius; }

    private:
        float m_radius; // ���̔��a
    };
}


#endif // !I_COLLISIONSPHERE_H
