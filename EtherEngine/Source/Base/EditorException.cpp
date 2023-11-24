#include <Base/EditorException.h>


//----- EditorException ��`
namespace EtherEngine {
    // �R���X�g���N�^
    EditorException::EditorException(const std::string in, const EditorException* const exception, std::source_location source) noexcept {
        //----- ��O���b�Z�[�W�\�z
        std::string message = in + '\n';
        message += " Line : " + std::to_string(source.line()) + '\n';
        message += " File : " + std::string(source.file_name()) + '\n';
        message += " Function : " + std::string(source.function_name()) + '\n';

        //----- ��O�ǉ�
        m_errorMessage = message;

        //----- �O�X�^�b�N�̗�O��ǉ�
        if (exception == nullptr) return;
        m_exceptions.push_back(*exception);
        for (auto&& exception : exception->m_exceptions) {
            m_exceptions.push_back(exception);
        }
    }
    // �f�X�g���N�^
    EditorException::~EditorException(void) {
    }


    // �C���f�b�N�X�t���ŗ�O���b�Z�[�W���擾����
    std::optional<std::string> EditorException::GetErrorMessage(uint index) const noexcept {
        //----- 0�Ȃ玩�g�̃��b�Z�[�W��ԋp
        if (index == 0) return m_errorMessage;

        //----- 1�C���f�b�N�X��0�C���f�b�N�X�ɖ߂�
        index--;

        //----- �͈͊O�Q�Ƃ��s���Ă��Ȃ���
        if (index >= m_exceptions.size()) return std::optional<std::string>();

        //----- �͈͓��B�ԋp����
        return m_exceptions[index].GetErrorMessage();
    }
    // ���g�̗�O���b�Z�[�W���擾����
    std::string EditorException::GetErrorMessage(void) const noexcept {
        return m_errorMessage;
    }
}
