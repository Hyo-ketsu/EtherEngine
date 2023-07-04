#ifndef I_HANDLESYSTEM_H
#define I_HANDLESYSTEM_H

#include <Base/ConceptUtility.h>
#include <Base/Singleton.h>
#include <Base/Random.h>
#include <Base/Atomic.h>


//----- �萔����`
namespace EtherEngine {
    using HandleNumberType = ullint;    // �n���h���Ƃ��Ďg�p���鐔�l�^


    const HandleNumberType NO_CREATE_HANDLE_NUMBER = 0; // �n���h���Ƃ��Ďg�p���Ȃ��ԍ�


    // �n���h������i�N���X�̂݁j
    template <typename T>
    concept HandleSystemConcept = std::is_class_v<T>;
}


//----- HandleSystem ��`
namespace EtherEngine {
    // Handle�őΏە����Ǘ�����N���X
    template <HandleSystemConcept Type>
    class HandleSystem : public Singleton<HandleSystem<Type>> {
    public:
        // �f�X�g���N�^
        ~HandleSystem(void) override;


        // �v�f��ǉ��AHandle���擾����
        // @ Memo : �ǉ��̍ۂ͎Ⴕ����Handle�̃R���X�g���N�^���g�p���������B
        // @ Ret  : �쐬���ꂽ�v�f�ւ�Handle
        // @ Arg1 : �ǉ�����v�f�i�E�Ӓl�j
        [[nodiscard]] std::pair<HandleNumberType, std::weak_ptr<nullptr_t>> AddItem(Type&& item);
        // �v�f���폜����
        // @ Arg1 : �폜����ԍ�
        void DeleteItem(const HandleNumberType& handle);


        // �v�f���̃J�E���g�A�b�v
        // @ Arg1 : �J�E���g�A�b�v����ԍ�
        void CountUpItem(const HandleNumberType& handle);
        // �v�f���̃J�E���g�_�E��
        // @ Arg1 : �J�E���g�_�E������ԍ�
        void CountDownItem(const HandleNumberType& handle);


        // �w�肵���v�f�����݂��邩
        // @ Ret  : ���݂��Ȃ��Ⴕ���́A�J�E���^�[��0�ȉ��Ȃ� false ����ȊO�Ȃ� true
        // @ Arg1 : Handle
        bool IsItemEnable(const HandleNumberType& handle) const;


        // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        // @ Arg1 : Handle
        std::optional<NonAtomicData<Type>> GetNoAtomicItem(const HandleNumberType& handle);
        // Handle����r�����䂳�ꂽ�v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        // @ Arg1 : Handle
        std::optional<AtomicData<Type>> GetAtomicItem(const HandleNumberType& handle);
        // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        // @ Arg1 : Handle
        std::optional<AtomicReadData<Type>> GetAtomicReadItem(const HandleNumberType& handle);


    private:
        // �R���X�g���N�^
        HandleSystem(void) {}


        // �Q�Ɛ���0�ȉ��̗v�f���폜����
        void Delete0ReferenceCounter(const HandleNumberType& handle);


        std::unordered_map<HandleNumberType, Atomic<Type>> m_item;     // �ێ����Ă���v�f�̘A�z�z��
        std::unordered_map<HandleNumberType, int> m_referenceCounter;  // ����Handle�̎Q�Ɛ�
        std::vector<std::shared_ptr<nullptr_t>> m_deleteHandle;  // �폜���̃J�E���g�_�E�����s��Ȃ��t���O

        friend class Singleton<HandleSystem<Type>>;
    };
}




//----- HandleSystem ����
namespace EtherEngine {
    // �f�X�g���N�^
    template <HandleSystemConcept Type>
    HandleSystem<Type>::~HandleSystem(void) {
    }


    // �v�f��ǉ��AHandle���擾����
    // @ Ret  : �쐬���ꂽ�v�f�ւ�Handle
    // @ Arg1 : �ǉ�����v�f�i�E�Ӓl�j
    template <HandleSystemConcept Type>
    [[nodiscard]] std::pair<HandleNumberType, std::weak_ptr<nullptr_t>> HandleSystem<Type>::AddItem(Type&& item) {
        //----- ���b�N
        std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

        //----- Handle����
        HandleNumberType handle = EtherEngine::Random::GetRandom<HandleNumberType>();
        while (true) {
            //----- ���݂��Ă��邩
            // @ Memo : �P�Ȃ�ԍ��`�F�b�N
            Delete0ReferenceCounter(handle);
            auto item = m_item.find(handle);
            if (handle != NO_CREATE_HANDLE_NUMBER && item == m_item.end()) break;

            //----- ����
            handle = EtherEngine::Random::GetRandom<HandleNumberType>();
        }

        //----- �A�z�z��Ɋi�[
        Atomic<Type> atomic(item);
        m_item.emplace(handle, std::move(atomic));

        //----- �Q�ƃJ�E���^�ǉ�
        m_referenceCounter.emplace(handle, 1);

        //----- �ԋp�p�ϐ��錾
        m_deleteHandle.push_back(std::make_shared<nullptr_t>(nullptr));
        std::pair<HandleNumberType, std::weak_ptr<nullptr_t>> ret = decltype(ret)(handle, m_deleteHandle.back());

        //----- �ԋp
        return ret;
    }
    // �v�f���폜����
    // @ Arg1 : �폜����ԍ�
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::DeleteItem(const HandleNumberType& handle) {
        //----- ���݂���΍폜
        if (IsItemEnable(handle)) {
            //----- ���b�N
            std::lock_guard<decltype(this->m_mutex)> lock(this->m_mutex);

            //----- �J�E���g�� 0 �ɂ��A���̌�J�E���g 0 �v�f���폜
            m_referenceCounter.find(handle)->second = 0;
            Delete0ReferenceCounter(handle);
        }
    }


    // �v�f���̃J�E���g�A�b�v
    // @ Arg1 : �폜����ԍ�
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::CountUpItem(const HandleNumberType& handle) {
        auto reference = m_referenceCounter.find(handle);
        if (reference != m_referenceCounter.end()) {
            reference->second++;
        }
    }
    // �v�f���̃J�E���g�_�E��
    // @ Arg1 : �폜����ԍ�
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::CountDownItem(const HandleNumberType& handle) {
        auto reference = m_referenceCounter.find(handle);
        if (reference != m_referenceCounter.end()) {
            reference->second--;
            Delete0ReferenceCounter(handle);
        }
    }


    // �w�肵���v�f�����݂��邩
    // @ Ret  : ���݂��Ȃ��Ⴕ���́A�J�E���^�[��0�ȉ��Ȃ� false ����ȊO�Ȃ� true
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    bool HandleSystem<Type>::IsItemEnable(const HandleNumberType& handle) const {
        if (m_item.find(handle) == m_item.end()) return false;
        if (m_referenceCounter.find(handle) == m_referenceCounter.end()) return false;
        if (m_referenceCounter.find(handle)->second < 1) return false;
        return true;
    }


    // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    std::optional<NonAtomicData<Type>> HandleSystem<Type>::GetNoAtomicItem(const HandleNumberType& handle) {
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
    std::optional<AtomicData<Type>> HandleSystem<Type>::GetAtomicItem(const HandleNumberType& handle) {
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
    std::optional<AtomicReadData<Type>> HandleSystem<Type>::GetAtomicReadItem(const HandleNumberType& handle) {
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
    void HandleSystem<Type>::Delete0ReferenceCounter(const HandleNumberType& handle) {
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
