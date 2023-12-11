#ifndef I_HANDLE_H
#define I_HANDLE_H
#include <Base/HandleSystem.h>
#include <Base/EditorException.h>
#include <Base/IDClass.h>


namespace EtherEngine {
    enum class HandleCountType : bool {
        Count = 0,      // �Q�ƃJ�E���g���s��
        UnCount,    // �Q�ƃJ�E���g���s��Ȃ�
    };


    // �n���h���Ƃ��Ďg�p�ł��邩���肷��R���Z�v�g
    // @ Memo : ���l�^�łȂ��A����HandleNumberType�ɕϊ��ł��邩
    template <typename T>
    concept UseHandleConcept = std::is_arithmetic_v<T> && std::is_convertible_v<T, IDClass>;
}


//----- Handle�錾
namespace EtherEngine {
    // �Ώۂւ̎Q�Ƃ𐔒l�i�n���h���j�Ƃ��Ď������^
    // @ Temp1: �Ǘ��Ώی^
    template <HandleSystemConcept Type>
    class Handle {
    public:
        // �R���X�g���N�^�\�z
        // @ Arg1 : �n���h���Ƃ��Ēǉ�����v�f
        // @ Arg2 : ���������J�E���g���邩(Default : �J�E���g����)
        Handle(Type&& item, HandleCountType countType = HandleCountType::Count);
        // ID�\�z�R���X�g���N�^
        // @ Arg1 : �R�s�[����ID
        // @ Arg2 : ���������J�E���g���邩(Default : �J�E���g����)
        Handle(IDClass id, HandleCountType countType = HandleCountType::Count);
        // �R���X�g���N�^
        // @ Arg1 : ���������J�E���g���邩(Default : �J�E���g����)
        Handle(HandleCountType countType = HandleCountType::Count);
        // �f�X�g���N�^
        ~Handle(void);
        // �R�s�[�R���X�g���N�^
        Handle(const Handle<Type>& copy);
        // ���[�u�R���X�g���N�^
        Handle(Handle<Type>&& move);
        // �R�s�[���
        Handle<Type>& operator =(const Handle<Type>& copy);
        // ���[�u���
        Handle<Type>& operator =(Handle<Type>&& move);


        // �Q�ƃJ�E���g���s�����Q�b�^�[
        HandleCountType GetIsCountUp(void) const { return m_count; }


        // �Q�ƃn���h�����쐬����
        // @ Ret  : �Q�ƃn���h��
        Handle<Type> GetRefHandle(void);


        // ���̃n���h�����w�����̂��폜����
        void Delete(void);


        // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
        // @ Ret  : �擾�����v�f
        NonAtomicData<Type> GetNoAtomicItem(void) const;
        // Handle����r�����䂳�ꂽ�v�f���擾����
        // @ Ret  : �擾�����v�f
        AtomicData<Type> GetAtomicItem(void) const;

        // Handle����r�����䂳��Ă��Ȃ��v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f
        Type& GetData(void) const;
        // Handle����r�����䂳�ꂽ�v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f
        Type& GetAtomicData(void) const;


        // ����Handle�̕ێ����Ă���ԍ��͗L����
        // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
        bool IsEnable(void) const;
        // ����Handle�̕ێ����Ă���ԍ��͗L����
        // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
        operator bool(void) const;


        // �������̂��w���Ă���n���h����
        bool operator ==(const Handle<Type>& comparison);
        // �������̂��w���Ă��Ȃ��n���h����
        bool operator !=(const Handle<Type>& comparison);


        // HandleNumber�擾
        IDClass GetHandleNumber(void) const;
        // HandleNumber�擾
        operator IDClass(void) const;

    protected:
        // �Q�Ƃ̃J�E���g�A�b�v���s��
        // @ Memo : ������s��
        void CountUp(void);
        // �Q�Ƃ̃J�E���g�_�E�����s��
        // @ Memo : ������s��
        void CountDown(void);

        IDClass m_id; // ���g���ێ����Ă���Handle
        HandleCountType m_count;   // �J�E���g�A�b�v���s����
        std::weak_ptr<ullint> m_deleteHandle;    // HandleSystem�폜����HandleSystem���g�p���邩
    };
}




