#ifndef I_HANDLESYSTEM_H
#define I_HANDLESYSTEM_H
#include <Base/Singleton.h>
#include <Base/Random.h>
#include <Base/Atomic.h>


//----- Handle�錾
namespace EtherEngine {
    using HandleNumberType = unsigned long long;


    // �N���X�̂ݐ���
    template <typename T>
    concept HandleSystemConcept = std::is_class_v<T>;


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


        // �R���X�g���N�^�����Z�b�^�[
        // @ Memo : �������̂݉�
        void SetConstructor(std::function<void(void)> in) { if (m_constructor == nullptr) m_constructor = in; }
        // �f�X�g���N�^�����Z�b�^�[
        // @ Memo : �������̂݉�
        void SetDestructor(std::function<void(void)> in) { if (m_destructor == nullptr) m_destructor = in; }


        // Handle����v�f���擾�A�r��������s��
        // @ Memo : Handle������������Ă���A���݂��Ȃ��ꍇ�ɗ�O��f���܂�
        // @ Ret  : �擾�����v�f
        AtomicData<Type> GetAtomicItem(void) const;
        // Handle����v�f���擾
        // @ Memo : Handle������������Ă���A���݂��Ȃ��ꍇ�ɗ�O��f���܂�
        // @ Ret  : �擾�����v�f
        NonAtomicData<Type> GetNonAtomicItem(void) const;
        // Handle����ǂݎ���p�v�f���擾����
        // @ Memo : Handle������������Ă���A���݂��Ȃ��ꍇ�ɗ�O��f���܂�
        // @ Ret  : �擾�����v�f
        AtomicData<Type> GetAtomicItem(void) const;
        // Handle�����b�N���s���邩
        // @ Ret  : ���b�N���s����(= ���b�N����Ă��Ȃ�)��
        // @ Memo : �ǂݎ�胍�b�N��(Default : false)
        bool IsLock(const bool& isReadLock) const;


        // ����Handle���L����
        // @ Ret  : ����Handle���́AHandle�̎Q�Ɛ悪�L���������ꂼ�ꔻ��
        bool IsEnable(void) const;
        // ����Handle���L����
        // @ Ret  : ����Handle���́AHandle�̎Q�Ɛ悪�L���������ꂼ�ꔻ��
        explicit operator bool(void) const;


        // �Q�Ƃ𖳌�������
        void Destroy(void);


        // ��r
        bool operator ==(const Handle<Type>& handle) const;

    private:
        std::optional<HandleNumberType> m_handle;      // ���g���ێ����Ă���Handle
        std::function<void(void)>       m_constructor; // ����������
        std::function<void(void)>       m_destructor;  // �I��������
    };
}




//----- HandleSystem ��`
namespace EtherEngine {
    // Handle�őΏە����Ǘ�����N���X
    // @ Temp : �Ǘ��Ώی^
    template <HandleSystemConcept Type>
    class HandleSystem : public Singleton<HandleSystem<Type>> {
    public:
        // �v�f��ǉ��AHandle���擾����
        // @ Ret  : �쐬���ꂽ�v�f�ւ�Handle
        // @ Arg1 : �ǉ�����v�f�i�E�Ӓl�j
        Handle<Type> AddItem(Type&& item);


        // �w�肵���v�f�����݂��邩
        // @ Ret  : ���݂��Ȃ��Ⴕ���́A�J�E���^�[��0�ȉ��Ȃ� false ����ȊO�Ȃ� true
        // @ Arg1 : Handle
        bool IsItemEnable(const Handle<Type>& handle) const;


        // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        // @ Arg1 : Handle
        std::optional<NonAtomicData<Type>> GetNoAtomicItem(const Handle<Type>& handle);
        // Handle����r�����䂳�ꂽ�v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        // @ Arg1 : Handle
        std::optional<AtomicData<Type>> GetAtomicItem(const Handle<Type>& handle);
        // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        // @ Arg1 : Handle
        std::optional<AtomicReadData<Type>> GetAtomicReadItem(const Handle<Type>& handle);

