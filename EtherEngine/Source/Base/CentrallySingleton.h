#ifndef I_CENTRALLYSINGLETON_H
#define I_CENTRALLYSINGLETON_H
#include <Base/Mutex.h>
#include <Base/BaseUtility.h>


//----- CentrallySingleton �錾
namespace EtherEngine {
    // �V���O���g����T::Get()�ŌĂяo���A���R���X�g���N�^���Ăяo���Ȃ��^�𔻒肷��R���Z�v�g
    template <typename T>
    concept SingletonTypeConcept = requires(T t) {
        {t.Get()}-> std::same_as<T*>;
    };


    // �V���O���g�����ꌳ�I�ɕێ����Ă���N���X
    class CentrallySingleton {
    public:
        // �f�X�g���N�^
        ~CentrallySingleton(void);


        // �C���X�^���X���擾����
        static std::shared_ptr<CentrallySingleton>& Get(void);
        // �C���X�^���X��ݒ肷��
        static void Set(std::shared_ptr<CentrallySingleton> instance);


        // �V���O���g����ǉ�����
        // @ Temp : �ǉ�����V���O���g��
        // @ Ret  : �ǉ����ꂽ�C���X�^���X
        template <SingletonTypeConcept SingletonType>
        SingletonType* AddSingleton(void);
        // �V���O���g�����폜����
        // @ Temp : �폜����V���O���g��
        template <SingletonTypeConcept SingletonType>
        void DeleteSingleton(void);
        // �V���O���g�����擾����
        // @ Temp : �擾����V���O���g��
        // @ Ret  : �C���X�^���X
        template <SingletonTypeConcept SingletonType>
        SingletonType* GetSingleton(void);

    private:
        // �R���X�g���N�^
        CentrallySingleton(void);

        static std::shared_ptr<CentrallySingleton> ms_instance; // �ێ��C���X�^���X
        static Mutex ms_mutex;
        std::unordered_map<ullint, std::pair<void*, std::function<void(void*)>>> m_instances;   // �ێ����Ă���C���X�^���X�ꗗ
    };
}




//----- CentrallySingleton ��`
namespace EtherEngine {
    // �V���O���g����ǉ�����
    template <SingletonTypeConcept SingletonType>
    SingletonType* CentrallySingleton::AddSingleton(void) {
        auto ret = new SingletonType();
        auto hoge = typeid(SingletonType).hash_code();
        auto instance = std::pair<void*, std::function<void(void*)>>(static_cast<void*>(ret), [](void* instance) { 
            auto deleteInstance = static_cast<SingletonType*>(instance);
            DELETE_NULL(deleteInstance);
        });
        m_instances.emplace(typeid(SingletonType).hash_code(), instance);  // typeid.name��p���Ă��邪�N���X�ň�ӂɖ��O���擾�ł���Ηǂ��̂ŃR���p�C�����̍��ق͖�������
        return ret;
    }
    // �V���O���g�����폜����
    template <SingletonTypeConcept SingletonType>
    void CentrallySingleton::DeleteSingleton(void) {
        auto find = m_instances.find(typeid(SingletonType).hash_code());
        if (find != m_instances.end()) {
            find->second.second(find->second.first);
            m_instances.erase(find);
        }
    }
    // �V���O���g�����擾����
    template <SingletonTypeConcept SingletonType>
    SingletonType* CentrallySingleton::GetSingleton(void) {
        auto find = m_instances.find(typeid(SingletonType).hash_code());
        if (find != m_instances.end()) {
            return static_cast<SingletonType*>(find->second.first);
        }
        else {
            return AddSingleton<SingletonType>();
        }
    }
}
#endif // !I_CENTRALLYSINGLETON_H
