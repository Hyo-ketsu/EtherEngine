#include <EtherEngine/MSVCMediation.h>


//----- 定数定義
namespace EtherEngine {
    const int READ_COMMAND_SIZE = 256;
}




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

        //----- パイプ作成
        SECURITY_ATTRIBUTES saAttr;
        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle = TRUE;
        saAttr.lpSecurityDescriptor = NULL;
        if (!CreatePipe(&m_childRead, &m_childWrite, &saAttr, 0) ||
            !CreatePipe(&m_read, &m_write, &saAttr, 0)) {
            //----- パイプが作成できなかった。例外送出
            throw std::exception("Error!");
        }

        //----- 
        startupInfo.cb = sizeof(startupInfo);
        startupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
        startupInfo.hStdOutput = m_write;
        startupInfo.hStdInput = m_childRead;
        startupInfo.dwFlags |= STARTF_USESTDHANDLES;
#ifdef _DEBUG
        startupInfo.wShowWindow = SW_NORMAL;
#else 
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
        if (!WriteFile(m_childWrite, inputCommand, strlen(inputCommand), &bytesWritten, NULL)) {
            //----- 書き込めない。例外送出
            HandleClose();
            throw std::exception("Error! Non write pipe");
        }
    }
    // コマンドプロンプト出力取得
    std::string MSVCMediation::ReadCmd(void) {
        //----- 変数宣言
        std::string ret;    // 読み込まれた文字列
        DWORD readBytes;    // 読み込まれたバイト数
        char buffer[READ_COMMAND_SIZE] = {'\0'};  // 読み込みバッファ

        //----- 読み取りが行えなくなるまで読み込み
        while (PeekNamedPipe(m_read, NULL, NULL, NULL, NULL, NULL) != 0) {
            //----- 読み取りと追加
            ReadFile(m_read, buffer, sizeof(buffer), &readBytes, NULL);
            ret.append(buffer, readBytes);

            //----- これ以上読み取れないなら強制的に終了する
            if (readBytes != READ_COMMAND_SIZE) break;
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
        if (ReadFile(m_childErrorRead, buffer, sizeof(buffer), &readBytes, NULL) && readBytes > 0) {
            ret.append(buffer, readBytes);
        }

        //----- 返却
        return ret;
    }


    // ハンドルのクローズ
    void MSVCMediation::HandleClose(void) {
        if (!CloseHandle(m_read)) throw std::exception("Error! Pipe close");
        if (!CloseHandle(m_write)) throw std::exception("Error! Pipe close");
        if (!CloseHandle(m_childRead)) throw std::exception("Error! Pipe close");
        if (!CloseHandle(m_childWrite)) throw std::exception("Error! Pipe close");
        if (!CloseHandle(m_childErrorRead)) throw std::exception("Error! Pipe close");
        if (!CloseHandle(m_childErrorWrite)) throw std::exception("Error! Pipe close");
    }
}
