#include <Base/CameraStorage.h>


namespace EtherEngine {
    // �J������ǉ�����
    void CameraStorage::AddCamera(CameraBase& camera, const IDClass& id) {
        m_cameras.emplace_back(id, camera, false);
    }
    // �J�������폜����
    void CameraStorage::DeleteCamera(const IDClass& id) {
        for (auto it = m_cameras.begin(); it != m_cameras.end(); it++) {
            if (std::get<0>(*it) == id && std::get<2>(*it) == false) {
                //----- �폜
                std::get<2>(*it) = true;
                m_cameras.erase(it);
                break;
            }
        }
    }


    // �w�肵��ID�̃J���������݂��邩
    bool CameraStorage::IsIDToCamera(const IDClass& id) {
        //----- ID�Ŏ擾����
        for (auto&& it : m_cameras) {
            if (std::get<0>(it) == id) {
                return true;
            }
        }

        return false;
    }


    // �J�������擾����
    [[deprecated]] CameraBase* const CameraStorage::GetCamera(const uint priority) {
        //----- �\�[�g��������
        std::sort(m_cameras.begin(), m_cameras.end(), [](decltype(*m_cameras.begin()) i, decltype(*m_cameras.begin()) j) -> bool {
            return std::get<1>(i).AccessCameraData().GetPriority() > std::get<1>(j).AccessCameraData().GetPriority();
            });

        //----- �D�揇�ʂŎ擾
        if (m_cameras.size() > priority) {
            return &std::get<1>(m_cameras[priority]);
        }

        //----- �w�菇�ʂ��Ȃ� or �J�������Ȃ��Bnullptr�ԋp
        return nullptr;
    }

    // �J�������擾����
    CameraBase* const CameraStorage::GetCamera(const IDClass& id) {
        //----- ID�Ŏ擾����
        for (auto&& it : m_cameras) {
            if (std::get<0>(it) == id) {
                return &std::get<1>(it);
            }
        }

        //----- �ԋp
        return nullptr;
    }
}
