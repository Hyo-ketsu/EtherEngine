#ifndef I_COLLISIONBASE_H
#define I_COLLISIONBASE_H


//----- �񋓑� ��`
namespace EtherEngine {
    //----- �����蔻��̌`��
    enum class CollisionShape {
        Ray = 0,   // ���C(����)
        Sphere,    // ��
        Capsule,   // �J�v�Z��
        Box,       // ��
        Mesh,      // ���b�V��
    };


    //----- �����蔻��̎��
    enum class CollisionType {
        Substance = 0,  // ���� (= �����߂����s��)
        Transparent,    // ���� (= �����߂����s��Ȃ�)
    };
}


//----- CollisionBase �錾
namespace EtherEngine {
    //----- �����蔻���\������N���X
    class CollisionBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �����蔻��̌`��
        // @ Arg2 : �����蔻��̎��
        CollisionBase(const CollisionShape& shape, const CollisionType& type);
        // �f�X�g���N�^
        virtual ~CollisionBase(void) {}
        // �R�s�[�R���X�g���N�^
        CollisionBase(const CollisionBase& copy) = default;
        // ���[�u�R���X�g���N�^
        CollisionBase(CollisionBase&& move) = default;


        // �����蔻��`��Q�b�^�[
        CollisionShape GetShape(void) const { return mc_shape; }

        // �����蔻���ރQ�b�^�[
        CollisionType GetType(void) const { return m_type; }
        // �����蔻���ރZ�b�^�[
        void SetType(const CollisionType& in) { m_type = in; }
        // �����蔻���ރA�N�Z�T�[
        CollisionType& AccessType(void) { return m_type; }

    private:
        const CollisionShape mc_shape;  // ���̓����蔻��̌`��
        CollisionType m_type;           // ���̓����蔻��̎��
    };
}


#endif // !I_COLLISIONBASE_H