    private:
        // �R���X�g���N�^
        HandleSystem(void) {}


        // �Q�Ɛ���0�ȉ��̗v�f���폜����
        void Delete0ReferenceCounter(const Handle<Type>& handle);


        std::unordered_map<Handle<Type>, Atomic<Type>> m_item; // �ێ����Ă���v�f�̘A�z�z��
        std::unordered_map<Handle<Type>, int> m_referenceCounter;  // ����Handle�̎Q�Ɛ�

        friend class Singleton<HandleSystem<Type>>;
    };


    // HandleClass �V���[�g�J�b�g
    template <HandleSystemConcept Type>
    using UseHandle = HandleSystem<Type>::Handle<Type>;
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


    // Handle����v�f���擾�A�r��������s��
    // @ Memo : Handle������������Ă���A���݂��Ȃ��ꍇ�ɗ�O��f���܂�
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    AtomicData<Type> Handle<Type>::GetAtomicItem(void) const {
        if (IsEnable() == false) throw std::runtime_error("A Handle does not hold an element");
        // TODO : ����Ȃ��z�Q�Ƃ��܂��Ď��ʁB�����HandleSystem.h�ɓ�������H
    }
    // Handle����v�f���擾
    // @ Memo : Handle������������Ă���A���݂��Ȃ��ꍇ�ɗ�O��f���܂�
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    NonAtomicData<Type> Handle<Type>::GetNonAtomicItem(void) const {
        if (IsEnable() == false) throw std::runtime_error("A Handle does not hold an element");
        // TODO : ����Ȃ��z�Q�Ƃ��܂��Ď��ʁB�����HandleSystem.h�ɓ�������H
    }
    // Handle����ǂݎ���p�v�f���擾����
    // @ Memo : Handle������������Ă���A���݂��Ȃ��ꍇ�ɗ�O��f���܂�
    // @ Ret  : �擾�����v�f
    template<HandleSystemConcept Type>
    AtomicData<Type> Handle<Type>::GetAtomicItem(void) const {
        if (IsEnable() == false) throw std::runtime_error("A Handle does not hold an element");
        // TODO : ����Ȃ��z�Q�Ƃ��܂��Ď��ʁB�����HandleSystem.h�ɓ�������H
    }
    // Handle�����b�N���s���邩
    // @ Ret  : ���b�N���s����(= ���b�N����Ă��Ȃ�)��
    // @ Memo : �ǂݎ�胍�b�N��(Default : false)
    template<HandleSystemConcept Type>
    bool Handle<Type>::IsLock(const bool& isReadLock) const {
        // TODO : ����Ȃ��z�Q�Ƃ��܂��Ď��ʁB�����HandleSystem.h�ɓ�������H
    }


    // ����Handle���L����
    // @ Ret  : ����Handle���́AHandle�̎Q�Ɛ悪�L���������ꂼ�ꔻ��
    template<HandleSystemConcept Type>
    bool Handle<Type>::IsEnable(void) const {
        
        return m_handle.has_value() && HandleSystem<Type>:: IsItemEnable(*this);
    }
    // ����Handle���L����
    // @ Ret  : ����Handle���́AHandle�̎Q�Ɛ悪�L���������ꂼ�ꔻ��
    template<HandleSystemConcept Type>
    Handle<Type>::operator bool(void) const {
        return IsEnable();
    }
    // �Q�Ƃ𖳌�������
    template<HandleSystemConcept Type>
    void Handle<Type>::Destroy(void) {
        m_handle.reset();
    }


    // ��r
    template<HandleSystemConcept Type>
    bool Handle<Type>::operator ==(const Handle<Type>& handle) const {
        //----- �����l����
        if (this->IsEnable() == false) return false;
        if (handle.IsEnable() == false) return false;

        //----- Handle�̔�r
        return m_handle.value() == handle.m_handle.value();
    }
}




