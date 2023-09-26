#include <EtherEngine/MSVCMediation.h>


//----- MSVCMediation 定義
namespace EtherEngine {
    // コンストラクタ
    MSVCMediation::MSVCMediation(void) {
    }


    // 初期化する
    void MSVCMediation::Init(const PathClass& cmdPath, const PathClass& msvcPath) {
        //----- 変数宣言と初期化
        STARTUPINFO startupInfo;
        ZeroMemory(&startupInfo, sizeof(startupInfo));
        ZeroMemory(&m_processInfo, sizeof(m_processInfo));
        startupInfo.cb = sizeof(startupInfo);

        //----- パイプ作成
        SECURITY_ATTRIBUTES saAttr;
        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle = TRUE;
        saAttr.lpSecurityDescriptor = NULL;
        if (!CreatePipe(&m_childRead, &m_childWrite, &saAttr, 0) || 
            !CreatePipe(&m_childErrorRead, &m_childErrorWrite, &saAttr, 0) ||
            !SetHandleInformation(m_childRead, HANDLE_FLAG_INHERIT, 0) ||
            !SetHandleInformation(m_childErrorRead, HANDLE_FLAG_INHERIT, 0)) {
            //----- パイプが作成できなかった。例外送出
            throw std::exception("Error!");
        }

        //----- 
        startupInfo.cb = sizeof(STARTUPINFO);
        startupInfo.hStdError = m_childErrorWrite; // Use the standard error handle of the parent process
        startupInfo.hStdOutput = m_childWrite; // Use the standard output handle of the parent process
        startupInfo.hStdInput = m_childRead; // Use the read end of the input pipe for the child process
        startupInfo.dwFlags |= STARTF_USESTDHANDLES;
#ifdef _DEBUG
        startupInfo.wShowWindow = SW_HIDE;
#endif // _DEBUG

        //----- 入力コマンド用変数宣言
        // @ Memo : CreateProcessの第2引数がconst char*では正常に動作しないため
        // @ MEMO : 余分なバッファが必要？
        char pram[1024];
        strcpy_s(pram, msvcPath.Get().c_str());

        //----- コマンドプロンプト立ち上げ
        if (!CreateProcess(
            cmdPath.Get().c_str(), 
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
            throw std::exception("Error!");
        }
    }
    // 終了処理
    void MSVCMediation::Uninit(void) {
        HandleClose();

        WaitForSingleObject(m_processInfo.hProcess, INFINITE);

        CloseHandle(m_processInfo.hProcess);
        CloseHandle(m_processInfo.hThread);
    }


    // コマンド入力
    void MSVCMediation::WriteCmd(const std::string& command) {
        //----- 変数宣言
        DWORD bytesWritten; // 書き込みバイト数
        char inputCommand[1024];

        //----- コマンド設定
        strcpy_s(inputCommand, command.c_str());
        inputCommand[strlen(inputCommand) + 1] = '\0';
        inputCommand[strlen(inputCommand)] = '\n';

        //----- パイプ書き込み
        if (!WriteFile(
            m_childWrite,
            inputCommand,
            strlen(inputCommand),
            &bytesWritten,
            NULL
        )) {
            //----- 書き込めない。例外送出
            throw std::exception("Error! Non write pipe");
        }
    }
    // コマンドプロンプト出力取得
    std::string MSVCMediation::ReadCmd(void) {
        //----- 変数宣言
        std::string ret;    // 読み込まれた文字列
        char buffer[256];   // 読み込みバッファ
        DWORD readBytes;    // 読み込まれたバイト数

        //----- 読み込み
        WaitForSingleObject(m_processInfo.hProcess, 10000);
        while (ReadFile(m_childRead, buffer, sizeof(buffer), &readBytes, NULL) && readBytes > 0) {
            ret.append(buffer, readBytes);
        }

        //----- 返却
        return ret;
    }
    // コマンドプロンプトエラー出力取得
    std::string MSVCMediation::ReadCmdError(void) {
        //----- 変数宣言
        std::string ret;    // 読み込まれた文字列
        char buffer[256];   // 読み込みバッファ
        DWORD readBytes;    // 読み込まれたバイト数

        //----- 読み込み
        while (ReadFile(m_childErrorRead, buffer, sizeof(buffer), &readBytes, NULL) && readBytes > 0) {
            ret.append(buffer, readBytes);
        }

        //----- 返却
        return ret;
    }


    // ハンドルのクローズ
    void MSVCMediation::HandleClose(void) {
        CloseHandle(m_childRead);
        CloseHandle(m_childWrite);
        CloseHandle(m_childErrorRead);
        CloseHandle(m_childErrorWrite);
    }
}
