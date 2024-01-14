#ifndef I_EXCLUSIONOBJECT_H
#define I_EXCLUSIONOBJECT_H
#include <Base/ExclusionData.h>
#include <Base/NonExclusionData.h>
#include <Base/Mutex.h>


//----- ExclusionObject �錾
namespace EtherEngine {
    // �r��������s���N���X
    // @ Temp : �r�����s���^
    template <class AtomicType>
    class ExclusionObject {
    public:
        // �f�t�H���g�R���X�g���N�^
        ExclusionObject(void);
        // �R���X�g���N�^
        // @ Arg1 : �r�����s�����
        ExclusionObject(AtomicType&& data);
        // �f�X�g���N�^
        ~ExclusionObject(void) noexcept;
        // �R�s�[�R���X�g���N�^
        ExclusionObject(const ExclusionObject& copy) = delete;
        // ���[�u�R���X�g���N�^
        ExclusionObject(ExclusionObject&& move) = default;
        // �R�s�[���
        ExclusionObject& operator =(const ExclusionObject& copy) = delete;
        // ���[�u���
        ExclusionObject& operator =(ExclusionObject&& move) = default;


        // �f�[�^���擾����
        // @ Ret  : �r�����䂳�ꂽ�f�[�^
        ExclusionData<AtomicType> GetData(void) const;
        // �f�[�^���擾����
        // @ Ret  : �r�����䂳��Ă��Ȃ��f�[�^
        NonExclusionData<AtomicType> GetNonExclusionData(void) const;


        // ���b�N���擾�ł��邩
        // @ Ret  : ���b�N���擾�ł���i= ���b�N����Ă��Ȃ��j�Ȃ� true
        bool TryLock(void) const;
        // ���b�N����
        void Look(void) const;
        // �A�����b�N����
        void UnLock(void) const;

    private:
        std::shared_ptr<AtomicType> m_lock;  // �ێ����Ă���f�[�^
        Mutex m_mutex; // �r���p�~���[�e�b�N�X
    };
}




//----- ExclusionObject ����
namespace EtherEngine {
    // �f�t�H���g�R���X�g���N�^
    template <class AtomicType>
    ExclusionObject<AtomicType>::ExclusionObject(void)
        : m_lock(nullptr) {
    }
    // �R���X�g���N�^
    // @ Arg1 : �r�����s�����
    template <class AtomicType>
    ExclusionObject<AtomicType>::ExclusionObject(AtomicType&& data) 
        : m_lock(std::make_shared<AtomicType>(data)) {
    }
    // �f�X�g���N�^
    template <class AtomicType>
    ExclusionObject<AtomicType>::~ExclusionObject(void) noexcept {
    }


    // �f�[�^���擾����
    // @ Ret  : �r�����䂳�ꂽ�f�[�^
    template <class AtomicType>
    ExclusionData<AtomicType> ExclusionObject<AtomicType>::GetData(void) const {
        //----- �r���f�[�^�̍쐬�ƕԋp
        return std::move(ExclusionData<AtomicType>(*m_lock,
            [this](void) -> void { m_mutex.Lock(); }, [this](void) -> void { m_mutex.UnLock(); }));
    }
    // �f�[�^���擾����
    // @ Ret  : �r�����䂳��Ă��Ȃ��f�[�^
    template <class AtomicType>
    NonExclusionData<AtomicType> ExclusionObject<AtomicType>::GetNonExclusionData(void) const {
        //----- �r���f�[�^�̍쐬�ƕԋp
        return std::move(NonExclusionData<AtomicType>(*m_lock));
    }


    // ���b�N���擾�ł��邩
    // @ Ret  : ���b�N���擾�ł���i= ���b�N����Ă��Ȃ��j�Ȃ� true
    template <class AtomicType>
    bool ExclusionObject<AtomicType>::TryLock(void) const {
        bool lock = m_mutex.IsCanLock();
        return lock;
    }
    // ���b�N����
    template <class AtomicType>
    void ExclusionObject<AtomicType>::Look(void) const {
        m_mutex.Lock();
    }
    template <class AtomicType>
    // �A�����b�N����
    void ExclusionObject<AtomicType>::UnLock(void) const {
        m_mutex.UnLock();
    }
}

#endif // !I_EXCLUSIONOBJECT_H
