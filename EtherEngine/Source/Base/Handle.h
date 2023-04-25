#ifndef I_HANDLE_H
#define I_HANDLE_H
#include <Base/HandleSystem.h>



//----- Handle�錾
namespace EtherEngine {
    // Handle
    // @ Temp : �Ǘ��Ώی^
    template <HandleSystemConcept Type>
    class Handle {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �����ԍ�
        Handle(HandleNumberType handleNumber);
        // �f�X�g���N�^
        ~Handle(void);
        // �R�s�[�R���X�g���N�^
        Handle(const Handle<Type>& copy);
        // ������Z�q(Copy)
        Handle<Type>& operator=(const Handle<Type>& copy);
        // ������Z�q(Move)
        Handle<Type>& operator=(Handle<Type>&& move);


        // ���̃n���h�����w�����̂��폜����
        void Delete(void);


        // �R���X�g���N�^�����Z�b�^�[
        // @ Memo : �������̂݉�
        void SetConstructor(std::function<void(void)> in) { if (m_constructor == nullptr) m_constructor = in; }
        // �f�X�g���N�^�����Z�b�^�[
        // @ Memo : �������̂݉�
        void SetDestructor(std::function<void(void)> in) { if (m_destructor == nullptr) m_destructor = in; }


        // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        std::optional<NonAtomicData<Type>> GetNoAtomicItem(void) const;
        // Handle����r�����䂳�ꂽ�v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        std::optional<AtomicData<Type>> GetAtomicItem(void) const;
        // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        std::optional<AtomicReadData<Type>> GetAtomicReadItem(void) const;


        // ����Handle�̕ێ����Ă���ԍ��͗L����
        // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
        bool GetEnable(void) const;
        // ����Handle�̕ێ����Ă���ԍ��͗L����
        // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
        operator bool(void) const;


        // HandleNumber�擾
        operator HandleNumberType(void) const;

    private:
        std::optional<HandleNumberType> m_handle; // ���g���ێ����Ă���Handle
        std::function<void(void)> m_constructor;  // ����������
        std::function<void(void)> m_destructor;   // �I��������
    };
}




//----- Handle����
namespace EtherEngine {
    // �R���X�g���N�^
    // @ Arg1 : �����ԍ�
    template<HandleSystemConcept Type>
    Handle<Type>::Handle(HandleNumberType handleNumber)
        : m_handle(handleNumber)
        , m_constructor(nullptr)
        , m_destructor(nullptr) {
    }
    // �f�X�g���N�^
    template<HandleSystemConcept Type>
    Handle<Type>::~Handle(void) {
        if (m_destructor != nullptr) m_destructor();
    }
    // �R�s�[�R���X�g���N�^
    template<HandleSystemConcept Type>
    Handle<Type>::Handle(const Handle<Type>& copy)
        : m_handle(copy.m_handle)
        , m_constructor(copy.m_constructor)
        , m_destructor(copy.m_destructor) {
        if (m_constructor != nullptr) m_constructor();
    }
    // ������Z�q(Copy)
    template<HandleSystemConcept Type>
    Handle<Type>& Handle<Type>::operator=(const Handle<Type>& copy) {
        m_handle = copy.m_handle;
        m_constructor = copy.m_constructor;
        m_destructor = copy.m_destructor;

        if (m_constructor != nullptr) m_constructor();
    }
    // ������Z�q(Move)
    template<HandleSystemConcept Type>
    Handle<Type>& Handle<Type>::operator=(Handle<Type>&& move) {
        m_handle = move.m_handle;
        m_constructor = move.m_constructor;
        m_destructor = move.m_destructor;

        if (m_constructor != nullptr) m_constructor();
    }


    // ���̃n���h�����w�����̂��폜����
    template<HandleSystemConcept Type>
    void Handle<Type>::Delete(void) {
        HandleSystem<Type>::Get()->DeleteItem(m_handle);
    }


    // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    template<HandleSystemConcept Type>
    std::optional<NonAtomicData<Type>> Handle<Type>::GetNoAtomicItem(void) const {
        return HandleSystem<Type>::Get()->GetNoAtomicItem(m_handle);
    }
    // Handle����r�����䂳�ꂽ�v�f���擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    template<HandleSystemConcept Type>
    std::optional<AtomicData<Type>> Handle<Type>::GetAtomicItem(void) const {
        return HandleSystem<Type>::Get()->GetAtomicItem(m_handle);
    }
    // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f���擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    template<HandleSystemConcept Type>
    std::optional<AtomicReadData<Type>> Handle<Type>::GetAtomicReadItem(void) const {
        return HandleSystem<Type>::Get()->GetAtomicReadItem(m_handle);
    }


    // ����Handle�̕ێ����Ă���ԍ��͗L����
    // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
    template<HandleSystemConcept Type>
    bool Handle<Type>::GetEnable(void) const {
        return !(m_handle.has_value() && HandleSystem<Type>::Get()->IsItemEnable(m_handle.value()));
    }
    // ����Handle�̕ێ����Ă���ԍ��͗L����
    // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
    template<HandleSystemConcept Type>
    Handle<Type>::operator bool(void) const {
        GetEnable();
    }


    // HandleNumber�擾
    template<HandleSystemConcept Type>
    Handle<Type>::operator HandleNumberType(void) const {
        return m_handle.value();
    }
}


#endif // !I_HANDLE_H
