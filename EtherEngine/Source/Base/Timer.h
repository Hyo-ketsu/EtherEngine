#ifndef I_TIMERBASE_H
#define I_TIMERBASE_H

#include <Base/Singleton.h>


namespace EtherEngine {
    // タイマー
    class Timer {
    public:
        // 現在時間を取得する
        // @ Ret  :  現在時刻
        std::chrono::nanoseconds GetTime(void);


        // 前回からの経過時間を取得する
        // @ Memo : 初使用の際は0を返却します
        // @ Ret  : 前回DeltaTime使用時からの経過時間
        std::chrono::nanoseconds GetDeltaTime(void);

    private:
        std::optional<std::chrono::steady_clock::time_point> m_deltaTime;   // 前回DeltaTime使用時時刻
    };


    // グローバルタイマー
    class GlobalTimer : public Singleton<GlobalTimer> {
    public:
        // デストラクタ
        ~GlobalTimer(void) override {}


        // 初期化
        // @ Memo : この初期化を行った時間を起点にします
        void Init(void);
        // 終了
        void Uninit(void);


        // グローバルタイムを取得する
        // @ Ret  : GlobalTimer初期時からの経過時間
        std::chrono::nanoseconds GetGlobalTime(void);

    private:
        // コンストラクタ
        GlobalTimer(void) {}


        std::optional<std::chrono::steady_clock::time_point> m_firstTime;   // 初期化時刻

        friend class Singleton<GlobalTimer>;
    };
}


#endif // !I_TIMER_H
