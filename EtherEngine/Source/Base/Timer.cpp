#include <Base/Timer.h>


//----- 前方宣言定義
namespace EtherEngine {
    namespace ForwardDeclaration {
        // TimePointer用前方宣言
        class TimePointer {
        public:
            // コンストラクタ
            TimePointer(std::chrono::steady_clock::time_point timePoint)
                : m_timePoint(timePoint) {
            }
            // デストラクタ
            TimePointer(void) {}
            // コピー代入
            TimePointer& operator =(const TimePointer& copy) = default;


            operator std::chrono::steady_clock::time_point(void) { return m_timePoint; }


            std::chrono::steady_clock::time_point m_timePoint;  
        };
    }
}


//----- Timer 定義
namespace EtherEngine {
    using namespace EtherEngine::ForwardDeclaration;


    // コンストラクタ
    Timer::Timer(void) 
        : m_deltaTime(nullptr) {
    }
    // デストラクタ
    Timer::~Timer(void) {
    }
    // 現在時間を取得する
    milliSecond Timer::GetTime(void) {
        return GlobalTimer::Get()->GetGlobalTime();
    }


    // 前回からの経過時間を取得する
    milliSecond Timer::GetDeltaTime(void) {
        //----- usingと変数宣言
        milliSecond ret = 0;

        //----- 減算処理
        if (m_deltaTime == nullptr) {
            //----- 無効値。初期化
            m_deltaTime = new TimePointer(std::chrono::steady_clock::now());
        }
        else {
            //----- 有効値。処理する
            ret = (std::chrono::steady_clock::now() - m_deltaTime->m_timePoint).count() * 0.001f * 0.001f;  // ナノ秒をマイクロ秒、ミリ秒へ変換
        }

        //----- 時間更新
        *m_deltaTime = std::chrono::steady_clock::now();

        //----- 返却
        return ret;
    }
}


namespace EtherEngine {
    // コンストラクタ
    GlobalTimer::GlobalTimer(void) 
        : m_firstTime(new TimePointer(std::chrono::steady_clock::now()))
        , m_updateTime(new TimePointer(*m_firstTime)) {
    }
    // デストラクタ
    GlobalTimer::~GlobalTimer(void) {
        delete m_updateTime;
        delete m_firstTime;
    }


    // 初期化
    void GlobalTimer::Init(void) {
    }
    // 更新
    void GlobalTimer::Update(void) {
        *m_updateTime = TimePointer(std::chrono::steady_clock::now());
    }
    // 終了
    void GlobalTimer::Uninit(void) {
    }


    // グローバルタイムを取得する
    // @ Ret  : GlobalTimer初期時からの経過時間
    milliSecond GlobalTimer::GetGlobalTime(void) {
        //----- 経過時間をナノ秒で取得
        auto second = std::chrono::steady_clock::now() - m_firstTime->m_timePoint;

        //----- ナノ秒をマイクロ秒からミリ秒に変換して返却
        return second.count() * 0.001f * 0.001f;
    }
}
