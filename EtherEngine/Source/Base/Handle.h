#ifndef I_HANDLE_H
#define I_HANDLE_H
#include <Base/HandleSystem.h>


//----- Handle�錾
namespace EtherEngine {
    enum class HandleCountType {
        Count = 0,      // �Q�ƃJ�E���g���s��
        UnCount = 1,    // �Q�ƃJ�E���g���s��Ȃ�
    };


    // �Ώۂւ̎Q�Ƃ𐔒l�i�n���h���j�Ƃ��Ď������^
    // @ Temp1: �Ǘ��Ώی^
    // @ Temp2: �Q�ƃJ�E���g�A�b�v���s����(�f�t�H���g : �s��)
    template <HandleSystemConcept Type, HandleCountType Count = HandleCountType::Count>
    class Handle {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �����ԍ�
        Handle(const HandleNumberType& handleNumber);
        // �R���X�g���N�^
        Handle(void);
        // �f�X�g���N�^
        ~Handle(void);
        // �R�s�[�R���X�g���N�^
        Handle(const Handle<Type, Count>& copy);
        // ������Z�q(Copy)
        Handle<Type, Count>& operator=(const Handle<Type, Count>& copy);
        // ������Z�q(Move)
        Handle<Type, Count>& operator=(Handle<Type, Count>&& move);


        // ���̃n���h�����w�����̂��폜����
        void Delete(void);
        // ���̃n���h���̎Q�Ƃ��폜����
        void DeleteRef(void);


        // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        NonAtomicData<Type> GetNoAtomicItem(void) const;
        // Handle����r�����䂳�ꂽ�v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        AtomicData<Type> GetAtomicItem(void) const;
        // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        AtomicReadData<Type> GetAtomicReadItem(void) const;

        // Handle����r�����䂳��Ă��Ȃ��v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        Type& GetNoAtomicData(void) const;
        // Handle����r�����䂳�ꂽ�v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        Type& GetAtomicData(void) const;
        // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        Type& GetAtomicReadData(void) const;


        // ����Handle�̕ێ����Ă���ԍ��͗L����
        // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
        bool GetEnable(void) const;
        // ����Handle�̕ێ����Ă���ԍ��͗L����
        // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
        operator bool(void) const;


        // �������̂��w���Ă���n���h����
        bool operator ==(const Handle<Type, Count>& comparison);
        // �������̂��w���Ă��Ȃ��n���h����
        bool operator !=(const Handle<Type, Count>& comparison);


        // HandleNumber�擾
        HandleNumberType GetHandleNumberType(void) const;
        // HandleNumber�擾
        operator HandleNumberType(void) const;

    private:
        // �Q�Ƃ̃J�E���g�A�b�v���s��
        void CountUp(void);

        HandleNumberType m_handle; // ���g���ێ����Ă���Handle
    };


    // �Q�ƃn���h��
    // @ Memo : �Q�ƃJ�E���g���s��Ȃ�
    template <typename T>
    using RefHandle = Handle<T, HandleCountType::UnCount>;

    // �n���h���N���X�����肷��R���Z�v�g
    // @ Memo : �n���h���N���X�ł���� true
    template <typename T, typename Type> 
    concept HandleConcept = std::is_same_v<T, Handle<Type, HandleCountType::Count>> || std::is_same_v<T, Handle<Type, HandleCountType::UnCount>>;
    // �n���h�����Q�ƃJ�E���g���s�������ʂ���R���Z�v�g
    // @ Memo : �n���h���N���X�A���J�E���g�^�C�v�������ł���� true
    template <typename T, typename Type, HandleCountType Count>
    concept HandleCountTypeConcept = HandleConcept<T, Type>&& std::is_same_v<T, Handle<Type, Count>>;
}




