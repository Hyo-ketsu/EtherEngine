#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H
#include <Base/Handle.h>


//----- ComponentBase�錾
namespace EtherEngine {
    // �R���|�[�l���g�̊�b�ƂȂ�N���X
    class ComponentBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �Q�[���I�u�W�F�N�g
        ComponentBase(void* gameObject);
        // �f�X�g���N�^
        ~ComponentBase(void);
        ComponentBase(const ComponentBase& copy) = delete;
        // ���[�u�R���X�g���N�^
        ComponentBase(ComponentBase&& move) = default;


        // �����Q�[���I�u�W�F�N�g�̎擾
        // @ MEMO : �z�Q�Ƃ̊֌W��ʓ|�Ȃ��ƂɂȂ��Ă��܂��B�w���p�[�����g�p���������B
        // @ Arg1 : �Q�[���I�u�W�F�N�g���i�[����
        void GetGameObject(void** gameObject) const;


        // �X�V�������s��
        void UpdateFuntion(void);

    protected:
        virtual void Start(void) {}
        virtual void Update(void) {}

    private:
        class GameObject* m_gameObject;   // �����Q�[���I�u�W�F�N�g
        bool m_isStart; // ����Start�������s���Ă��邩
    };
}


#endif // !I_COMPONENTBASE_H
