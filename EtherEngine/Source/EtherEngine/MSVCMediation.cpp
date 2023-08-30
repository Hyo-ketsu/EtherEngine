#include <EtherEngine/MSVCMediation.h>


//----- MSVCMediation ��`
namespace EtherEngine {
    // �R���X�g���N�^
    MSVCMediation::MSVCMediation(void) {
    }


    // ����������
    void MSVCMediation::Init(const PathClass& cmdPath, const PathClass& msvcPath) {
        //----- �ϐ��錾�Ə�����
        STARTUPINFO startupInfo;
        ZeroMemory(&startupInfo, sizeof(startupInfo));
        ZeroMemory(&m_processInfo, sizeof(m_processInfo));
        startupInfo.cb = sizeof(startupInfo);

        //----- �p�C�v�쐬
        SECURITY_ATTRIBUTES saAttr;
        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle = TRUE;
        saAttr.lpSecurityDescriptor = NULL;
        if (!CreatePipe(&m_childStdInRead, &m_childStdInWrite, &saAttr, 0)) {
            //----- �p�C�v���쐬�ł��Ȃ������B��O���o
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

        //----- ���̓R�}���h�p�ϐ��錾
        // @ Memo : CreateProcess�̑�2������const char*�ł͐���ɓ��삵�Ȃ�����
        char pram[512];
        strcpy_s(pram, msvcPath.Get().c_str());

        //----- �R�}���h�v�����v�g�����グ
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
            //----- �����グ���ł��Ȃ������B��O���o
            CloseHandle(m_childStdInRead);
            CloseHandle(m_childStdInWrite);
            throw std::exception("Error!");
        }
    }
    // �I������
    void MSVCMediation::Uninit(void) {
        CloseHandle(m_childStdInWrite);

        WaitForSingleObject(m_processInfo.hProcess, INFINITE);

        CloseHandle(m_processInfo.hProcess);
        CloseHandle(m_processInfo.hThread);
    }


    // �R�}���h����
    bool MSVCMediation::Command(const std::string& command) {
        //----- �ϐ��錾
        DWORD bytesWritten;
        char inputCommand[1024];

        //----- �R�}���h�̐ݒ�
        strcpy_s(inputCommand, command.c_str());
        inputCommand[strlen(inputCommand) + 1] = '\0';
        inputCommand[strlen(inputCommand)] = '\n';

        //----- �p�C�v��������
        if (!WriteFile(
            m_childStdInWrite,
            inputCommand,
            strlen(inputCommand),
            &bytesWritten,
            NULL
        )) {
            //----- �������߂Ȃ��B��O���o
            throw std::exception("Error! Non write pipe");
        }
    }
}
