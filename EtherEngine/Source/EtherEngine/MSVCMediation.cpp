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
        if (!CreatePipe(&m_childStdInRead, &m_childStdInWrite, &saAttr, 0)) {
            //----- パイプが作成できなかった。例外送出
            throw std::exception("Error!");
        }

        //----- 
        SetHandleInformation(m_childStdInWrite, HANDLE_FLAG_INHERIT, 0);

        //-----
        startupInfo.cb = sizeof(STARTUPINFO);
        startupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE); // Use the standard error handle of the parent process
        startupInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE); // Use the standard output handle of the parent process
        startupInfo.hStdInput = m_childStdInRead; // Use the read end of the input pipe for the child process
        startupInfo.dwFlags |= STARTF_USESTDHANDLES;
#ifdef _DEBUG
        startupInfo.wShowWindow = SW_HIDE;
#endif // _DEBUG

        //----- 入力コマンド用変数宣言
        // @ Memo : CreateProcessの第2引数がconst char*では正常に動作しないため
        char pram[512];
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
            CloseHandle(m_childStdInRead);
            CloseHandle(m_childStdInWrite);
            throw std::exception("Error!");
        }
    }
    // 終了処理
    void MSVCMediation::Uninit(void) {
        CloseHandle(m_childStdInWrite);

        WaitForSingleObject(m_processInfo.hProcess, INFINITE);

        CloseHandle(m_processInfo.hProcess);
        CloseHandle(m_processInfo.hThread);
    }


    // コマンド入力
    bool MSVCMediation::Command(const std::string& command) {
        //----- 変数宣言
        DWORD bytesWritten;
        char inputCommand[1024];

        //----- コマンドの設定
        strcpy_s(inputCommand, command.c_str());
        inputCommand[strlen(inputCommand) + 1] = '\0';
        inputCommand[strlen(inputCommand)] = '\n';

        //----- パイプ書き込み
        if (!WriteFile(
            m_childStdInWrite,
            inputCommand,
            strlen(inputCommand),
            &bytesWritten,
            NULL
        )) {
            //----- 書き込めない。例外送出
            throw std::exception("Error! Non write pipe");
        }
    }
}
