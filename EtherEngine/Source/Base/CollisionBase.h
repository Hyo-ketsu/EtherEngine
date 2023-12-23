#ifndef I_COLLISIONBASE_H
#define I_COLLISIONBASE_H
#include <Base/BaseDefines.h>
#include <Base/StorageSystem.h>


//----- �񋓑� ��`
namespace EtherEngine {
    //----- �����蔻��̌`��
    enum class CollisionShape {
        Ray = 0,   // ���C(����)
        Sphere,    // ��
        Capsule,   // �J�v�Z��
        Box,       // ��(OBB)
        Mesh,      // ���b�V��
    };

    //----- �Փ˃^�C�~���O
    enum class CollisionHitTiming {
        Start = 0,  // �ՓˊJ�n
        End,        // �ՓˏI��
        Hit,        // �Փ˒�
    };


    //----- �����蔻��̎��
    enum class CollisionType {
        Substance = 0,  // ���� (= �����߂����s��)
        Transparent,    // ���� (= �����߂����s��Ȃ�)
    };
}


//----- CollisionHitData �錾
namespace EtherEngine {
    // �Փˏ��
    class CollisionHitData {
    public:
        // �R���X�g���N�^
        // @ Arg1 : ���������Ώ�
        CollisionHitData(void* gameObject);


        // �ՓˑΏۃQ�b�^�[
        // @ Memo : �w���p�[�����g�p���������B
        // @ Arg1 : �i�[����|�C���^
        void GetHitTarget(void** gameObject) const;

    private:
        class NativeGameObject* m_hitTarget; // �ՓˑΏ�
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
        // @ Arg3 : �����蔻��̈ړ���(Default : �S��0.0f)
        CollisionBase(const CollisionShape& shape, const CollisionType& type, const Eigen::Vector3f& offset = Eigen::Vector3f::Zero());
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

        // �����蔻��̈ړ��ʃQ�b�^�[
        Eigen::Vector3f GetOffset(void) const { return m_offset; }
        // �����蔻��̈ړ��ʃZ�b�^�[
        void SetOffset(const Eigen::Vector3f& in) { m_offset = in; }
        // �����蔻��̈ړ��ʃA�N�Z�T�[
        Eigen::Vector3f& AccessOffSet(void) { return m_offset; }

        // ID�Q�b�^�[
        const IDNumberType& GetId(void) const { return m_id; }

    private:
        const CollisionShape     mc_shape;  // ���̓����蔻��̌`��
        CollisionType            m_type;    // ���̓����蔻��̎��
        Eigen::Vector3f          m_offset;  // �����蔻��̈ړ���
        IDNumberType             m_id;      // ���g��ID
    };
}


#endif // !I_COLLISIONBASE_H
