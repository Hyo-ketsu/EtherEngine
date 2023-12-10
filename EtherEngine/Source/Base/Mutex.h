#ifndef I_MUTEX_H
#define I_MUTEX_H
#include <Base/RAIIClass.h>
#include <Base/ManageMediation.h>


// @ Memo : ��`���̂͂����ł���Ă��܂���B


//----- Mutex �錾
namespace EtherEngine {
    // mutex�̃��b�v�N���X
    class Mutex {
    protected:
        // ���b�N��RAII�ɑ���s���N���X
        class MutexLockKey {
        public:
            // �R���X�g���N�^
            // @ Arg1 : �e���̎Q��
            MutexLockKey(Mutex& lock);
            // �f�X�g���N�^
            ~MutexLockKey(void);

        private:
            Mutex& m_lock;
        };

    public:
        // �f�X�g���N�^
        virtual ~Mutex(void) {}
        // �R�s�[�R���X�g���N�^
        Mutex(const Mutex& move) = default;
        // ���[�u�R���X�g���N�^
        Mutex(Mutex&& move) = default;


        // ���b�N�����s����
        // @ Memo : �X���b�h�����b�N����܂�
        virtual bool TryLock(void) = 0;
        // ���b�N���{�s�ł��邩�擾
        // @ Ret  : ���b�N���{�s�ł��邩
        virtual bool IsCanLock(void) = 0;


        // ���b�N���s���iRAII�j
        // @ Ret  : RAII���b�N�E�A�����b�N�N���X
        virtual MutexLockKey KeyLock(void) = 0;
        // ���b�N���s���iRAII�j
        // @ Ret  : RAII���b�N�E�A�����b�N�N���X
        virtual MutexLockKey KeySpinLock(void) = 0;


        // �蓮���b�N���s��
        virtual void Lock(void) = 0;
        // �蓮�X�s�����b�N���s��
        virtual void SpinLock(void) = 0;
        // �蓮�A�����b�N���s��
        virtual void UnLock(void) = 0;

    protected:
        // �R���X�g���N�^
        Mutex(void) {}


        // ���b�N�J�n��ʒm����
        // @ Ret  : ���b�N���\��
        bool LockMessage(void);
        // ���b�N������ʒm����
        // @ Ret  : ���b�N�������\��
        bool UnLockMessage(void);


        // ���g�̃��b�N���s��
        // @ Memo : �������̂̓X�s�����b�N�ōs���܂�
        virtual MutexLockKey ThisLock(void) = 0;


        static thread_local uint ms_thisThreadLockCount;   // ���g�̃X���b�h�̃��b�N��
    };
}


#endif // !I_MUTEX_H
