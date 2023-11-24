#ifndef I_HANDLE_H
#define I_HANDLE_H
#include <Base/HandleSystem.h>
#include <Base/EditorException.h>


namespace EtherEngine {
    enum class HandleCountType {
        Count = 0,      // �Q�ƃJ�E���g���s��
        UnCount = 1,    // �Q�ƃJ�E���g���s��Ȃ�
    };


    // �n���h���Ƃ��Ďg�p�ł��邩���肷��R���Z�v�g
    // @ Memo : ���l�^�łȂ��A����HandleNumberType�ɕϊ��ł��邩
    template <typename T>
    concept UseHandleConcept = std::is_arithmetic_v<T> && std::is_convertible_v<T, HandleNumberType>;
}


//----- Handle�錾
namespace EtherEngine {
    // �Ώۂւ̎Q�Ƃ𐔒l�i�n���h���j�Ƃ��Ď������^
    // @ Temp1: �Ǘ��Ώی^
    template <HandleSystemConcept Type>
    class BaseHandle {
    public:
        // �R���X�g���N�^�\�z
        // @ Arg1 : ���������J�E���g���邩
        // @ Arg2 : �n���h���Ƃ��Ēǉ�����v�f
        BaseHandle(HandleCountType countType, Type&& item);
        // �R���X�g���N�^�\�z
        // @ Arg1 : ���������J�E���g���邩
        BaseHandle(HandleCountType countType);
        // �R���X�g���N�^
        BaseHandle(void);
        // �f�X�g���N�^
        ~BaseHandle(void);
        // �R�s�[�R���X�g���N�^
        BaseHandle(const BaseHandle<Type>& copy);
        // ������Z�q(Copy)
        BaseHandle<Type>& operator=(const BaseHandle<Type>& copy);
        // ������Z�q(Move)
        BaseHandle<Type>& operator=(BaseHandle<Type>&& move);


        // ���̃n���h�����w�����̂��폜����
        void Delete(void);
        // ���̃n���h���̎Q�Ƃ��폜����
        void DeleteRef(void);


        // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
        // @ Ret  : �擾�����v�f
        NonAtomicData<Type> GetNoAtomicItem(void) const;
        // Handle����r�����䂳�ꂽ�v�f���擾����
        // @ Ret  : �擾�����v�f
        AtomicData<Type> GetAtomicItem(void) const;
        // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f���擾����
        // @ Ret  : �擾�����v�f
        AtomicReadData<Type> GetAtomicReadItem(void) const;

        // Handle����r�����䂳��Ă��Ȃ��v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f
        Type& GetNoAtomicData(void) const;
        // Handle����r�����䂳�ꂽ�v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f
        Type& GetAtomicData(void) const;
        // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f
        Type& GetAtomicReadData(void) const;


        // ����Handle�̕ێ����Ă���ԍ��͗L����
        // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
        bool IsEnable(void) const;
        // ����Handle�̕ێ����Ă���ԍ��͗L����
        // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
        operator bool(void) const;


        // �������̂��w���Ă���n���h����
        bool operator ==(const BaseHandle<Type>& comparison);
        // �������̂��w���Ă��Ȃ��n���h����
        bool operator !=(const BaseHandle<Type>& comparison);


        // HandleNumber�擾
        HandleNumberType GetHandleNumber(void) const;
        // HandleNumber�擾
        operator HandleNumberType(void) const;


        // �Q�ƃJ�E���g���s�����Q�b�^�[
        bool GetIsCountUp(void) const { return m_isCount; }
        // ��Q�ƃn���h���Q�b�^�[
        std::weak_ptr<nullptr_t> GetDeleteHandle(void) const { return m_deleteHandle; }

    protected:
        // �Q�Ƃ̃J�E���g�A�b�v���s��
        // @ Memo : ������s��
        void CountUp(void);
        // �Q�Ƃ̃J�E���g�_�E�����s��
        // @ Memo : ������s��
        void CountDown(void);

