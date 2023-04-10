#ifndef I_ATOMIC_H
#define I_ATOMIC_H
#include <Base/AtomicData.h>
#include <Base/AtomicReadData.h>
#include <Base/NonAtomicData.h>


namespace EtherEngine {
    // �r��������s���N���X
    // @ Temp : �r�����s���^
    template <class AtomicType>
    class Atomic {
    public:
        Atomic(const Atomic&) = delete;
        Atomic& operator=(const Atomic&) = delete;


        // �R���X�g���N�^
        // @ Memo : �����͉E�Ӓl�̂ݎ󂯕t���܂�
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
        // �ǂݎ���p�f�[�^���擾����
        // @ Ret  : �r�����䂳�ꂽ�ǂݎ���p�f�[�^
        AtomicReadData<AtomicType> GetReadData(void);


        // ���b�N���擾�ł��邩
        // @ Ret  : ���b�N���擾�ł���i= ���b�N����Ă��Ȃ��j�Ȃ� true
        bool TryLock(void);
        // �ǂݎ�胍�b�N���擾�ł��邩
        // @ Ret  : ���b�N���擾�ł���i= ���b�N����Ă��Ȃ��j�Ȃ� true
        bool TryReadLock(void);


    private:
        std::unique_ptr<AtomicType> m_data;  // �ێ����Ă���f�[�^
        std::recursive_mutex        m_mutex; // �r���p�~���[�e�b�N�X
        std::mutex                m_readMutex;     // �ǂݎ�胍�b�N�p�~���[�e�b�N�X
        std::condition_variable   m_readCondition; // �ǂݎ�胍�b�N�p�����ϐ�
        std::atomic<unsigned int> m_readCount;     // �ǂݎ�胍�b�N�pRead��
    };
}




//----- Atomic����
namespace EtherEngine {
    // �R���X�g���N�^
    // @ Memo : �����̓��[�u���ꂽ���̂̂ݎ󂯕t���܂�
    // @ Arg1 : �r�����s�����
    template <class AtomicType>
    Atomic<AtomicType>::Atomic(AtomicType&& data)
        : m_data(std::make_unique<AtomicType>(data)) {
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
        {
            std::lock_guard<std::recursive_mutex> lock(move.m_mutex);

            //----- �ǂݎ�胍�b�N������Ă��邩
            if (m_readCount.load() > 0) {
                //----- �ǂݍ��ݐ���1�ȏ�B�ǂݎ�胍�b�N�i�������ݑ��̃X���b�h��Q�����j���s��
                std::unique_lock<std::mutex> lock(m_readMutex);
                m_readCondition.wait(lock, [this] {return m_readCount.load() > 0; });
            }
        }

        //----- ���[�u
        m_data = std::move(move.m_data);
        m_mutex = std::move(move.m_mutex);
    }


    // �f�[�^���擾����
    // @ Ret  : �r�����䂳�ꂽ�f�[�^
    template <class AtomicType>
    AtomicData<AtomicType> Atomic<AtomicType>::GetData(void) {
        //----- �������݂��I������܂őҋ@����
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        //----- �ǂݎ�胍�b�N������Ă��邩
        if (m_readCount.load() > 0) {
            //----- �ǂݍ��ݐ���1�ȏ�B�ǂݎ�胍�b�N�i�������ݑ��̃X���b�h��Q�����j���s��
            std::unique_lock<std::mutex> lock(m_readMutex);
            m_readCondition.wait(lock, [this] {return m_readCount.load() > 0; });
        }

        //----- �r���f�[�^�̍쐬�ƕԋp
        return std::move(AtomicData<AtomicType>(*m_data,
            [this](void) -> void { m_mutex.lock(); }, [this](void) -> void { m_mutex.unlock(); }));
    }
    // �f�[�^���擾����
    // @ Ret  : �r�����䂳��Ă��Ȃ��f�[�^
    template <class AtomicType>
    NonAtomicData<AtomicType> Atomic<AtomicType>::GetNonAtomicData(void) {
        //----- �������݂��I������܂őҋ@����
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        //----- �ǂݎ�胍�b�N������Ă��邩
        if (m_readCount.load() > 0) {
            //----- �ǂݍ��ݐ���1�ȏ�B�ǂݎ�胍�b�N�i�������ݑ��̃X���b�h��Q�����j���s��
            std::unique_lock<std::mutex> lock(m_readMutex);
            m_readCondition.wait(lock, [this] {return m_readCount.load() > 0; });
        }

        //----- �r���f�[�^�̍쐬�ƕԋp
        return std::move(NonAtomicData<AtomicType>(*m_data,
            [this](void) -> void {}, [this](void) -> void {}));
    }
    // �ǂݎ���p�f�[�^���擾����
    // @ Ret  : �r�����䂳�ꂽ�ǂݎ���p�f�[�^
    template <class AtomicType>
    AtomicReadData<AtomicType> Atomic<AtomicType>::GetReadData(void) {
        //----- �������݂��I������܂őҋ@����
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        //----- �r���f�[�^�̍쐬�ƕԋp
        return std::move(AtomicReadData<AtomicType>(*m_data,
            [this](void) -> void { m_readCount.store(m_readCount.load() + 1); }, [this](void) -> void { m_readCount.store(m_readCount.load() - 1); }));
    }


    // ���b�N���擾�ł��邩
    // @ Ret  : ���b�N���擾�ł���i= ���b�N����Ă��Ȃ��j�Ȃ� true
    template <class AtomicType>
    bool Atomic<AtomicType>::TryLock(void) {
        bool lock = m_mutex.try_lock();
        bool read = m_readMutex.try_lock();
        if (lock) m_mutex.unlock();
        if (read) m_readMutex.unlock();
        return lock && read;
    }
    // �ǂݎ�胍�b�N���擾�ł��邩
    // @ Ret  : ���b�N���擾�ł���i= ���b�N����Ă��Ȃ��j�Ȃ� true
    template <class AtomicType>
    bool Atomic<AtomicType>::TryReadLock(void) {
        bool lock = m_mutex.try_lock();
        if (lock) m_mutex.unlock();
        return lock;
    }
}

#endif // !I_ATOMIC_H
