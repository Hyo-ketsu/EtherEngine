#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H
#include <Base/CollisionBase.h>
#include <Base/EtherEngineUtility.h>
class NativeGameObject;
#include <Base/NativeBaseObject.h>
#include <Base/Handle.h>


//----- ComponentBase �錾
namespace EtherEngine {
    // �R���|�[�l���g�̊�b�ƂȂ�N���X
    class ComponentBase : public NativeBaseObject {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �Q�[���I�u�W�F�N�g
        // @ Arg2 : �R���|�[�l���g��(Default : "Conponent")
        ComponentBase(NativeGameObject* gameObject, const std::string& name = "Component");
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


        // �e�I�u�W�F�N�g�Q�b�^�[
        NativeGameObject* GetParentObject(void) const { return m_gameObject; }

        // �Փ˃R���W�����f�[�^�Q�b�^�[
        const std::vector<CollisionHitData>& GetCollisionHitData(void) const { return m_hitData; }
        // �Փ˃R���W�����f�[�^�Z�b�^�[
        void SetCollisionHitData(const std::vector<CollisionHitData>& in) { m_hitData = in; }
        // �Փ˃R���W�����f�[�^�A�N�Z�T�[
        std::vector<CollisionHitData>& AccessCollisionHitData(void) { return m_hitData; }


        // �ǉ����������s��
        void CreateFunction(void);
        // �X�V�������s��
        void UpdateFunction(void);
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
        // �ǉ�������
        virtual void Create(void) = 0;
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
        NativeGameObject* m_gameObject;             // �����Q�[���I�u�W�F�N�g
        std::vector<CollisionHitData> m_hitData;    // �Փ˃R���W�����f�[�^
        bool m_isStart; // ����Start�������s���Ă��邩
    };
}


#endif // !I_COMPONENTBASE_H
