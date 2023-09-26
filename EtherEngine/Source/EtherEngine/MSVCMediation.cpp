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
        if (!CreatePipe(&m_childRead, &m_childWrite, &saAttr, 0) || 
            !CreatePipe(&m_childErrorRead, &m_childErrorWrite, &saAttr, 0) ||
            !SetHandleInformation(m_childRead, HANDLE_FLAG_INHERIT, 0) ||
            !SetHandleInformation(m_childErrorRead, HANDLE_FLAG_INHERIT, 0)) {
            //----- �p�C�v���쐬�ł��Ȃ������B��O���o
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

        //----- ���̓R�}���h�p�ϐ��錾
        // @ Memo : CreateProcess�̑�2������const char*�ł͐���ɓ��삵�Ȃ�����
        // @ MEMO : �]���ȃo�b�t�@���K�v�H
        char pram[1024];
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
            HandleClose();
            throw std::exception("Error!");
        }
    }
    // �I������
    void MSVCMediation::Uninit(void) {
        HandleClose();

        WaitForSingleObject(m_processInfo.hProcess, INFINITE);

        CloseHandle(m_processInfo.hProcess);
        CloseHandle(m_processInfo.hThread);
    }


    // �R�}���h����
    void MSVCMediation::WriteCmd(const std::string& command) {
        //----- �ϐ��錾
        DWORD bytesWritten; // �������݃o�C�g��
        char inputCommand[1024];

        //----- �R�}���h�ݒ�
        strcpy_s(inputCommand, command.c_str());
        inputCommand[strlen(inputCommand) + 1] = '\0';
        inputCommand[strlen(inputCommand)] = '\n';

        //----- �p�C�v��������
        if (!WriteFile(
            m_childWrite,
            inputCommand,
            strlen(inputCommand),
            &bytesWritten,
            NULL
        )) {
            //----- �������߂Ȃ��B��O���o
            throw std::exception("Error! Non write pipe");
        }
    }
    // �R�}���h�v�����v�g�o�͎擾
    std::string MSVCMediation::ReadCmd(void) {
        //----- �ϐ��錾
        std::string ret;    // �ǂݍ��܂ꂽ������
        char buffer[256];   // �ǂݍ��݃o�b�t�@
        DWORD readBytes;    // �ǂݍ��܂ꂽ�o�C�g��

        //----- �ǂݍ���
        WaitForSingleObject(m_processInfo.hProcess, 10000);
        while (ReadFile(m_childRead, buffer, sizeof(buffer), &readBytes, NULL) && readBytes > 0) {
            ret.append(buffer, readBytes);
        }

        //----- �ԋp
        return ret;
    }
    // �R�}���h�v�����v�g�G���[�o�͎擾
    std::string MSVCMediation::ReadCmdError(void) {
        //----- �ϐ��錾
        std::string ret;    // �ǂݍ��܂ꂽ������
        char buffer[256];   // �ǂݍ��݃o�b�t�@
        DWORD readBytes;    // �ǂݍ��܂ꂽ�o�C�g��

        //----- �ǂݍ���
        while (ReadFile(m_childErrorRead, buffer, sizeof(buffer), &readBytes, NULL) && readBytes > 0) {
            ret.append(buffer, readBytes);
        }

        //----- �ԋp
        return ret;
    }


    // �n���h���̃N���[�Y
    void MSVCMediation::HandleClose(void) {
        CloseHandle(m_childRead);
        CloseHandle(m_childWrite);
        CloseHandle(m_childErrorRead);
        CloseHandle(m_childErrorWrite);
    }
}
