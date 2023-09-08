#ifndef I_STORAGESYSTEM_H
#define I_STORAGESYSTEM_H
#include <Base/Singleton.h>
#include <Base/IDClass.h>


//----- ���̑��錾
namespace EtherEngine {
    // StorageSystem�̃R���Z�v�g
    template <typename T>
    concept StorageSystemConcept = std::is_class_v<T>;
}


//----- StorageID �錾
namespace EtherEngine {
    // StorageSystem�Ŏg�p����ID
    template <StorageSystemConcept DataType>
    class StorageID {
    public:
        // �R���X�g���N�^
        // @ Arg1 : ID
        StorageID(std::weak_ptr<IDClass> id = nullptr);
        // �f�X�g���N�^
        ~StorageID(void);


        // �L���� shared_ptr �������Ă��邩
        bool GetEnable(void) const;
        // �L���� shared_ptr �������Ă��邩
        operator bool(void) const;
        // ID�̎擾
        IDClass GetId(void) const;
        // ID�̎擾
        operator IDClass(void) const;

    private:
        std::weak_ptr<IDClass> m_id;        // �ێ����Ă���ID
    };
}


//----- StorageSystem �錾
namespace EtherEngine {
    // ID�Ń|�C���^���Ǘ�����N���X
    template <StorageSystemConcept DataType>
    class StorageSystem : public Singleton<StorageSystem<DataType>> {
    public:
        // �f�X�g���N�^
        ~StorageSystem(void) {}


        // �f�[�^��ǉ�����
        // @ Ret  : ID
        // @ Arg1 : �ǉ�����f�[�^(�Q��)
        [[nodiscard]] StorageID<DataType> AddData(DataType& data);
        // �f�[�^���폜����
        // @ Arg1 : ID
        void DeleteData(const StorageID<DataType>& id);


        // �w�肵��ID�̃f�[�^�����݂��邩
        // @ Arg1 : �w��ID
        bool IsIDToData(const IDClass& id);


        // �f�[�^���擾����
        // @ Arg1 : �w��ID
        DataType* const GetData(const IDClass& id);

    private:
        // �R���X�g���N�^
        StorageSystem(void) {}

        friend class Singleton<StorageSystem<DataType>>;

        std::vector<std::tuple<std::shared_ptr<IDClass>, DataType*>> m_datas;   // �ێ����Ă���f�[�^
    };
}




//----- StorageID ��`
namespace EtherEngine {
    // �R���X�g���N�^
    template <StorageSystemConcept DataType>
    StorageID<DataType>::StorageID(std::weak_ptr<IDClass> id)
        : m_id(id) {
    }
    template <StorageSystemConcept DataType>
    // �f�X�g���N�^
    StorageID<DataType>::~StorageID(void) {
        if (m_id.expired() == false) {
            StorageSystem<DataType>::Get()->DeleteData(*this);
        }
    }


    // �L���� shared_ptr �������Ă��邩
    template <StorageSystemConcept DataType>
    bool StorageID<DataType>::GetEnable(void) const {
        return !(m_id.expired());   // expired�́u�������؂�Ă��� true�v�Ȃ̂Ŕ��]
    }
    // �L���� shared_ptr �������Ă��邩
    template <StorageSystemConcept DataType>
    StorageID<DataType>::operator bool(void) const {
        return GetEnable();
    }
    // ID�̎擾
    template <StorageSystemConcept DataType>
    IDClass StorageID<DataType>::GetId(void) const {
        return *m_id.lock();
    }
    // ID�̎擾
    template <StorageSystemConcept DataType>
    StorageID<DataType>::operator IDClass(void) const {
        return GetId();
    }
}




//----- StorageSystem ��`
namespace EtherEngine {
    // �f�[�^��ǉ�����
    // @ Ret  : ID
    // @ Arg1 : �ǉ�����f�[�^(�Q��)
    template <StorageSystemConcept DataType>
    [[nodiscard]] StorageID<DataType> StorageSystem<DataType>::AddData(DataType& data) {
        //----- ID�̍쐬�ƒǉ�
        auto ptr = std::make_shared<IDClass>(IDClass());
        m_datas.emplace_back(std::move(ptr), &data);

        //----- �ԋp
        return StorageID<DataType>(std::weak_ptr<IDClass>(std::get<0>(m_datas.back())));
    }
    // �f�[�^���폜����
    // @ Arg1 : ID
    template <StorageSystemConcept DataType>
    void StorageSystem<DataType>::DeleteData(const StorageID<DataType>& id) {
        if (m_datas.size() == 0) return;
        for (auto it = m_datas.begin(); it != m_datas.end(); it++) {
            if (*std::get<0>(*it) == id.GetId()) {
                //----- �폜
                m_datas.erase(it);
                break;
            }
        }
    }


    // �w�肵��ID�̃f�[�^�����݂��邩
    // @ Arg1 : �w��ID
    template <StorageSystemConcept DataType>
    bool StorageSystem<DataType>::IsIDToData(const IDClass& id) {
        //----- ID�Ŏ擾����
        for (auto&& it : m_datas) {
            if (*std::get<0>(it) == id) {
                return true;
            }
        }

        return false;
    }


    // �f�[�^���擾����
    // @ Arg1 : �w��ID
    template <StorageSystemConcept DataType>
    DataType* const StorageSystem<DataType>::GetData(const IDClass& id) {
        //----- ID�Ŏ擾����
        for (auto&& it : m_datas) {
            if (*std::get<0>(it) == id) {
                return std::get<1>(it);
            }
        }

        //----- �ԋp
        return nullptr;
    }
}


#endif // !I_STORAGESYSTEM_H
