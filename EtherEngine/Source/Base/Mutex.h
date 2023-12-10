#ifndef I_MUTEX_H
#define I_MUTEX_H
#include <Base/RAIIClass.h>


//----- Mutex �錾
namespace EtherEngine {
    using MutexLockKey = RAIIClass;


    // mutex�̃��b�v�N���X
    class Mutex {
    public:
        // �R���X�g���N�^
        Mutex(void);
        // �f�X�g���N�^
        ~Mutex(void);
        // �R�s�[�R���X�g���N�^
        Mutex(const Mutex& move) = default;
        // ���[�u�R���X�g���N�^
        Mutex(Mutex&& move) = default;


        // ���b�N�����s����
        // @ Memo : �X���b�h�����b�N����܂�
        bool TryLock(void);
        // ���b�N���{�s�ł��邩�擾
        // @ Ret  : ���b�N���{�s�ł��邩
        bool IsCanLock(void);


        // ���b�N���s���iRAII�j
        // @ Ret  : RAII���b�N�E�A�����b�N�N���X
        MutexLockKey KeyLock(void);
        // ���b�N���s���iRAII�j
        // @ Ret  : RAII���b�N�E�A�����b�N�N���X
        MutexLockKey KeySpinLock(void);


        // �蓮���b�N���s��
        void Lock(void);
        // �蓮�X�s�����b�N���s��
        void SpinLock(void);
        // �蓮�A�����b�N���s��
        void UnLock(void);

    protected:
        // ���b�N�J�n��ʒm����
        // @ Ret  : ���b�N���\��
        bool LockMessage(void);
        // ���b�N������ʒm����
        // @ Ret  : ���b�N�������\��
        bool UnLockMessage(void);


        // ���g�̃��b�N���s��
        // @ Memo : �������̂̓X�s�����b�N�ōs���܂�
        MutexLockKey ThisLock(void);


        HANDLE m_mutex;     // �~���[�e�b�N�X�̃n���h��
        HANDLE m_thisMutex; // ���g�ɍs���r������
        static thread_local uint ms_thisThreadLockCount;   // ���g�̃X���b�h�̃��b�N��
    };
}


#endif // !I_MUTEX_H
