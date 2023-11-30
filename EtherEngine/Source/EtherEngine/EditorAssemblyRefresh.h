#ifndef I_EDITORASSEMBLYREFRESH_H
#define I_EDITORASSEMBLYREFRESH_H
#include <EtherEngine/EditorProgressBar.h>
#include <EtherEngine/CommandPrompt.h>


//----- �A�Z���u���̃��t���b�V���֐�
namespace EtherEngine {
    // ���t���b�V���N���X
    class Refresh {
    public:
        // �G���[���e
        enum class RefreshStateType {
            Ok = 0,   // ���Ȃ�
            StartRefresh,           // ���t���b�V���J�n
            CurrentlyRefresh,       // ���݃��t���b�V����
            NoneLoadProject,        // �v���W�F�N�g���ǂݍ��܂�Ă��Ȃ�
            NoneCommandPromptInit,  // CommandPrompt������������Ă��Ȃ�
            InputCommandFailed,     // �R�}���h���͂����s����
            CompileError,           // �r���h�̍ۃR���p�C���G���[���o�͂��ꂽ
        };


        // �r���h�󋵃Q�b�^�[
        static bool GetBuildEnd(void) { return ms_isBuildEnd; }
        // �r���h�����Q�b�^�[
        static bool GetBuildSuccess(void) { return ms_isBuildSuccess; }


        // ���t���b�V�����s��
        // @ Ret  : ���t���b�V����
        static RefreshStateType AssemblyRefresh(void);
        // ���݂̃��t���b�V���󋵂��擾����
        // @ Ret  : ���݂̃��t���b�V����
        static RefreshStateType GetRefreshState(void);
        // �r���h���O��ǂݎ��
        // @ Ret  : �r���h���O
        static std::string GetRefreshLog(void);
        
    private:
        static std::unique_ptr<CommandPrompt> ms_cmd;   // �ێ����Ă���R�}���h�v�����v�g
        static std::string ms_buildLog; // �r���h���O
        static bool ms_isBuildEnd;      // �r���h���I��������
        static bool ms_isBuildSuccess;  // �r���h������������
    };
}


#endif // !I_EDITORASSEMBLYREFRESH_H