//----- Handle����
namespace EtherEngine {
    // �R���X�g���N�^�\�z
    // @ Arg1 : �n���h���Ƃ��Ēǉ�����v�f
    // @ Arg2 : ���������J�E���g���邩
    template <HandleSystemConcept Type>
    Handle<Type>::Handle(Type&& item, HandleCountType countType)
        : Handle(countType) {
        //----- �n���h���Ƃ��č\�z
        auto handle = HandleSystem<Type>::Get()->AddItem(std::move(item));

        //----- �����o������
        m_id = handle.first;
        m_deleteHandle = handle.second;
    }
    // ID�\�z�R���X�g���N�^
    // @ Arg1 : �R�s�[����ID
    // @ Arg2 : ���������J�E���g���邩(Default : true)
    template <HandleSystemConcept Type>
    Handle<Type>::Handle(IDClass id, HandleCountType countType) 
        : Handle(countType) {
        //----- �����o������
        m_id = id;
        m_deleteHandle = HandleSystem<Type>::Get()->GetReferenceCount(m_id);
    }
    // �R���X�g���N�^�\�z
    // @ Arg1 : ���������J�E���g���邩
    template <HandleSystemConcept Type>
    Handle<Type>::Handle(HandleCountType countType) 
        : m_count(countType) {
        //----- �J�E���g�A�b�v
        CountUp();
    }
    // �f�X�g���N�^
    template<HandleSystemConcept Type>
    Handle<Type>::~Handle(void) {
        CountDown();
    }
    // �R�s�[�R���X�g���N�^
    template<HandleSystemConcept Type>
    Handle<Type>::Handle(const Handle<Type>& copy)
        : m_id(copy.m_id) 
        , m_count(copy.m_count) 
        , m_deleteHandle(copy.m_deleteHandle) {
        CountUp();
    }
    // ���[�u�R���X�g���N�^
    template<HandleSystemConcept Type>
    Handle<Type>::Handle(Handle<Type>&& move)
        : m_id(move.m_id)
        , m_count(move.m_count)
        , m_deleteHandle(move.m_deleteHandle) {
        CountUp();
    }
    // �R�s�[���
    template<HandleSystemConcept Type>
    Handle<Type>& Handle<Type>::operator =(const Handle<Type>& copy) {
        m_id = copy.m_id;
        m_count = copy.m_count;
        m_deleteHandle = copy.m_deleteHandle;
        CountUp();
    }
    // ���[�u���
    template<HandleSystemConcept Type>
    Handle<Type>& Handle<Type>::operator =(Handle<Type>&& move) {
        m_id = move.m_id;
        m_count = move.m_count;
        m_deleteHandle = move.m_deleteHandle;
        CountUp();
    }


    // �Q�ƃn���h�����쐬����
    // @ Ret  : �Q�ƃn���h��
    template<HandleSystemConcept Type>
    Handle<Type> Handle<Type>::GetRefHandle(void) {
        return Handle(m_id, HandleCountType::UnCount);
    }


    // ���̃n���h�����w�����̂��폜����
    template<HandleSystemConcept Type>
    void Handle<Type>::Delete(void) {
        HandleSystem<Type>::Get()->DeleteItem(m_id);
    }


    // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    NonAtomicData<Type> Handle<Type>::GetNoAtomicItem(void) const {
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");
        return HandleSystem<Type>::Get()->GetNoAtomicItem(m_id).value();
    }
    // Handle����r�����䂳�ꂽ�v�f���擾����
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    AtomicData<Type> Handle<Type>::GetAtomicItem(void) const {
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");
        return HandleSystem<Type>::Get()->GetAtomicItem(m_id).value();
    }


    // Handle����r�����䂳��Ă��Ȃ��v�f�𒼐ڎ擾����
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    Type& Handle<Type>::GetData(void) const {
        return GetNoAtomicItem().GetData();
    }
    // Handle����r�����䂳�ꂽ�v�f�𒼐ڎ擾����
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    Type& Handle<Type>::GetAtomicData(void) const {
        return GetAtomicItem().GetData();
    }


    // ����Handle�̕ێ����Ă���ԍ��͗L����
    // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
    template<HandleSystemConcept Type>
    bool Handle<Type>::IsEnable(void) const {
        return HandleSystem<Type>::Get()->IsItemEnable(m_id);
    }
    // ����Handle�̕ێ����Ă���ԍ��͗L����
    // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
    template<HandleSystemConcept Type>
    Handle<Type>::operator bool(void) const {
        return IsEnable();
    }


    // �������̂��w���Ă���n���h����
    template<HandleSystemConcept Type>
    bool Handle<Type>::operator ==(const Handle<Type>& comparison) {
        return comparison.GetHandleNumber() == m_id;
    }
    // �������̂��w���Ă��Ȃ��n���h����
    template<HandleSystemConcept Type>
    bool Handle<Type>::operator !=(const Handle<Type>& comparison) {
        return comparison.GetHandleNumber() != m_id;
    }


    // HandleNumber�擾
    template<HandleSystemConcept Type>
    IDClass Handle<Type>::GetHandleNumber(void) const {
        return m_id;
    }
    // HandleNumber�擾
    template<HandleSystemConcept Type>
    Handle<Type>::operator IDClass(void) const {
        return GetHandleNumber();
    }


    // �Q�Ƃ̃J�E���g�A�b�v���s��
    template<HandleSystemConcept Type>
    void Handle<Type>::CountUp(void) {
        if (m_count == HandleCountType::Count && m_deleteHandle.expired() == false) {
            HandleSystem<Type>::Get()->CountUpItem(m_id);
        }
    }
    // �Q�Ƃ̃J�E���g�_�E�����s��
    template<HandleSystemConcept Type>
    void Handle<Type>::CountDown(void) {
        if (m_count == HandleCountType::Count && m_deleteHandle.expired() == false) {
            HandleSystem<Type>::Get()->CountDownItem(m_id);
        }
    }
}


#endif // !I_HANDLE_H
