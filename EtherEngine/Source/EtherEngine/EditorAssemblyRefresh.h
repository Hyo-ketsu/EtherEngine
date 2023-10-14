#ifndef I_EDITORASSEMBLYREFRESH_H
#define I_EDITORASSEMBLYREFRESH_H


//----- �A�Z���u���̃��t���b�V���֐�
namespace EtherEngine {
    namespace Refresh {
        // �G���[���e
        enum class RefreshStateType {
            Ok = 0,   // ���Ȃ�
            CurrentlyRefresh,       // ���݃��t���b�V����
            NoneLoadProject,        // �v���W�F�N�g���ǂݍ��܂�Ă��Ȃ�
            NoneMSVCMediationInit,  // MSVCMediation������������Ă��Ȃ�
            InputCommandFailed,     // �R�}���h���͂����s����
            CompileError,           // �r���h�̍ۃR���p�C���G���[���o�͂��ꂽ
        };


        // ���t���b�V�����s��
        // @ Ret  : ���t���b�V����
        RefreshStateType AssemblyRefresh(void);
    }
}


#endif // !I_EDITORASSEMBLYREFRESH_H
