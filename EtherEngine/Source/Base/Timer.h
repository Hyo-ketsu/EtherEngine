#ifndef I_TIMERBASE_H
#define I_TIMERBASE_H
#include <Base/Singleton.h>


//----- �ʖ���`
namespace EtherEngine {
    using milliSecond = float;
}


//----- �O���錾
namespace EtherEngine {
    namespace ForwardDeclaration {
        // TimePointer�p�O���錾
        class TimePointer;
    }
}


//----- Timer �錾
namespace EtherEngine {
    // �^�C�}�[
    class Timer {
    public:
        // �R���X�g���N�^
        Timer(void);
        // �f�X�g���N�^
        virtual ~Timer(void);
        // �R�s�[�R���X�g���N�^
        Timer(const Timer& copy) = default;
        // ���[�u�R���X�g���N�^
        Timer(Timer&& move) = default;


        // ���ݎ��Ԃ��擾����
        // @ Ret  :  ���ݎ���
        milliSecond GetTime(void);
        // �O�񂩂�̌o�ߎ��Ԃ��擾����
        // @ Memo : ���g�p�̍ۂ�0��ԋp���܂�
        // @ Ret  : �O��DeltaTime�g�p������̌o�ߎ���
        milliSecond GetDeltaTime(void);


        // @ MEMO : ���C�ƕK�v�������
        // ���ݎ��Ԃ�YYYY/MM/DD/ HH:MM:SS�`���ŏo�͂���


    private:
        class ForwardDeclaration::TimePointer* m_deltaTime;   // Timer�̌��ݕێ�����
    };
}


//----- GlobalTimer �錾
namespace EtherEngine {
    // �O���[�o���^�C�}�[
    class GlobalTimer : public Singleton<GlobalTimer> {
    public:
        // �f�X�g���N�^
        ~GlobalTimer(void) override;


        // ������
        // @ Memo : ���̏��������s�������Ԃ��N�_�ɂ��܂�
        void Init(void);
        // �X�V����
        void Update(void);
        // �I��
        void Uninit(void);


        // �O���[�o���^�C�����擾����
        // @ Ret  : GlobalTimer����������̌o�ߎ���
        milliSecond GetGlobalTime(void);
        // 1�t���[���b�����擾����
        // @ Ret  : �o�ߎ���

    private:
        // �R���X�g���N�^
        GlobalTimer(void);


        ForwardDeclaration::TimePointer* m_firstTime;   // ����������
        ForwardDeclaration::TimePointer* m_updateTime;  // �t���[���J�n����

        friend class CentrallySingleton;
    };
}


#endif // !I_TIMER_H
