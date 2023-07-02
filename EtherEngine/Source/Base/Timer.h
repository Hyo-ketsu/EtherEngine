#ifndef I_TIMERBASE_H
#define I_TIMERBASE_H

#include <Base/Singleton.h>


namespace EtherEngine {
    // �^�C�}�[
    class Timer {
    public:
        // ���ݎ��Ԃ��擾����
        // @ Ret  :  ���ݎ���
        std::chrono::nanoseconds GetTime(void);


        // �O�񂩂�̌o�ߎ��Ԃ��擾����
        // @ Memo : ���g�p�̍ۂ�0��ԋp���܂�
        // @ Ret  : �O��DeltaTime�g�p������̌o�ߎ���
        std::chrono::nanoseconds GetDeltaTime(void);

    private:
        std::optional<std::chrono::steady_clock::time_point> m_deltaTime;   // �O��DeltaTime�g�p������
    };


    // �O���[�o���^�C�}�[
    class GlobalTimer : public Singleton<GlobalTimer> {
    public:
        // �f�X�g���N�^
        ~GlobalTimer(void) override {}


        // ������
        // @ Memo : ���̏��������s�������Ԃ��N�_�ɂ��܂�
        void Init(void);
        // �I��
        void Uninit(void);


        // �O���[�o���^�C�����擾����
        // @ Ret  : GlobalTimer����������̌o�ߎ���
        std::chrono::nanoseconds GetGlobalTime(void);

    private:
        // �R���X�g���N�^
        GlobalTimer(void) {}


        std::optional<std::chrono::steady_clock::time_point> m_firstTime;   // ����������

        friend class Singleton<GlobalTimer>;
    };
}


#endif // !I_TIMER_H
