#ifndef I_TIMERBASE_H
#define I_TIMERBASE_H
#include <Base/Singleton.h>


//----- 別名定義
namespace EtherEngine {
    using milliSecond = float;
}


//----- 前方宣言
namespace EtherEngine {
    namespace ForwardDeclaration {
        // TimePointer用前方宣言
        class TimePointer;
    }
}


//----- Timer 宣言
namespace EtherEngine {
    // タイマー
    class Timer {
    public:
        // コンストラクタ
        Timer(void);
        // デストラクタ
        virtual ~Timer(void);
        // コピーコンストラクタ
        Timer(const Timer& copy) = default;
        // ムーブコンストラクタ
        Timer(Timer&& move) = default;


        // 現在時間を取得する
        // @ Ret  :  現在時刻
        milliSecond GetTime(void);
        // 前回からの経過時間を取得する
        // @ Memo : 初使用の際は0を返却します
        // @ Ret  : 前回DeltaTime使用時からの経過時間
        milliSecond GetDeltaTime(void);


        // @ MEMO : やる気と必要があれば
        // 現在時間をYYYY/MM/DD/ HH:MM:SS形式で出力する


    private:
        class ForwardDeclaration::TimePointer* m_deltaTime;   // Timerの現在保持時間
    };
}


//----- GlobalTimer 宣言
namespace EtherEngine {
    // グローバルタイマー
    class GlobalTimer : public Singleton<GlobalTimer> {
    public:
        // デストラクタ
        ~GlobalTimer(void) override;


        // 初期化
        // @ Memo : この初期化を行った時間を起点にします
        void Init(void);
        // 更新処理
        void Update(void);
        // 終了
        void Uninit(void);


        // グローバルタイムを取得する
        // @ Ret  : GlobalTimer初期時からの経過時間
        milliSecond GetGlobalTime(void);
        // 1フレーム秒数を取得する
        // @ Ret  : 経過時刻

    private:
        // コンストラクタ
        GlobalTimer(void);


        ForwardDeclaration::TimePointer* m_firstTime;   // 初期化時刻
        ForwardDeclaration::TimePointer* m_updateTime;  // フレーム開始時刻

        friend class CentrallySingleton;
    };
}


#endif // !I_TIMER_H
