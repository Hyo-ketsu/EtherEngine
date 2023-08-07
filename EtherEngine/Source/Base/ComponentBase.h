#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H
#include <Base/CollisionBase.h>
#include <Base/EtherEngineUtility.h>
#include <Base/BaseObject.h>
#include <Base/Handle.h>


//----- �R���|�[�l���g�p�萔
namespace EtherEngine {
    namespace Component {
        const std::string TYPE_COMPONENT = "Component";                     // �ʏ�R���|�[�l���g��`��
        const std::string TYPE_DRAW_COMPONENT = "DrawComponent";            // �`��R���|�[�l���g��`��
        const std::string TYPE_COLLISION_COMPONENT = "CollisionComponent";  // �����蔻��R���|�[�l���g��`��
    }
}


//----- ComponentBase �錾
namespace EtherEngine {
    // �R���|�[�l���g�̊�b�ƂȂ�N���X
    class ComponentBase : public BaseObject, public IInOuter {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �Q�[���I�u�W�F�N�g
        // @ Arg2 : �R���|�[�l���g��(Default : "Conponent")
        ComponentBase(void* gameObject, const std::string& name = "Component");
        // �f�X�g���N�^
        virtual ~ComponentBase(void) {}
        // �R�s�[�R���X�g���N�^
        ComponentBase(const ComponentBase& copy) = delete;
        // ���[�u�R���X�g���N�^
        ComponentBase(ComponentBase&& move) = default;
        // �R�s�[���
        ComponentBase& operator =(const ComponentBase& copy) = delete;
        // ���[�u���
        ComponentBase& operator =(ComponentBase&& move) = default;


        // �Փ˃R���W�����f�[�^�Q�b�^�[
        const std::vector<CollisionHitData>& GetCollisionHitData(void) const { return m_hitData; }
        // �Փ˃R���W�����f�[�^�Z�b�^�[
        void SetCollisionHitData(const std::vector<CollisionHitData>& in) { m_hitData = in; }
        // �Փ˃R���W�����f�[�^�A�N�Z�T�[
        std::vector<CollisionHitData>& AccessCollisionHitData(void) { return m_hitData; }


        // �����Q�[���I�u�W�F�N�g�̎擾
        // @ Memo : �z�Q�Ƃ̊֌W��ʓ|�Ȃ��ƂɂȂ��Ă��܂��B�w���p�[�����g�p���������B
        // @ Arg1 : �Q�[���I�u�W�F�N�g���i�[����
        void GetParentObject(void** gameObject) const;


        // �R���|�[�l���g���̎擾
        // @ Ret  : �R���|�[�l���g��
        virtual std::string GetComponentName(void) const;
        // �R���|�[�l���g�^�C�v���̎擾
        // @ Ret  : �R���|�[�l���g�̃^�C�v
        virtual std::string GetComponentTypeName(void) const;


        // �X�V�������s��
        void UpdateFuntion(void);
        // �����X�V�������s��
        // @ MEMO : ���΂炭�����\��Ȃ�
        void FixedUpdateFunction(void) {}
        // �폜���������s��
        void DeleteFuntion(void);
        // �ՓˊJ�n���������s��
        void CollisionStartFunction(void);
        // �ՓˏI�����������s��
        void CollisionEndFunction(void);
        // �Փˎ��������s��
        void CollisionHitFunction(void);

    protected:
        // �J�n����
        virtual void Start(void) = 0;
        // �X�V����
        virtual void Update(void) = 0;
        // �폜������
        virtual void Delete(void) = 0;
        // �ՓˊJ�n����
        virtual void CollisionStart(void) = 0;
        // �ՓˏI������
        virtual void CollisionEnd(void) = 0;
        // �Փˏ���
        virtual void CollisionHit(void) = 0;

    private:
        class GameObject* m_gameObject;   // �����Q�[���I�u�W�F�N�g
        std::vector<CollisionHitData> m_hitData;    // �Փ˃R���W�����f�[�^
        bool m_isStart; // ����Start�������s���Ă��邩
    };
}


#endif // !I_COMPONENTBASE_H
