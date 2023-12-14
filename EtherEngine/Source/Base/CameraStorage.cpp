#include <Base/CameraStorage.h>


//----- CameraSystem ��`
namespace EtherEngine {
    // �f�[�^��ǉ�����
    [[nodiscard]] IDClass CameraSystem::AddData(std::weak_ptr<CameraData> data, int priority) {
        //----- ID�̍쐬�ƒǉ�
        auto id = IDClass();
        m_datas.emplace_back(id, data, priority);

        //----- �ԋp
        return id;
    }
    // �f�[�^���폜����
    void CameraSystem::DeleteData(const IDClass& id) {
        if (m_datas.size() == 0) return;
        for (auto it = m_datas.begin(); it != m_datas.end(); it++) {
            if (std::get<0>(*it) == id) {
                //----- �폜
                m_datas.erase(it);
                break;
            }
        }
    }


    // �f�[�^���擾����
    std::optional<CameraData> CameraSystem::GetData(const IDClass& id) {
        //----- �ԋp�p�ϐ��錾
        std::optional<CameraData> ret;

        //----- ID�Ŏ擾����
        for (auto&& it : m_datas) {
            if (std::get<0>(it) == id) {
                ret = *std::get<1>(it).lock();
                break;
            }
        }

        //----- �ԋp
        return ret;
    }


    // ���C���J�������擾����
    std::optional<CameraData> CameraSystem::GetMainData(void) {
        //------ �ϐ��錾
        decltype(m_datas)::iterator useData = m_datas.begin();
        std::optional<CameraData> ret;

        //----- �f�[�^���Ȃ��Ȃ牽���Ԃ��Ȃ�
        if (m_datas.size() == 0) return ret;

        //----- ID�Ŏ擾����
        for (auto it = m_datas.begin(); it != m_datas.end(); it++) {
            if (std::get<2>(*it) > std::get<2>(*useData)) {
                useData = it;
            }
        }

        //----- �ԋp
        return std::optional<CameraData>((*std::get<1>(*useData).lock()));
    }
}
