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
        // @ Ret  : �R�}���h���͂�����������
        // @ Arg1 : �R�}���h����
        bool Command(const std::string& commnad);


        // 


    private:
        // �R���X�g���N�^
        MSVCMediation(void);

        friend class Singleton<MSVCMediation>;

        std::string m_output;   // �O���o��
        std::string m_error;    // �G���[�o��
        PROCESS_INFORMATION m_processInfo;
        HANDLE m_childStdInRead;
        HANDLE m_childStdInWrite;
    };
}


#endif // !I_MSVCMEDIATION_H
