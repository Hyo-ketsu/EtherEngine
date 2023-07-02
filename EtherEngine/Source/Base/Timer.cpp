#include <Base/Timer.h>


namespace EtherEngine {
    // 現在時間を取得する
    std::chrono::nanoseconds Timer::GetTime(void) {
        using namespace std::chrono;
        return duration_cast<nanoseconds>(GlobalTimer::Get()->GetGlobalTime());
    }


    // 前回からの経過時間を取得する
    std::chrono::nanoseconds Timer::GetDeltaTime(void) {
        //----- usingと変数宣言
        using namespace std::chrono;
        std::chrono::nanoseconds ret{};

        //----- 減算処理
        if (m_deltaTime.has_value()) {
            //----- 有効値。処理する
            ret = duration_cast<nanoseconds>(std::chrono::steady_clock::now() - m_deltaTime.value());
        }
        else {
            m_deltaTime.emplace(std::chrono::steady_clock::now());
        }

        //----- 時間更新
        m_deltaTime.value() = std::chrono::steady_clock::now();

        //----- 返却
        return ret;
    }
}


namespace EtherEngine {
    // 初期化
    void GlobalTimer::Init(void) {
        m_firstTime = std::chrono::steady_clock::now();
    }
    // 終了
    void GlobalTimer::Uninit(void) {

    }


    // グローバルタイムを取得する
    // @ Ret  : GlobalTimer初期時からの経過時間
    std::chrono::nanoseconds GlobalTimer::GetGlobalTime(void) {
        return std::chrono::steady_clock::now() - m_firstTime.value();
    }
}
