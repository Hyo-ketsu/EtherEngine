#ifndef I_ATOMIC_H
#define I_ATOMIC_H
#include <Base/AtomicData.h>
#include <Base/NonAtomicData.h>
#include <Base/ThreadingUtility.h>
#include <Base/Mutex.h>


namespace EtherEngine {
    // �r��������s���N���X
    // @ Temp : �r�����s���^
    template <class AtomicType>
    class Atomic {
    public:
        Atomic(const Atomic&) = delete;


        // �f�t�H���g�R���X�g���N�^
        Atomic(void);
        // �R���X�g���N�^
        // @ Arg1 : �r�����s�����
        Atomic(AtomicType&& data);
        // �f�X�g���N�^
        ~Atomic(void) noexcept;
        // ���[�u�R���X�g���N�^
        // @ Memo : ���L���̈ړ���\�����Ă��܂�
        Atomic(Atomic&& move) noexcept;


        // �f�[�^���擾����
        // @ Ret  : �r�����䂳�ꂽ�f�[�^
        AtomicData<AtomicType> GetData(void);
        // �f�[�^���擾����
        // @ Ret  : �r�����䂳��Ă��Ȃ��f�[�^
        NonAtomicData<AtomicType> GetNonAtomicData(void);


        // ���b�N���擾�ł��邩
        // @ Ret  : ���b�N���擾�ł���i= ���b�N����Ă��Ȃ��j�Ȃ� true
        bool TryLock(void);

    private:
        std::unique_ptr<AtomicType> m_lock;  // �ێ����Ă���f�[�^
        Mutex m_mutex; // �r���p�~���[�e�b�N�X
    };
}




//----- Atomic����
namespace EtherEngine {
    // �f�t�H���g�R���X�g���N�^
    template <class AtomicType>
    Atomic<AtomicType>::Atomic(void)
        : m_lock(nullptr){
    }
    // �R���X�g���N�^
    // @ Arg1 : �r�����s�����
    template <class AtomicType>
    Atomic<AtomicType>::Atomic(AtomicType&& data) 
        : m_lock(std::make_unique<AtomicType>(data)){
    }
    // �f�X�g���N�^
    template <class AtomicType>
    Atomic<AtomicType>::~Atomic(void) noexcept {
    }
    // ���[�u�R���X�g���N�^
    // @ Memo : ���L���̈ړ���\�����Ă��܂�
    template <class AtomicType>
    Atomic<AtomicType>::Atomic(Atomic&& move) noexcept {
        //----- ���b�N���s��
        auto lock = move.m_mutex.KeyLock();

        //----- ���[�u
        m_lock = std::move(move.m_lock);
    }


    // �f�[�^���擾����
    // @ Ret  : �r�����䂳�ꂽ�f�[�^
    template <class AtomicType>
    AtomicData<AtomicType> Atomic<AtomicType>::GetData(void) {
        //----- �r���f�[�^�̍쐬�ƕԋp
        return std::move(AtomicData<AtomicType>(*m_lock,
            [this](void) -> void { m_mutex.Lock(); }, [this](void) -> void { m_mutex.UnLock(); }));
    }
    // �f�[�^���擾����
    // @ Ret  : �r�����䂳��Ă��Ȃ��f�[�^
    template <class AtomicType>
    NonAtomicData<AtomicType> Atomic<AtomicType>::GetNonAtomicData(void) {
        //----- �r���f�[�^�̍쐬�ƕԋp
        return std::move(NonAtomicData<AtomicType>(*m_lock));
    }


    // ���b�N���擾�ł��邩
    // @ Ret  : ���b�N���擾�ł���i= ���b�N����Ă��Ȃ��j�Ȃ� true
    template <class AtomicType>
    bool Atomic<AtomicType>::TryLock(void) {
        bool lock = m_mutex.IsCanLock();
        return lock;
    }
}

#endif // !I_ATOMIC_H
