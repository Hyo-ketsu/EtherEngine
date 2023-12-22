#include <Base/CameraStorage.h>


//----- CameraSystem 定義
namespace EtherEngine {
    // データを追加する
    [[nodiscard]] IDNumberType CameraSystem::AddData(std::weak_ptr<CameraData> data, int priority) {
        //----- IDの作成と追加
        m_datas.emplace_back(data.lock()->GetId(), data, priority);

        //----- 返却
        return data.lock()->GetId();
    }
    // データを削除する
    void CameraSystem::DeleteData(const IDNumberType& id) {
        if (m_datas.size() == 0) return;
        for (auto it = m_datas.begin(); it != m_datas.end(); it++) {
            if (std::get<0>(*it) == id) {
                //----- 削除
                m_datas.erase(it);
                break;
            }
        }
    }


    // データを取得する
    std::optional<CameraData> CameraSystem::GetData(const IDNumberType& id) {
        //----- 返却用変数宣言
        std::optional<CameraData> ret;

        //----- IDで取得する
        for (auto&& it : m_datas) {
            if (std::get<0>(it) == id) {
                ret = *std::get<1>(it).lock();
                break;
            }
        }

        //----- 返却
        return ret;
    }


    // メインカメラを取得する
    std::optional<CameraData> CameraSystem::GetMainData(void) {
        //------ 変数宣言
        decltype(m_datas)::iterator useData = m_datas.begin();
        std::optional<CameraData> ret;

        //----- データがないなら何も返さない
        if (m_datas.size() == 0) return ret;

        //----- IDで取得する
        for (auto it = m_datas.begin(); it != m_datas.end(); it++) {
            if (std::get<2>(*it) > std::get<2>(*useData)) {
                useData = it;
            }
        }

        //----- 返却
        return std::optional<CameraData>((*std::get<1>(*useData).lock()));
    }
}