//----- HandleSystem����
namespace EtherEngine {
    // �v�f��ǉ��AHandle���擾����
    // @ Ret  : �쐬���ꂽ�v�f�ւ�Handle
    // @ Arg1 : �ǉ�����v�f�i�E�Ӓl�j
    template <HandleSystemConcept Type>
    Handle<Type> HandleSystem<Type>::AddItem(Type&& item) {
        //----- ���b�N
        std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

        //----- Handle����
        Handle<Type> handle = Handle<Type>(EtherEngine::Random::GetRandom<HandleNumberType>());
        while (true) {
            //----- ���݂��Ă��邩
            // @ Memo : �P�Ȃ�ԍ��`�F�b�N
            Delete0ReferenceCounter(handle);
            auto item = m_item.find(handle);
            if (item == m_item.end()) break;

            //----- ����
            handle = Handle<Type>(EtherEngine::Random::GetRandom<HandleNumberType>());
        }

        //----- �Q�Ƃ�A�z�z��Ɋi�[
        m_item.emplace(handle, item);
        
        //----- �Q�ƃJ�E���^�ǉ�
        m_referenceCounter.emplace(handle, 1);

        //----- �R�[���o�b�N�o�^
        handle.SetConstructor();

        //----- �ԋp
        return handle;
    }


    // �w�肵���v�f�����݂��邩
    // @ Ret  : ���݂��Ȃ��Ⴕ���́A�J�E���^�[��0�ȉ��Ȃ� false ����ȊO�Ȃ� true
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    bool HandleSystem<Type>::IsItemEnable(const Handle<Type>& handle) const {
        if (m_item.find(handle) == m_item.end()) return false;
        if (m_referenceCounter.find(handle) == m_referenceCounter.end()) return false;
        if (m_referenceCounter.find(handle)->second > 0) return false;
        return true;
    }


    // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    std::optional<NonAtomicData<Type>> HandleSystem<Type>::GetNoAtomicItem(const Handle<Type>& handle) {
        //----- ���b�N
        std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

        //----- �ϐ��錾
        auto ret = std::optional<NonAtomicData<Type>>();

        if (IsItemEnable(handle)) {
            //----- ���݂���
            ret.emplace(m_item.find(handle)->second.GetNonAtomicData());
        }

        //----- �ԋp
        return ret;
    }
    // Handle����r�����䂳�ꂽ�v�f���擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    std::optional<AtomicData<Type>> HandleSystem<Type>::GetAtomicItem(const Handle<Type>& handle) {
        //----- ���b�N
        std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

        //----- �ϐ��錾
        auto ret = std::optional<AtomicData<Type>>();

        if (IsItemEnable(handle)) {
            //----- ���݂���
            ret.emplace(m_item.find(handle)->second.GetData());
        }

        //----- �ԋp
        return ret;
    }
    // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f���擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    std::optional<AtomicReadData<Type>> HandleSystem<Type>::GetAtomicReadItem(const Handle<Type>& handle) {
        //----- ���b�N
        std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

        //----- �ϐ��錾
        auto ret = std::optional<AtomicReadData<Type>>();

        if (IsItemEnable(handle)) {
            //----- ���݂���
            ret.emplace(m_item.find(handle)->second.GetReadData());
        }

        //----- �ԋp
        return ret;
    }


    // �Q�Ɛ���0�ȉ��̗v�f���폜����
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::Delete0ReferenceCounter(const Handle<Type>& handle) {
        //----- ���b�N
        std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

        //----- �Q�ƃJ�E���^��0��
        if (m_referenceCounter.find(handle) != m_referenceCounter.end() && m_referenceCounter.find(handle)->second < 1) {
            //----- 1�����B�Q�ƃJ�E���^�폜
            m_referenceCounter.erase(m_referenceCounter.find(handle));

            //----- �A�z�z��̍폜�p�C�e���[�^�[
            auto item = m_item.find(handle);

            //----- �A�z�z��̍폜
            if (item != m_item.end()) m_item.erase(item);
        }
    }
}


#endif // !I_HANDLESYSTEM_H
