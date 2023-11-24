#ifndef I_EDITOREXCEPTION_H
#define I_EDITOREXCEPTION_H
#include <Base/ConceptUtility.h>


//----- EditorException �錾
namespace EtherEngine {
    // ���̃G���W���ł̗�O�N���X
    class EditorException {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �\��������(Default : "")
        // @ Arg2 : �X�^�b�N�g���[�X(Default : nullptr)
        // @ Arg3 : ��O������(Default : ��O������(Default����))
        EditorException(const std::string in = "", const EditorException* const exception = nullptr, std::source_location source = std::source_location::current()) noexcept;
        // �f�X�g���N�^
        ~EditorException(void);


        // �C���f�b�N�X�t���ŗ�O���b�Z�[�W���擾����
        // @ Ret  : �擾������O���b�Z�[�W
        // @ Arg1 : �C���f�b�N�X(0�Ŏ��g�̃��b�Z�[�W�擾)
        std::optional<std::string> GetErrorMessage(uint index) const noexcept;
        // ���g�̗�O���b�Z�[�W���擾����
        // @ Ret  : �擾������O���b�Z�[�W
        std::string GetErrorMessage(void) const noexcept;

    private:
        std::vector<EditorException> m_exceptions;  // �X�^�b�N�g���[�X
        std::string m_errorMessage;     // ���g���ێ����Ă����O
    };
}


#endif // !I_EDITOREXCEPTION_H
