#ifndef I_LOGSYSTEM_H
#define I_LOGSYSTEM_H
#include <Base/SpinLock.h>


//----- 画面出力あたりの宣言
namespace EtherEngine {
    // 画面出力ログの種類
    enum class LogWindowMessageType {
        MessageShow = 0,    // 通常のメッセージ
        HelpShow,           // ヘルプ表示
        WarningShow,        // 警告表示
        ErrorShow,          // エラー表示
        NoneShow,           // 特に表示しない
    };


    // 画面表示ログ用クラス
    struct LogWindowMessage {
        // コンストラクタ
        // @ Arg1 : 表示メッセージタイプ
        // @ Arg2 : メッセージ出力時間
        // @ Arg3 : メッセージ
        LogWindowMessage(const LogWindowMessageType& type, const std::chrono::system_clock::time_point& timeStamp, const std::string& message);
        // コンストラクタ
        // @ Arg1 : メッセージ
        // @ Arg2 : 表示メッセージタイプ(Default : MessageShow)
        LogWindowMessage(const std::string& message, const LogWindowMessageType& type = LogWindowMessageType::MessageShow);


        LogWindowMessageType m_type;    // 表示メッセージタイプ
        std::chrono::system_clock::time_point m_timeStamp;  // メッセージ出力時間
        std::string m_message;          // メッセージ
    };
}


//----- LogSystem 宣言
namespace EtherEngine {
    // ログ（画面に表示するものやファイルに出力するログ）を管理するクラス
    class LogSystem {
    public:
        // コンストラクタ
        LogSystem(void) = delete;
        // デストラクタ
        ~LogSystem(void) = delete;
        // コピーコンストラクタ
        LogSystem(const LogSystem& copy) = delete;
        // ムーブコンストラクタ
        LogSystem(LogSystem&& move) = delete;


        // 画面表示ログにメッセージを追加する
        // @ Arg1 : 追加するメッセージ
        static void AddLogWindowMessage(const LogWindowMessage& message);
        // 画面表示ログを取得する
        // @ Ret  : 取得するメッセージ
        static std::vector<LogWindowMessage> GetLogWindowMessage(void);
        // 画面表示ログを消去する
        static void DeleteLogWindowMessage(void);


        // ビルド結果のメッセージをログに追加する
        // @ Memo : 改行が自動的に行われます
        // @ Arg1 : 追加する行
        static void AddBuildLogMessage(const std::string& message);
        // ビルド結果のログを取得する
        // @ Ret  : ビルドログ
        static std::string GetBuildLogMessage(void);
        // ビルドログをすべて消去する
        static void DeleteBuildLogMessage(void);

    private:
        static std::vector<LogWindowMessage> ms_logWindowMessage;    // 画面表示のログ
        static std::string ms_buildLog; // build結果の出力ログ
        static SpinLock ms_spinlock; // スピンロックを提供する
    };
}


#endif // !I_LOGSYSTEM_H
