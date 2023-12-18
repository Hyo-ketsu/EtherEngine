#ifndef I_HANDLESYSTEM_H
#define I_HANDLESYSTEM_H
#include <Base/ConceptUtility.h>
#include <Base/Singleton.h>
#include <Base/Random.h>
#include <Base/ExclusionObject.h>
#include <Base/IDClass.h>


//----- �萔����`
namespace EtherEngine {
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
        [[nodiscard]] std::pair<IDClass, std::weak_ptr<ullint>> AddItem(Type&& item);
        // �v�f���폜����
        // @ Arg1 : �폜����ԍ�
        void DeleteItem(const IDClass& handle);


        // �v�f���̃J�E���g�A�b�v
        // @ Arg1 : �J�E���g�A�b�v����ԍ�
        void CountUpItem(const IDClass& handle);
        // �v�f���̃J�E���g�_�E��
        // @ Arg1 : �J�E���g�_�E������ԍ�
        void CountDownItem(const IDClass& handle);


        // �w�肵���v�f�����݂��邩
        // @ Ret  : ���݂��Ȃ��Ⴕ���́A�J�E���^�[��0�ȉ��Ȃ� false ����ȊO�Ȃ� true
        // @ Arg1 : Handle
        bool IsItemEnable(const IDClass& handle) const;


        // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        // @ Arg1 : Handle
        std::optional<NonExclusionData<Type>> GetNoAtomicItem(const IDClass& handle);
        // Handle����r�����䂳�ꂽ�v�f���擾����
        // @ Ret  : �擾�����v�f�ioptional�j
        // @ Arg1 : Handle
        std::optional<ExclusionData<Type>> GetAtomicItem(const IDClass& handle);


        // ID����Q�Ɛ����擾����
        // @ Ret  : �擾�����Q�Ɛ�
        // @ Arg1 : ID
        std::weak_ptr<ullint> GetReferenceCount(const IDClass& handle);

    private:
        // �R���X�g���N�^
        HandleSystem(void) {}


        // �Q�Ɛ���0�ȉ��̗v�f���폜����
        void Delete0ReferenceCounter(const IDClass& handle);


        std::unordered_map<IDClass, ExclusionObject<Type>> m_item;     // �ێ����Ă���v�f�̘A�z�z��
        std::unordered_map<IDClass, std::shared_ptr<ullint>> m_referenceCounter;    // �Q�Ɛ�

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
    [[nodiscard]] std::pair<IDClass, std::weak_ptr<ullint>> HandleSystem<Type>::AddItem(Type&& item) {
        //----- ���b�N
        auto lock = this->GetMutex()->KeySpinLock();

        //----- Handle����
        auto handle = IDClass();

        //----- �A�z�z��Ɋi�[
        ExclusionObject<Type> atomic(std::move(item));
        m_item.emplace(handle, std::move(atomic));

        //----- �Q�ƃJ�E���^�ǉ�
        auto refCounter = std::make_shared<ullint>(1);
        m_referenceCounter.emplace(handle, refCounter);

        //----- �ԋp
        return std::pair<IDClass, std::weak_ptr<ullint>>(handle, refCounter);
    }
    // �v�f���폜����
    // @ Arg1 : �폜����ԍ�
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::DeleteItem(const IDClass& handle) {
        //----- ���݂���΍폜
        if (IsItemEnable(handle)) {
            //----- ���b�N
            auto lock = this->GetMutex()->KeySpinLock();

            //----- �J�E���g�� 0 �ɂ��A���̌�J�E���g 0 �v�f���폜
            m_referenceCounter.find(handle)->second = 0;
            Delete0ReferenceCounter(handle);
        }
    }


    // �v�f���̃J�E���g�A�b�v
    // @ Arg1 : �폜����ԍ�
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::CountUpItem(const IDClass& handle) {
        auto reference = m_referenceCounter.find(handle);
        if (reference != m_referenceCounter.end()) {
            auto& count = reference->second;
            (*count)++;
        }
    }
    // �v�f���̃J�E���g�_�E��
    // @ Arg1 : �폜����ԍ�
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::CountDownItem(const IDClass& handle) {
        auto reference = m_referenceCounter.find(handle);
        if (reference != m_referenceCounter.end()) {
            auto& count = reference->second;
            (*count)--;
            Delete0ReferenceCounter(handle);
        }
    }


    // �w�肵���v�f�����݂��邩
    // @ Ret  : ���݂��Ȃ��Ⴕ���́A�J�E���^�[��0�ȉ��Ȃ� false ����ȊO�Ȃ� true
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    bool HandleSystem<Type>::IsItemEnable(const IDClass& handle) const {
        if (m_item.find(handle) == m_item.end()) return false;
        auto ref = m_referenceCounter.find(handle);
        if (  ref == m_referenceCounter.end()) return false;
        if ((*ref->second.get()) < 1) return false;
        return true;
    }


    // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    std::optional<NonExclusionData<Type>> HandleSystem<Type>::GetNoAtomicItem(const IDClass& handle) {
        //----- ���b�N
        auto lock = this->GetMutex()->KeySpinLock();

        //----- �ϐ��錾
        auto ret = std::optional<NonExclusionData<Type>>();

        if (IsItemEnable(handle)) {
            //----- ���݂���
            ret.emplace(m_item.find(handle)->second.GetNonExclusionData());
        }

        //----- �ԋp
        return ret;
    }
    // Handle����r�����䂳�ꂽ�v�f���擾����
    // @ Ret  : �擾�����v�f�ioptional�j
    // @ Arg1 : Handle
    template <HandleSystemConcept Type>
    std::optional<ExclusionData<Type>> HandleSystem<Type>::GetAtomicItem(const IDClass& handle) {
        //----- ���b�N
        auto lock = this->GetMutex()->KeySpinLock();

        //----- �ϐ��錾
        auto ret = std::optional<ExclusionData<Type>>();

        if (IsItemEnable(handle)) {
            //----- ���݂���
            ret.emplace(m_item.find(handle)->second.GetData());
        }

        //----- �ԋp
        return ret;
    }


    // �Q�Ɛ���0�ȉ��̗v�f���폜����
    template <HandleSystemConcept Type>
    void HandleSystem<Type>::Delete0ReferenceCounter(const IDClass& handle) {
        //----- ���b�N
        auto lock = this->GetMutex()->KeySpinLock();

        //----- �Q�ƃJ�E���^��0��
        auto find = m_referenceCounter.find(handle);
        if (find != m_referenceCounter.end() && (*find->second) < 1) {
            //----- 1�����B�Q�ƃJ�E���^�폜
            m_referenceCounter.erase(find);

            //----- �A�z�z��̍폜�p�C�e���[�^�[
            auto item = m_item.find(handle);

            //----- �A�z�z��̍폜
            if (item != m_item.end()) m_item.erase(item);
        }
    }
    // ID����Q�Ɛ����擾����
    template <HandleSystemConcept Type>
    std::weak_ptr<ullint> HandleSystem<Type>::GetReferenceCount(const IDClass& handle) {
        //----- ���b�N
        auto lock = this->GetMutex()->KeySpinLock();

        //----- �ϐ��錾
        std::weak_ptr<ullint> ret;

        //----- �擾����
        auto find = m_referenceCounter.find(handle);
        if (find == m_referenceCounter.end()) {
            ret = decltype(ret)(find->second);
        }

        //----- �ԋp
        return ret;
    }
}


#endif // !I_HANDLESYSTEM_H