        HandleNumberType m_handle; // ���g���ێ����Ă���Handle
        bool m_isCount;            // �J�E���g�A�b�v���s����
        std::weak_ptr<nullptr_t> m_deleteHandle;    // HandleSystem�폜����HandleSystem���g�p���邩
    };
}




//----- Handle�錾
namespace EtherEngine {
    // �Q�ƃJ�E���g���s���n���h��
    template <HandleSystemConcept Type>
    class Handle : public BaseHandle<Type> {
    public:
        using BaseHandle<Type>::BaseHandle;

        // �R���X�g���N�^�\�z
        // @ Arg1 : �n���h���Ƃ��Ēǉ�����v�f
        Handle(Type&& item);
    };
}
//----- RefHandle�錾
namespace EtherEngine {
    // �Q�ƃJ�E���g���s��Ȃ��n���h��
    template <HandleSystemConcept Type>
    class RefHandle : public BaseHandle<Type> {
    public:
        using BaseHandle<Type>::BaseHandle;

        // �R���X�g���N�^�\�z
        // @ Arg1 : �n���h���Ƃ��Ēǉ�����v�f
        RefHandle(Type&& item);
    };
}




//----- Handle����
namespace EtherEngine {
    // �R���X�g���N�^�\�z
    // @ Arg1 : ���������J�E���g���邩
    // @ Arg2 : �n���h���Ƃ��Ēǉ�����v�f
    template <HandleSystemConcept Type>
    BaseHandle<Type>::BaseHandle(HandleCountType countType, Type&& item) {
        //----- �n���h���Ƃ��č\�z
        auto handle = HandleSystem<Type>::Get()->AddItem(std::move(item));

        //----- �����o������
        m_handle = handle.first;
        m_deleteHandle = handle.second;

        //----- �n���h���J�E���g���s����
        switch (countType) {
        case HandleCountType::Count:
            m_isCount = true;
            break;
        case HandleCountType::UnCount:
            m_isCount = false;
            break;
        }

        //----- �J�E���g�A�b�v
        CountUp();
    }
    // �R���X�g���N�^�\�z
    // @ Arg1 : ���������J�E���g���邩
    template <HandleSystemConcept Type>
    BaseHandle<Type>::BaseHandle(HandleCountType countType) {
    }
    // �R���X�g���N�^
    template<HandleSystemConcept Type>
    BaseHandle<Type>::BaseHandle(void) {
    }
    // �f�X�g���N�^
    template<HandleSystemConcept Type>
    BaseHandle<Type>::~BaseHandle(void) {
        CountDown();
    }
    // �R�s�[�R���X�g���N�^
    template<HandleSystemConcept Type>
    BaseHandle<Type>::BaseHandle(const BaseHandle<Type>& copy)
        : m_handle(copy.m_handle) 
        , m_isCount(copy.m_isCount) 
        , m_deleteHandle(copy.m_deleteHandle) {
        CountUp();
    }
    // ������Z�q(Copy)
    template<HandleSystemConcept Type>
    BaseHandle<Type>& BaseHandle<Type>::operator=(const BaseHandle<Type>& copy) {
        m_handle = copy.m_handle;
        m_isCount = copy.m_isCount; 
        m_deleteHandle = copy.m_deleteHandle;

        CountUp();
        return *this;
    }
    // ������Z�q(Move)
    template<HandleSystemConcept Type>
    BaseHandle<Type>& BaseHandle<Type>::operator=(BaseHandle<Type>&& move) {
        m_handle = move.m_handle;
        m_isCount = move.m_isCount;
        m_deleteHandle = move.m_deleteHandle;

        CountUp();
        return *this;
    }


    // ���̃n���h�����w�����̂��폜����
    template<HandleSystemConcept Type>
    void BaseHandle<Type>::Delete(void) {
        HandleSystem<Type>::Get()->DeleteItem(m_handle);
    }
    // ���̃n���h���̎Q�Ƃ��폜����
    template<HandleSystemConcept Type>
    void BaseHandle<Type>::DeleteRef(void) {
        CountDown();
        m_handle = NO_CREATE_HANDLE_NUMBER;
    }


    // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    NonAtomicData<Type> BaseHandle<Type>::GetNoAtomicItem(void) const {
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");
        return HandleSystem<Type>::Get()->GetNoAtomicItem(m_handle).value();
    }
    // Handle����r�����䂳�ꂽ�v�f���擾����
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    AtomicData<Type> BaseHandle<Type>::GetAtomicItem(void) const {
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");
        return HandleSystem<Type>::Get()->GetAtomicItem(m_handle).value();
    }
    // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f���擾����
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    AtomicReadData<Type> BaseHandle<Type>::GetAtomicReadItem(void) const {
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");
        return HandleSystem<Type>::Get()->GetAtomicReadItem(m_handle).value();
    }

    // Handle����r�����䂳��Ă��Ȃ��v�f�𒼐ڎ擾����
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    Type& BaseHandle<Type>::GetNoAtomicData(void) const {
        return GetNoAtomicItem().GetData();
    }
    // Handle����r�����䂳�ꂽ�v�f�𒼐ڎ擾����
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    Type& BaseHandle<Type>::GetAtomicData(void) const {
        return GetAtomicItem().GetData();
    }
    // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f�𒼐ڎ擾����
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    Type& BaseHandle<Type>::GetAtomicReadData(void) const {
        return GetAtomicReadItem().GetData();
    }


    // ����Handle�̕ێ����Ă���ԍ��͗L����
    // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
    template<HandleSystemConcept Type>
    bool BaseHandle<Type>::IsEnable(void) const {
        return HandleSystem<Type>::Get()->IsItemEnable(m_handle);
    }
    // ����Handle�̕ێ����Ă���ԍ��͗L����
    // @ Ret  : ����HandleSystem�ō폜���ꂽ�l�Ⴕ���͖����l�Ȃ� false
    template<HandleSystemConcept Type>
    BaseHandle<Type>::operator bool(void) const {
        return IsEnable();
    }


    // �������̂��w���Ă���n���h����
    template<HandleSystemConcept Type>
    bool BaseHandle<Type>::operator ==(const BaseHandle<Type>& comparison) {
        return comparison.GetHandleNumber() == m_handle;
    }
    // �������̂��w���Ă��Ȃ��n���h����
    template<HandleSystemConcept Type>
    bool BaseHandle<Type>::operator !=(const BaseHandle<Type>& comparison) {
        return comparison.GetHandleNumber() != m_handle;
    }


    // HandleNumber�擾
    template<HandleSystemConcept Type>
    HandleNumberType BaseHandle<Type>::GetHandleNumber(void) const {
        return m_handle;
    }
    // HandleNumber�擾
    template<HandleSystemConcept Type>
    BaseHandle<Type>::operator HandleNumberType(void) const {
        return GetHandleNumber();
    }


    // �Q�Ƃ̃J�E���g�A�b�v���s��
    template<HandleSystemConcept Type>
    void BaseHandle<Type>::CountUp(void) {
        if (m_isCount && m_deleteHandle.expired() == false) {
            HandleSystem<Type>::Get()->CountUpItem(m_handle);
        }
    }
    // �Q�Ƃ̃J�E���g�_�E�����s��
    template<HandleSystemConcept Type>
    void BaseHandle<Type>::CountDown(void) {
        if (m_isCount && m_deleteHandle.expired() == false) {
            HandleSystem<Type>::Get()->CountDownItem(m_handle);
        }
    }
}


//----- Handle����
namespace EtherEngine {
    // �R���X�g���N�^�\�z
    // @ Arg1 : �n���h���Ƃ��Ēǉ�����v�f
    template <HandleSystemConcept Type>
    Handle<Type>::Handle(Type&& item)
        : BaseHandle<Type>(HandleCountType::Count, std::move(item)) {
    }
}
//----- RefHandle����
namespace EtherEngine {
    // �R���X�g���N�^�\�z
    // @ Arg1 : �n���h���Ƃ��Ēǉ�����v�f
    template <HandleSystemConcept Type>
    RefHandle<Type>::RefHandle(Type&& item)
        : BaseHandle<Type>(HandleCountType::UnCount, std::move(item)) {
    }
}


#endif // !I_HANDLE_H
