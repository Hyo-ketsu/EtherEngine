#include <Base/CentrallySingleton.h>


namespace EtherEngine {
    // コンストラクタ
    CentrallySingleton::CentrallySingleton(void) {
    }
    // デストラクタ
    CentrallySingleton::~CentrallySingleton(void) {
        for (auto&& it : m_instances) {
            it.second.second(it.second.first);
        }
        m_instances.clear();
    }
    // インスタンスを取得する
    std::shared_ptr<CentrallySingleton>& CentrallySingleton::Get(void) {
        //----- ロックを行う
        auto lock = ms_mutex.KeyLock();

        //----- インスタンスの生成判断
        if (ms_instance == nullptr) {
            ms_instance = decltype(ms_instance)(new CentrallySingleton());
        }

        //----- 返却
        return ms_instance;
    }
    // インスタンスを設定する
    void CentrallySingleton::Set(std::shared_ptr<CentrallySingleton> instance) {
        //----- ロックを行う
        auto lock = ms_mutex.KeyLock();

        //----- 設定
        ms_instance = instance;
    }

    std::shared_ptr<CentrallySingleton> CentrallySingleton::ms_instance; // 保持インスタンス
    Mutex CentrallySingleton::ms_mutex;
}
