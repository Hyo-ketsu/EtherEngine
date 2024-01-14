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
        Mutex(const Mutex& move) = delete;
        // ���[�u�R���X�g���N�^
        Mutex(Mutex&& move) = default;
        // �R�s�[���
        Mutex& operator =(const Mutex& move) = delete;
        // ���[�u���
        Mutex& operator =(Mutex&& move) = default;


        // ���b�N�����s����
        // @ Memo : �X���b�h�����b�N����܂�
        bool TryLock(void) const;
        // ���b�N���{�s�ł��邩�擾
        // @ Ret  : ���b�N���{�s�ł��邩
        bool IsCanLock(void) const;


        // ���b�N���s���iRAII�j
        // @ Ret  : RAII���b�N�E�A�����b�N�N���X
        MutexLockKey KeyLock(void) const;
        // ���b�N���s���iRAII�j
        // @ Ret  : RAII���b�N�E�A�����b�N�N���X
        MutexLockKey KeySpinLock(void) const;


        // �蓮���b�N���s��
        void Lock(void) const;
        // �蓮�X�s�����b�N���s��
        void SpinLock(void) const;
        // �蓮�A�����b�N���s��
        void UnLock(void) const;

    protected:
        // ���b�N�J�n��ʒm����
        // @ Ret  : ���b�N���\��
        bool LockMessage(void) const;
        // ���b�N������ʒm����
        // @ Ret  : ���b�N�������\��
        bool UnLockMessage(void) const;


        // ���g�̃��b�N���s��
        // @ Memo : �������̂̓X�s�����b�N�ōs���܂�
        MutexLockKey ThisLock(void) const;


        HANDLE m_mutex;     // �~���[�e�b�N�X�̃n���h��
        HANDLE m_thisMutex; // ���g�ɍs���r������
        static thread_local uint ms_thisThreadLockCount;   // ���g�̃X���b�h�̃��b�N��
    };
}


#endif // !I_MUTEX_H
