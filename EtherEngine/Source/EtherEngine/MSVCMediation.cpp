#include <EtherEngine/MSVCMediation.h>


//----- �萔��`
namespace EtherEngine {
    const int READ_COMMAND_SIZE = 256;
}




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

        //----- �p�C�v�쐬
        SECURITY_ATTRIBUTES saAttr;
        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle = TRUE;
        saAttr.lpSecurityDescriptor = NULL;
        if (!CreatePipe(&m_childRead, &m_childWrite, &saAttr, 0) ||
            !CreatePipe(&m_read, &m_write, &saAttr, 0)) {
            //----- �p�C�v���쐬�ł��Ȃ������B��O���o
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
        if (!WriteFile(m_childWrite, inputCommand, strlen(inputCommand), &bytesWritten, NULL)) {
            //----- �������߂Ȃ��B��O���o
            HandleClose();
            throw std::exception("Error! Non write pipe");
        }
    }
    // �R�}���h�v�����v�g�o�͎擾
    std::string MSVCMediation::ReadCmd(void) {
        //----- �ϐ��錾
        std::string ret;    // �ǂݍ��܂ꂽ������
        DWORD readBytes;    // �ǂݍ��܂ꂽ�o�C�g��
        char buffer[READ_COMMAND_SIZE] = {'\0'};  // �ǂݍ��݃o�b�t�@

        //----- �ǂݎ�肪�s���Ȃ��Ȃ�܂œǂݍ���
        while (PeekNamedPipe(m_read, NULL, NULL, NULL, NULL, NULL) != 0) {
            //----- �ǂݎ��ƒǉ�
            ReadFile(m_read, buffer, sizeof(buffer), &readBytes, NULL);
            ret.append(buffer, readBytes);

            //----- ����ȏ�ǂݎ��Ȃ��Ȃ狭���I�ɏI������
            if (readBytes != READ_COMMAND_SIZE) break;
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
        if (ReadFile(m_childErrorRead, buffer, sizeof(buffer), &readBytes, NULL) && readBytes > 0) {
            ret.append(buffer, readBytes);
        }

        //----- �ԋp
        return ret;
    }


    // �n���h���̃N���[�Y
    void MSVCMediation::HandleClose(void) {
        if (!CloseHandle(m_read)) throw std::exception("Error! Pipe close");
        if (!CloseHandle(m_write)) throw std::exception("Error! Pipe close");
        if (!CloseHandle(m_childRead)) throw std::exception("Error! Pipe close");
        if (!CloseHandle(m_childWrite)) throw std::exception("Error! Pipe close");
        if (!CloseHandle(m_childErrorRead)) throw std::exception("Error! Pipe close");
        if (!CloseHandle(m_childErrorWrite)) throw std::exception("Error! Pipe close");
    }
}
