#include <EtherEngine/CommandPrompt.h>
#include <Base/EditorException.h> 


//----- 定数定義
namespace EtherEngine {
    const int READ_COMMAND_SIZE = 256;
}




//----- CommandPrompt 定義
namespace EtherEngine {
    // コンストラクタ
    CommandPrompt::CommandPrompt(const bool isShowPrompt) {
        //----- 変数宣言と初期化
        STARTUPINFO startupInfo;
        ZeroMemory(&startupInfo, sizeof(startupInfo));
        ZeroMemory(&m_processInfo, sizeof(m_processInfo));

        //----- パイプ作成
        SECURITY_ATTRIBUTES saAttr;
        ZeroMemory(&saAttr, sizeof(saAttr));
        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle = TRUE;
        saAttr.lpSecurityDescriptor = NULL;
        if (!CreatePipe(&m_childRead, &m_childWrite, &saAttr, 0) ||
            !CreatePipe(&m_read, &m_write, &saAttr, 0)) {
            //----- パイプが作成できなかった。例外送出
            throw EditorException("Error!");
        }

        //----- プロセスの立ち上げ設定
        startupInfo.cb = sizeof(startupInfo);
        startupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
        startupInfo.hStdOutput = m_write;
        startupInfo.hStdInput = m_childRead;
        startupInfo.dwFlags |= STARTF_USESTDHANDLES;
        if (isShowPrompt) {
            startupInfo.wShowWindow = SW_NORMAL;
        }
        else {
            startupInfo.wShowWindow = SW_HIDE;
        }

        //----- 入力コマンド用変数宣言
        char pram[64] = "cmd.exe";

        //----- コマンドプロンプト立ち上げ
        if (!CreateProcess(
            NULL,
            pram,
            NULL,
            NULL,
            TRUE,
            0,
            NULL,
            NULL,
            &startupInfo,
            &m_processInfo
            )) {
            //----- 立ち上げができなかった。例外送出
            HandleClose();
            throw EditorException("Error!");
        }
    }
    // デストラクタ
    CommandPrompt::~CommandPrompt(void) {
        HandleClose();

        WaitForSingleObject(m_processInfo.hProcess, INFINITE);

        CloseHandle(m_processInfo.hProcess);
        CloseHandle(m_processInfo.hThread);
    }


    // コマンド入力
    void CommandPrompt::Write(const std::string& command) {
        //----- 変数宣言
        DWORD bytesWritten; // 書き込みバイト数

        //----- パイプ書き込み
        WriteFile(m_childWrite, command.c_str(), command.size(), &bytesWritten, NULL);
    }
    // ディレクトリ遷移
    void CommandPrompt::CD(const std::string& dir) {
        //----- ディレクトリ存在チェック
        PathClass path = PathClass(dir);
        if (path.IsDirectory() && path.IsExists()) {
            //----- 遷移できる。遷移
            this->Write(std::string("cd ") + dir);
        }
        else {
            //----- 明らかに遷移できない。例外送出
            throw EditorException("Error! Destination directory does not exist");
        }
    }
    // コマンドプロンプト出力取得
    std::string CommandPrompt::Read(void) {
        //----- 変数宣言
        std::string ret;    // 読み込まれた文字列
        DWORD readBytes;    // 読み込まれたバイト数
        char buffer[READ_COMMAND_SIZE] = {'\0'};  // 読み込みバッファ

        //----- 読み取りが行えなくなるまで読み込み
        while (PeekNamedPipe(m_read, buffer, 1, &readBytes, NULL, NULL) != FALSE && readBytes != 0) {   // 読み込みが行える、かつ1文字以上でも読み込んだか
            //----- 読み取りと追加
            if (ReadFile(m_read, buffer, sizeof(buffer), &readBytes, NULL) != FALSE) {
                ret.append(buffer, readBytes);
            }
        }

        //----- 返却
        return ret;
    }
    // コマンドプロンプトエラー出力取得
    std::string CommandPrompt::ReadError(void) {
        //----- 変数宣言
        std::string ret;    // 読み込まれた文字列
        DWORD readBytes;    // 読み込まれたバイト数
        char buffer[READ_COMMAND_SIZE];   // 読み込みバッファ

        //----- 読み取りが行えなくなるまで読み込み
        while (PeekNamedPipe(m_childRead, buffer, 1, &readBytes, NULL, NULL) != FALSE && readBytes != 0) {   // 読み込みが行える、かつ1文字以上でも読み込んだか
            //----- 読み取りと追加
            if (ReadFile(m_childRead, buffer, sizeof(buffer), &readBytes, NULL) != FALSE) {
                ret.append(buffer, readBytes);
            }
        }

        //----- 返却
        return ret;
    }


    // ハンドルのクローズ
    void CommandPrompt::HandleClose(void) {
        if (!CloseHandle(m_read)) throw EditorException("Error! Pipe close");
        if (!CloseHandle(m_write)) throw EditorException("Error! Pipe close");
        if (!CloseHandle(m_childRead)) throw EditorException("Error! Pipe close");
        if (!CloseHandle(m_childWrite)) throw EditorException("Error! Pipe close");
        //if (!CloseHandle(m_childErrorRead)) throw EditorException("Error! Pipe close");    // @ MEMO : 例外を吐くのでいったんコメントアウト
        //if (!CloseHandle(m_childErrorWrite)) throw EditorException("Error! Pipe close");
    }
}
