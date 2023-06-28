#include <Base/CameraStorage.h>


namespace EtherEngine {
    // カメラを追加する
    [[nodiscard]] CameraID CameraStorage::AddCamera(CameraBase& camera) {
        //----- IDの作成と追加
        auto ptr = std::make_shared<IDClass>(IDClass());
        m_cameras.emplace_back(ptr, &camera, false);

        //----- 返却
        return CameraID(ptr);
    }
    // カメラを削除する
    void CameraStorage::DeleteCamera(const CameraID& id) {
        if (id.expired()) return;
        if (m_cameras.size() == 0) return;
        for (auto it = m_cameras.begin(); it != m_cameras.end(); it++) {
            if (*std::get<0>(*it) == *id.lock() && std::get<2>(*it) == false) {
                //----- 削除
                std::get<2>(*it) = true;
                m_cameras.erase(it);
                break;
            }
        }
    }


    // 指定したIDのカメラが存在するか
    bool CameraStorage::IsIDToCamera(const IDClass& id) {
        //----- IDで取得する
        for (auto&& it : m_cameras) {
            if (*std::get<0>(it) == id) {
                return true;
            }
        }

        return false;
    }


    // カメラを取得する
    [[deprecated]] CameraBase* const CameraStorage::GetCamera(const uint priority) {
        //----- ソートをかける
        std::sort(m_cameras.begin(), m_cameras.end(), [](decltype(*m_cameras.begin()) i, decltype(*m_cameras.begin()) j) -> bool {
            return std::get<1>(i)->AccessCameraData().GetPriority() > std::get<1>(j)->AccessCameraData().GetPriority();
            });

        //----- 優先順位で取得
        if (m_cameras.size() > priority) {
            return std::get<1>(m_cameras[priority]);
        }

        //----- 指定順位がない or カメラがない。nullptr返却
        return nullptr;
    }

    // カメラを取得する
    CameraBase* const CameraStorage::GetCamera(const IDClass& id) {
        //----- IDで取得する
        for (auto&& it : m_cameras) {
            if (*std::get<0>(it) == id) {
                return std::get<1>(it);
            }
        }

        //----- 返却
        return nullptr;
    }
}
