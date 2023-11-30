#ifndef I_MSVCMEDIATION_H
#define I_MSVCMEDIATION_H
#include <Base/Singleton.h>
#include <Base/PathClass.h>


//----- CommandPrompt ��`
namespace EtherEngine {
    // �R�}���h�v�����v�g�ł̓��o�͂𒇉��N���X
    class CommandPrompt {
    public:
        // �R���X�g���N�^
        // @ MEMO : �v�����v�g�\���ɂ͌��ݑΉ����Ă���܂���(�q�v���Z�X�̏o�̓p�C�v�͎�����܂܂Ȃ̂�)
        // @ Arg1 : �v�����v�g��\�����邩(Default : false)
        CommandPrompt(const bool isShowPrompt = false);
        // �f�X�g���N�^
        ~CommandPrompt(void);
        // �R�s�[�R���X�g���N�^
        CommandPrompt(const CommandPrompt& copy) = delete;
        // ���[�u�R���X�g���N�^
        CommandPrompt(CommandPrompt&& move) = delete;


        // �R�}���h����
        // @ Arg1 : ���̓R�}���h
        void Write(const std::string& commnad);
        // �f�B���N�g���J��
        // @ Exce : �J�ڂ��s������
        // @ Arg1 : �J�ڐ�f�B���N�g��
        void CD(const std::string& dir);
        // �R�}���h�v�����v�g�o�͎擾
        // @ Memo : ���̊֐��͑҂��Ȃǂ͈�؍s���܂���B
        // @ Ret  : �擾����
        std::string Read(void);
        // �R�}���h�v�����v�g�G���[�o�͎擾
        // @ Memo : ���̊֐��͑҂��Ȃǂ͈�؍s���܂���B
        // @ Ret  : �擾����
        std::string ReadError(void);

    private:
        // �n���h���̃N���[�Y
        void HandleClose(void);

        PROCESS_INFORMATION m_processInfo;
        HANDLE m_childRead;   // cmd�p�ǂݎ��p�p�C�v
        HANDLE m_childWrite;  // cmd�p�������ݗp�p�C�v
        HANDLE m_read;        // �ǂݎ��p�p�C�v
        HANDLE m_write;       // �������ݗp�p�C�v
        HANDLE m_childErrorRead;   // �G���[�ǂݎ��p�p�C�v
        HANDLE m_childErrorWrite;  // �G���[�������ݗp�p�C�v
    };
}


#endif // !I_MSVCMEDIATION_H