//----- Handle����
namespace EtherEngine {
    // �R���X�g���N�^
    // @ Arg1 : �����ԍ�
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>::Handle(const HandleNumberType& handleNumber)
        : m_handle(handleNumber) {
        
    }
    // �R���X�g���N�^
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>::Handle(void)
        : Handle(0) {
        if constexpr (HandleCountType::Count == Count) {
            HandleSystem<Type>::Get()->CountDownItem(m_handle);
        }
    }
    // �f�X�g���N�^
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>::~Handle(void) {
        HandleSystem<Type>::Get()->CountDownItem(m_handle);
    }
    // �R�s�[�R���X�g���N�^
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>::Handle(const Handle<Type, Count>& copy)
        : m_handle(copy.m_handle){
        HandleSystem<Type>::Get()->CountUpItem(m_handle);
    }
    // ������Z�q(Copy)
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>& Handle<Type, Count>::operator=(const Handle<Type, Count>& copy) {
        m_handle = copy.m_handle;

    }
    // ������Z�q(Move)
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>& Handle<Type, Count>::operator=(Handle<Type, Count>&& move) {
        m_handle = move.m_handle;

        HandleSystem<Type>::Get()->CountUpItem(m_handle);
        return *this;
    }


    // ���̃n���h�����w�����̂��폜����
    template<HandleSystemConcept Type, HandleCountType Count>
    void Handle<Type, Count>::Delete(void) {
        HandleSystem<Type>::Get()->DeleteItem(m_handle);
    }
    // ���̃n���h���̎Q�Ƃ��폜����
    template<HandleSystemConcept Type, HandleCountType Count>
    void Handle<Type, Count>::DeleteRef(void) {

    }


    // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    template<HandleSystemConcept Type, HandleCountType Count>
    NonAtomicData<Type> Handle<Type, Count>::GetNoAtomicItem(void) const {
        return HandleSystem<Type>::Get()->GetNoAtomicItem(m_handle).value();
    }
    // Handle����r�����䂳�ꂽ�v�f���擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    template<HandleSystemConcept Type, HandleCountType Count>
    AtomicData<Type> Handle<Type, Count>::GetAtomicItem(void) const {
        return HandleSystem<Type>::Get()->GetAtomicItem(m_handle).value();
    }
    // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f���擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    template<HandleSystemConcept Type, HandleCountType Count>
    AtomicReadData<Type> Handle<Type, Count>::GetAtomicReadItem(void) const {
        return HandleSystem<Type>::Get()->GetAtomicReadItem(m_handle).value();
    }

    // Handle����r�����䂳��Ă��Ȃ��v�f�𒼐ڎ擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    template<HandleSystemConcept Type, HandleCountType Count>
    Type& Handle<Type, Count>::GetNoAtomicData(void) const {
        return GetNoAtomicItem().GetData();
    }
    // Handle����r�����䂳�ꂽ�v�f�𒼐ڎ擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    template<HandleSystemConcept Type, HandleCountType Count>
    Type& Handle<Type, Count>::GetAtomicData(void) const {
        return GetAtomicItem().GetData();
    }
    // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f�𒼐ڎ擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    template<HandleSystemConcept Type, HandleCountType Count>
    Type& Handle<Type, Count>::GetAtomicReadData(void) const {
        return GetAtomicReadItem().GetData();
    }


    // ����Handle�̕ێ����Ă���ԍ��͗L����
    // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
    template<HandleSystemConcept Type, HandleCountType Count>
    bool Handle<Type, Count>::GetEnable(void) const {
        return !(HandleSystem<Type>::Get()->IsItemEnable(m_handle));
    }
    // ����Handle�̕ێ����Ă���ԍ��͗L����
    // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>::operator bool(void) const {
        GetEnable();
    }


    // �������̂��w���Ă���n���h����
    template<HandleSystemConcept Type, HandleCountType Count>
    bool Handle<Type, Count>::operator ==(const Handle<Type, Count>& comparison) {
        return comparison == m_handle;
    }
    // �������̂��w���Ă��Ȃ��n���h����
    template<HandleSystemConcept Type, HandleCountType Count>
    bool Handle<Type, Count>::operator !=(const Handle<Type, Count>& comparison) {
        return comparison != m_handle;
    }


    // HandleNumber�擾
    template<HandleSystemConcept Type, HandleCountType Count>
    HandleNumberType Handle<Type, Count>::GetHandleNumberType(void) const {
        return m_handle;
    }
    // HandleNumber�擾
    template<HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count>::operator HandleNumberType(void) const {
        return GetHandleNumberType();
    }


    // �Q�Ƃ̃J�E���g�A�b�v���s��
    template<HandleSystemConcept Type, HandleCountType Count>
    void Handle<Type, Count>::CountUp(void) {
        if constexpr (HandleCountType::Count == Count) {
            HandleSystem<Type>::Get()->CountUpItem(m_handle);
        }
    }
}


#endif // !I_HANDLE_H
