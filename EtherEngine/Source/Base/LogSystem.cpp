#include <Base/LogSystem.h>


//----- 画面出力あたりの定義
namespace EtherEngine {
    // コンストラクタ
    // @ Arg1 : 表示メッセージタイプ
    // @ Arg2 : メッセージ出力時間
    // @ Arg3 : メッセージ
    LogWindowMessage::LogWindowMessage(const LogWindowMessageType& type, const std::chrono::steady_clock::time_point& timeStamp, const std::string& message) 
        : m_type(type)
        , m_timeStamp(timeStamp) 
        , m_message(message) {
    }
}


//----- LogSystem 定義
namespace EtherEngine {
    // 画面表示ログにメッセージを追加する
    void LogSystem::AddLogWindowMessage(const LogWindowMessage& message) {
        //----- ロック
        auto lock = ms_spinlock.KeyLock();

        //----- 追加
        ms_logWindowMessage.push_back(message);
    }
    // 画面表示ログを取得する
    std::vector<LogWindowMessage> LogSystem::GetLogWindowMessage(void) {
        //----- ロック
        auto lock = ms_spinlock.KeyLock();

        //----- 返却
        return ms_logWindowMessage;
    }
    // 画面表示ログを消去する
    void LogSystem::DeleteLogWindowMessage(void) {
        //----- ロック
        auto lock = ms_spinlock.KeyLock();

        //----- 削除
        ms_logWindowMessage.clear();
    }

    
    std::vector<LogWindowMessage> LogSystem::ms_logWindowMessage;   // 画面表示のログ
    SpinLock LogSystem::ms_spinlock; // スピンロックを提供する
}
