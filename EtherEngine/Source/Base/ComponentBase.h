#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H
#include <Base/CollisionBase.h>
#include <Base/BaseObject.h>
#include <Base/Handle.h>


//----- ComponentBase �錾
namespace EtherEngine {
    // �R���|�[�l���g�̊�b�ƂȂ�N���X
    class ComponentBase : public BaseObject {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �Q�[���I�u�W�F�N�g
        // @ Arg2 : �R���|�[�l���g��(Default : "Conponent")
        ComponentBase(void* gameObject, const std::string& name = "Conponent");
        // �������z�f�X�g���N�^
        virtual ~ComponentBase(void) = 0 {}
        ComponentBase(const ComponentBase& copy) = delete;
        // ���[�u�R���X�g���N�^
        ComponentBase(ComponentBase&& move) = default;


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
        virtual void Start(void) {}
        virtual void Update(void) {}
        virtual void Delete(void) {}
        virtual void CollisionStart(void) {}
        virtual void CollisionEnd(void) {}
        virtual void CollisionHit(void) {}

    private:
        class GameObject* m_gameObject;   // �����Q�[���I�u�W�F�N�g
        std::vector<CollisionHitData> m_hitData;    // �Փ˃R���W�����f�[�^
        bool m_isStart; // ����Start�������s���Ă��邩
    };
}


#endif // !I_COMPONENTBASE_H
