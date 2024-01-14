#include <Base/CentrallySingleton.h>


namespace EtherEngine {
    // �R���X�g���N�^
    CentrallySingleton::CentrallySingleton(void) {
    }
    // �f�X�g���N�^
    CentrallySingleton::~CentrallySingleton(void) {
        for (auto&& it : m_instances) {
            it.second.second(it.second.first);
        }
        m_instances.clear();
    }
    // �C���X�^���X���擾����
    std::shared_ptr<CentrallySingleton>& CentrallySingleton::Get(void) {
        //----- ���b�N���s��
        auto lock = ms_mutex.KeyLock();

        //----- �C���X�^���X�̐������f
        if (ms_instance == nullptr) {
            ms_instance = decltype(ms_instance)(new CentrallySingleton());
        }

        //----- �ԋp
        return ms_instance;
    }
    // �C���X�^���X��ݒ肷��
    void CentrallySingleton::Set(std::shared_ptr<CentrallySingleton> instance) {
        //----- ���b�N���s��
        auto lock = ms_mutex.KeyLock();

        //----- �ݒ�
        ms_instance = instance;
    }

    std::shared_ptr<CentrallySingleton> CentrallySingleton::ms_instance; // �ێ��C���X�^���X
    Mutex CentrallySingleton::ms_mutex;
}
