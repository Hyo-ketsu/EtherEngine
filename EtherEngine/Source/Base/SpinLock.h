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
            // @ Arg1 : �R���X�g���N�^�ōs������
            // @ Arg2 : �f�X�g���N�^�ōs������
            SpinLockKey(std::function<void(void)> constructor, std::function<void(void)> destructor);
            // �f�X�g���N�^
            ~SpinLockKey(void);

        private:

            std::function<void(void)> m_destructor; // �f�X�g���N�^�ōs������
        };

    public:


        // �R���X�g���N�^
        SpinLock(void);
        // �f�X�g���N�^
        ~SpinLock(void);


        // �X�s�����b�N�����s����
        void DoSpinLock(void) const noexcept;


        // ���b�N���s���iRAII�j
        // @ Ret  : RAII���b�N�E�A�����b�N�N���X
        SpinLockKey KeyLock(void);
        // �蓮���b�N���s��
        void Lock(void);
        // �蓮�A�����b�N���s��
        void UnLock(void);

    private:
        std::atomic_bool m_isAtomicBool;  // �X�s�����b�N�ɗp����r��bool
    };
}


#endif // !I_SPINLOCK_H
