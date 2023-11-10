#ifndef I_MSVCMEDIATION_H
#define I_MSVCMEDIATION_H
#include <Base/Singleton.h>
#include <Base/PathClass.h>


//----- MSVCMediation ��`
namespace EtherEngine {
    class MSVCMediation : public Singleton<MSVCMediation> {
    public:
        // �f�X�g���N�^
        ~MSVCMediation(void) {}

        // ����������
        // @ Arg1 : �R�}���h�v�����v�g�p�X
        // @ Arg2 : MSVC�p�X
        void Init(const PathClass& cmdPath, const PathClass& msvcPath);
        // �I������
        void Uninit(void);


        // �R�}���h����
        // @ Arg1 : ���̓R�}���h
        void WriteCmd(const std::string& commnad);
        // �R�}���h�v�����v�g�o�͎擾
        // @ Memo : ���̊֐��͑҂��Ȃǂ͈�؍s���܂���B
        // @ Ret  : �擾����
        std::string ReadCmd(void);
        // �R�}���h�v�����v�g�G���[�o�͎擾
        // @ Memo : ���̊֐��͑҂��Ȃǂ͈�؍s���܂���B
        // @ Ret  : �擾����
        std::string ReadCmdError(void);

    private:
        // �R���X�g���N�^
        MSVCMediation(void);


        // �n���h���̃N���[�Y
        void HandleClose(void);

        friend class Singleton<MSVCMediation>;

        PROCESS_INFORMATION m_processInfo;
        bool m_isInit;  // ����������Ă��邩
        HANDLE m_childRead;   // cmd�p�ǂݎ��p�p�C�v
        HANDLE m_childWrite;  // cmd�p�������ݗp�p�C�v
        HANDLE m_read;        // �ǂݎ��p�p�C�v
        HANDLE m_write;       // �������ݗp�p�C�v
        HANDLE m_childErrorRead;   // �G���[�ǂݎ��p�p�C�v
        HANDLE m_childErrorWrite;  // �G���[�������ݗp�p�C�v
    };
}


#endif // !I_MSVCMEDIATION_H
