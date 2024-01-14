#ifndef I_HANDLE_H
#define I_HANDLE_H
#include <Base/BaseDefines.h>
#include <Base/EditorException.h>
#include <Base/ExclusionData.h>
#include <Base/ExclusionObject.h>
#include <Base/NonExclusionData.h>
#include <Base/Random.h>


namespace EtherEngine {
    // �n���h������i�N���X�̂݁j
    template <typename T>
    concept HandleSystemConcept = std::is_class_v<T>;


    enum class HandleCountType : bool {
        Count = 0,  // �Q�ƃJ�E���g���s��
        UnCount,    // �Q�ƃJ�E���g���s��Ȃ�
        None,       // �����Q�Ƃ��Ȃ�
    };


    // �n���h���Ƃ��Ďg�p�ł��邩���肷��R���Z�v�g
    // @ Memo : ���l�^�łȂ��A����HandleNumberType�ɕϊ��ł��邩
    template <typename T>
    concept UseHandleConcept = std::is_arithmetic_v<T> && std::is_convertible_v<T, IDNumberType>;
}


//----- Handle�錾
namespace EtherEngine {
    // �Ώۂւ̎Q�Ƃ𐔒l�i�n���h���j�Ƃ��Ď������^
    // @ Temp1: �Ǘ��Ώی^
    template <HandleSystemConcept Type>
    class Handle {
    public:
        // �f�t�H���g�R���X�g���N�^
        Handle(void);
        // �\�z�R���X�g���N�^
        // @ Arg1 : �n���h���Ƃ��Ēǉ�����v�f
        Handle(Type&& setItem);
        // �f�X�g���N�^
        ~Handle(void);
        // �R�s�[�R���X�g���N�^
        Handle(const Handle<Type>& copy);
        // ���[�u�R���X�g���N�^
        // @ Memo : �|�C���^�̈ړ����s���܂�
        Handle(Handle<Type>&& move);
        // �R�s�[���
        Handle<Type>& operator =(const Handle<Type>& copy);
        // ���[�u���
        // @ Memo : �|�C���^�̈ړ����s���܂�
        Handle<Type>& operator =(Handle<Type>&& move);


        // �Q�ƃJ�E���g���s�����Q�b�^�[
        HandleCountType GetIsCountUp(void) const { return m_count; }


        // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
        // @ Ret  : �擾�����v�f
        NonExclusionData<Type> GetNoAtomicItem(void) const;
        // Handle����r�����䂳�ꂽ�v�f���擾����
        // @ Ret  : �擾�����v�f
        ExclusionData<Type> GetAtomicItem(void) const;

        // Handle����r�����䂳��Ă��Ȃ��v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f
        Type& GetData(void) const;
        // Handle����r�����䂳�ꂽ�v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f
        Type& GetAtomicData(void) const;


        // �Q�ƃn���h�����擾����
        // @ Ret  : �Q�Ƃ��R�s�[���ꂽ�n���h��
        Handle<Type>&& GetHandle(void) const;


        // ����Handle�̓|�C���^��ێ����Ă��邩
        bool IsEnable(void) const;
        // ����Handle�̓|�C���^��ێ����Ă��邩
        operator bool(void) const;


        // �������̂��w���Ă���n���h����
        bool operator ==(const Handle<Type>& comparison);
        // �������̂��w���Ă��Ȃ��n���h����
        bool operator !=(const Handle<Type>& comparison);


        // HandleNumber�擾
        IDNumberType GetHandleNumber(void) const;
        // HandleNumber�擾
        operator IDNumberType(void) const;

    private:
        IDNumberType m_id; // ���g���ێ����Ă���Handle
        HandleCountType m_count;   // �J�E���g�A�b�v���s����
        std::variant<std::shared_ptr<ExclusionObject<std::shared_ptr<Type>>>, std::shared_ptr<ExclusionObject<std::weak_ptr<Type>>>> m_item;    // �ێ����Ă���A�C�e��
    };
}




