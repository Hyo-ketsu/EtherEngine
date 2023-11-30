#include <EtherEngine/CommandPrompt.h>
#include <Base/EditorException.h> 


//----- �萔��`
namespace EtherEngine {
    const int READ_COMMAND_SIZE = 256;
}




//----- CommandPrompt ��`
namespace EtherEngine {
    // �R���X�g���N�^
    CommandPrompt::CommandPrompt(const bool isShowPrompt) {
        //----- �ϐ��錾�Ə�����
        STARTUPINFO startupInfo;
        ZeroMemory(&startupInfo, sizeof(startupInfo));
        ZeroMemory(&m_processInfo, sizeof(m_processInfo));

        //----- �p�C�v�쐬
        SECURITY_ATTRIBUTES saAttr;
        ZeroMemory(&saAttr, sizeof(saAttr));
        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle = TRUE;
        saAttr.lpSecurityDescriptor = NULL;
        if (!CreatePipe(&m_childRead, &m_childWrite, &saAttr, 0) ||
            !CreatePipe(&m_read, &m_write, &saAttr, 0)) {
            //----- �p�C�v���쐬�ł��Ȃ������B��O���o
            throw EditorException("Error!");
        }

        //----- �v���Z�X�̗����グ�ݒ�
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

        //----- ���̓R�}���h�p�ϐ��錾
        char pram[64] = "cmd.exe";

        //----- �R�}���h�v�����v�g�����グ
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
            //----- �����グ���ł��Ȃ������B��O���o
            HandleClose();
            throw EditorException("Error!");
        }
    }
    // �f�X�g���N�^
    CommandPrompt::~CommandPrompt(void) {
        HandleClose();

        WaitForSingleObject(m_processInfo.hProcess, INFINITE);

        CloseHandle(m_processInfo.hProcess);
        CloseHandle(m_processInfo.hThread);
    }


    // �R�}���h����
    void CommandPrompt::Write(const std::string& command) {
        //----- �ϐ��錾
        DWORD bytesWritten; // �������݃o�C�g��

        //----- �p�C�v��������
        WriteFile(m_childWrite, command.c_str(), command.size(), &bytesWritten, NULL);
    }
    // �f�B���N�g���J��
    void CommandPrompt::CD(const std::string& dir) {
        //----- �f�B���N�g�����݃`�F�b�N
        PathClass path = PathClass(dir);
        if (path.IsDirectory() && path.IsExists()) {
            //----- �J�ڂł���B�J��
            this->Write(std::string("cd ") + dir);
        }
        else {
            //----- ���炩�ɑJ�ڂł��Ȃ��B��O���o
            throw EditorException("Error! Destination directory does not exist");
        }
    }
    // �R�}���h�v�����v�g�o�͎擾
    std::string CommandPrompt::Read(void) {
        //----- �ϐ��錾
        std::string ret;    // �ǂݍ��܂ꂽ������
        DWORD readBytes;    // �ǂݍ��܂ꂽ�o�C�g��
        char buffer[READ_COMMAND_SIZE] = {'\0'};  // �ǂݍ��݃o�b�t�@

        //----- �ǂݎ�肪�s���Ȃ��Ȃ�܂œǂݍ���
        while (PeekNamedPipe(m_read, buffer, 1, &readBytes, NULL, NULL) != FALSE && readBytes != 0) {   // �ǂݍ��݂��s����A����1�����ȏ�ł��ǂݍ��񂾂�
            //----- �ǂݎ��ƒǉ�
            if (ReadFile(m_read, buffer, sizeof(buffer), &readBytes, NULL) != FALSE) {
                ret.append(buffer, readBytes);
            }
        }

        //----- �ԋp
        return ret;
    }
    // �R�}���h�v�����v�g�G���[�o�͎擾
    std::string CommandPrompt::ReadError(void) {
        //----- �ϐ��錾
        std::string ret;    // �ǂݍ��܂ꂽ������
        DWORD readBytes;    // �ǂݍ��܂ꂽ�o�C�g��
        char buffer[READ_COMMAND_SIZE];   // �ǂݍ��݃o�b�t�@

        //----- �ǂݎ�肪�s���Ȃ��Ȃ�܂œǂݍ���
        while (PeekNamedPipe(m_childRead, buffer, 1, &readBytes, NULL, NULL) != FALSE && readBytes != 0) {   // �ǂݍ��݂��s����A����1�����ȏ�ł��ǂݍ��񂾂�
            //----- �ǂݎ��ƒǉ�
            if (ReadFile(m_childRead, buffer, sizeof(buffer), &readBytes, NULL) != FALSE) {
                ret.append(buffer, readBytes);
            }
        }

        //----- �ԋp
        return ret;
    }


    // �n���h���̃N���[�Y
    void CommandPrompt::HandleClose(void) {
        if (!CloseHandle(m_read)) throw EditorException("Error! Pipe close");
        if (!CloseHandle(m_write)) throw EditorException("Error! Pipe close");
        if (!CloseHandle(m_childRead)) throw EditorException("Error! Pipe close");
        if (!CloseHandle(m_childWrite)) throw EditorException("Error! Pipe close");
        //if (!CloseHandle(m_childErrorRead)) throw EditorException("Error! Pipe close");    // @ MEMO : ��O��f���̂ł�������R�����g�A�E�g
        //if (!CloseHandle(m_childErrorWrite)) throw EditorException("Error! Pipe close");
    }
}
