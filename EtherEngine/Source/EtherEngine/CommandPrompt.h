#ifndef I_MSVCMEDIATION_H
#define I_MSVCMEDIATION_H
#include <Base/Singleton.h>
#include <Base/PathClass.h>


//----- CommandPrompt 定義
namespace EtherEngine {
    // コマンドプロンプトでの入出力を仲介するクラス
    class CommandPrompt {
    public:
        // コンストラクタ
        // @ MEMO : プロンプト表示には現在対応しておりません(子プロセスの出力パイプは取ったままなので)
        // @ Arg1 : プロンプトを表示するか(Default : false)
        CommandPrompt(const bool isShowPrompt = false);
        // デストラクタ
        ~CommandPrompt(void);
        // コピーコンストラクタ
        CommandPrompt(const CommandPrompt& copy) = delete;
        // ムーブコンストラクタ
        CommandPrompt(CommandPrompt&& move) = delete;


        // コマンド入力
        // @ Arg1 : 入力コマンド
        void Write(const std::string& commnad);
        // ディレクトリ遷移
        // @ Exce : 遷移が行えたか
        // @ Arg1 : 遷移先ディレクトリ
        void CD(const std::string& dir);
        // コマンドプロンプト出力取得
        // @ Memo : この関数は待ちなどは一切行いません。
        // @ Ret  : 取得結果
        std::string Read(void);
        // コマンドプロンプトエラー出力取得
        // @ Memo : この関数は待ちなどは一切行いません。
        // @ Ret  : 取得結果
        std::string ReadError(void);

    private:
        // ハンドルのクローズ
        void HandleClose(void);

        PROCESS_INFORMATION m_processInfo;
        HANDLE m_childRead;   // cmd用読み取り用パイプ
        HANDLE m_childWrite;  // cmd用書き込み用パイプ
        HANDLE m_read;        // 読み取り用パイプ
        HANDLE m_write;       // 書き込み用パイプ
        HANDLE m_childErrorRead;   // エラー読み取り用パイプ
        HANDLE m_childErrorWrite;  // エラー書き込み用パイプ
    };
}


#endif // !I_MSVCMEDIATION_H
