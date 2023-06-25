#ifndef I_SPINLOCK_H
#define I_SPINLOCK_H


namespace EtherEngine {
    // �X�s�����b�N���Ȍ��Ɏ�������N���X
    class SpinLock {
    private:
        // �X�s�����b�N��RAII�ɑ���s���N���X
        class SpinLockKey {
        public:
            // �R���X�g���N�^
            // @ Arg1 : �e���̎Q��
            SpinLockKey(SpinLock& lock);
            // �f�X�g���N�^
            ~SpinLockKey(void);

        private:
            SpinLock& m_spinlock;
        };

    public:
        // �R���X�g���N�^
        SpinLock(void);
        // �f�X�g���N�^
        ~SpinLock(void);


        // �X�s�����b�N�����s����
        void DoSpinLock(void);


        // ���b�N���s���iRAII�j
        // @ Ret  : RAII���b�N�E�A�����b�N�N���X
        SpinLockKey KeyLock(void);
        // �蓮���b�N���s��
        void Lock(void);
        // �蓮�A�����b�N���s��
        void UnLock(void);

    private:
        std::recursive_mutex m_mutex;  // �X�s�����b�N�ɗp����~���[�e�b�N�X
        std::atomic_bool m_isAtomic;   // �X�s�����b�N�ɗp����AtomicBool
    };
}


#endif // !I_SPINLOCK_H
