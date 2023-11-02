#include <Base/LogSystem.h>


//----- 画面出力あたりの定義
namespace EtherEngine {
    // コンストラクタ
    LogWindowMessage::LogWindowMessage(const LogWindowMessageType& type, const std::chrono::system_clock::time_point& timeStamp, const std::string& message)
        : m_type(type)
        , m_timeStamp(timeStamp) 
        , m_message(message) {
    }
    // コンストラクタ
    LogWindowMessage::LogWindowMessage(const std::string& message, const LogWindowMessageType& type)
        : LogWindowMessage(type, std::chrono::system_clock::now(), message){
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


    // ビルド結果のメッセージをログに追加する
    void LogSystem::AddBuildLogMessage(const std::string& message) {
        //----- 追加
        ms_buildLog += message + '\n';
    }
    // ビルド結果のログを取得する
    std::string LogSystem::GetBuildLogMessage(void) {
        //----- 取得
        return ms_buildLog;
    }
    // ビルドログをすべて消去する
    void LogSystem::DeleteBuildLogMessage(void) {
        ms_buildLog.clear();
    }

    
    std::vector<LogWindowMessage> LogSystem::ms_logWindowMessage;   // 画面表示のログ
    std::string LogSystem::ms_buildLog; // build結果の出力ログ
    SpinLock LogSystem::ms_spinlock; // スピンロックを提供する
}