//----- Handle����
namespace EtherEngine {
    // �f�t�H���g�R���X�g���N�^
    template <HandleSystemConcept Type>
    Handle<Type>::Handle(void) 
        : m_id(0) 
        , m_count(HandleCountType::None) {
    }
    // �R���X�g���N�^�\�z
    template <HandleSystemConcept Type>
    Handle<Type>::Handle(Type&& setItem) 
        : m_id(Random::GetRandom<IDNumberType>()) // @ MEMO : �K���ɐ������Ă���B��ōl����
        , m_count(HandleCountType::Count)
        , m_item(std::make_shared<ExclusionObject<std::shared_ptr<Type>>>(std::make_shared<Type>(std::move(setItem)))) {
    }
    // �f�X�g���N�^
    template<HandleSystemConcept Type>
    Handle<Type>::~Handle(void) {
    }
    // �R�s�[�R���X�g���N�^
    template<HandleSystemConcept Type>
    Handle<Type>::Handle(const Handle<Type>& copy)
        : m_id(copy.m_id)
        , m_count(copy.m_count)
        , m_item(copy.m_item) {
    }
    // ���[�u�R���X�g���N�^
    template<HandleSystemConcept Type>
    Handle<Type>::Handle(Handle<Type>&& move)
        : m_id(move.m_id)
        , m_count(move.m_count)
        , m_item(move.m_item) {
    }
    // �R�s�[���
    template<HandleSystemConcept Type>
    Handle<Type>& Handle<Type>::operator =(const Handle<Type>& copy) {
        m_id = copy.m_id;
        m_count = copy.m_count;
        m_item = copy.m_item;

        return *this;
    }
    // ���[�u���
    template<HandleSystemConcept Type>
    Handle<Type>& Handle<Type>::operator =(Handle<Type>&& move) {
        m_id = move.m_id;
        m_count = move.m_count;
        m_item = move.m_item;
        return *this;
    }


    // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    NonExclusionData<Type> Handle<Type>::GetNoAtomicItem(void) const {
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");
        switch (m_item.index()) {
        case 0:
            return NonExclusionData<Type>(*std::get<0>(m_item)->GetNonExclusionData().GetData());
            break;
        case 1:
            return NonExclusionData<Type>(*std::get<1>(m_item)->GetNonExclusionData().GetData().lock());
            break;
        }
    }
    // Handle����r�����䂳�ꂽ�v�f���擾����
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    ExclusionData<Type> Handle<Type>::GetAtomicItem(void) const {
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");
        switch (m_item.index()) {
        case 0: {
            auto&& item = std::get<0>(m_item);
            return ExclusionData<Type>(*item->GetNonExclusionData().GetData(), [&]() { item->Look(); }, [&]() { item->UnLock(); });
            break;
        }
        case 1: {
            auto&& item = std::get<1>(m_item);
            return ExclusionData<Type>(*item->GetNonExclusionData().GetData().lock(), [&]() { item->Look(); }, [&]() { item->UnLock(); });
            break;
        }
        }
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


    // �Q�ƃn���h�����擾����
    template<HandleSystemConcept Type>
    Handle<Type>&& Handle<Type>::GetHandle(void) const {
        //----- ��n���h���`�F�b�N
        if (this->IsEnable() == false) throw EditorException("Erorr! Accessing unused handles.");

        //----- �Q�Ƃ𕡐����Đ���
        Handle<Type> ret;
        ret.m_id = this->m_id;
        ret.m_count = HandleCountType::UnCount;
        switch (this->m_item.index()) {
        case 0:
            ret.m_item = std::make_shared<ExclusionObject<std::weak_ptr<Type>>>(std::weak_ptr<Type>(std::get<0>(m_item)->GetNonExclusionData().GetData()));
            break;
        case 1:
            ret.m_item = std::make_shared<ExclusionObject<std::weak_ptr<Type>>>(std::weak_ptr<Type>(std::get<1>(m_item)->GetNonExclusionData().GetData()));
            break;
        }

        //----- �ԋp
        return std::move(ret);
    }


    // ����Handle�̓|�C���^��ێ����Ă��邩
    template<HandleSystemConcept Type>
    bool Handle<Type>::IsEnable(void) const {
        switch (m_item.index()) {
        case std::variant_npos:
            return false;
            break;
        case 0:
            return std::get<0>(m_item)->GetNonExclusionData().GetData() != nullptr;
            break;
        case 1:
            return !(std::get<1>(m_item)->GetNonExclusionData().GetData().expired());
            break;
        } 
    }
    // ����Handle�̓|�C���^��ێ����Ă��邩
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
    IDNumberType Handle<Type>::GetHandleNumber(void) const {
        return m_id;
    }
    // HandleNumber�擾
    template<HandleSystemConcept Type>
    Handle<Type>::operator IDNumberType(void) const {
        return GetHandleNumber();
    }
}


#endif // !I_HANDLE_H
