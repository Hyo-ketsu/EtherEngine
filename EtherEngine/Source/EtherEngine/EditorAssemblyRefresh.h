#ifndef I_EDITORASSEMBLYREFRESH_H
#define I_EDITORASSEMBLYREFRESH_H


//----- �A�Z���u���̃��t���b�V���֐�
namespace EtherEngine {
    // �G���[���e
    enum class RefreshError {
        Ok = 0,   // ���Ȃ�
        NoneLoadProject,        // �v���W�F�N�g���ǂݍ��܂�Ă��Ȃ�
        NoneMSVCMediationInit,  // MSVCMediation������������Ă��Ȃ�
        InputCommandFailed,     // �R�}���h���͂����s����
        CompileError,           // �r���h�̍ۃR���p�C���G���[���o�͂��ꂽ
    };


    // ���t���b�V�����s��
    // @ Ret  : ���t���b�V����
    RefreshError AssemblyRefresh(void);
}


#endif // !I_EDITORASSEMBLYREFRESH_H
