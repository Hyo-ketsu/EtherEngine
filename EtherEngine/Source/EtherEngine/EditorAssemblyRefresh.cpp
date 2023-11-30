#include <EtherEngine/EditorAssemblyRefresh.h>
#include <EtherEngine/ProjectMediation.h>
#include <EtherEngine/CommandPrompt.h>
#include <EtherEngine/EditorDefine.h>


//----- �A�Z���u���̃��t���b�V���֐�
namespace EtherEngine {
    // ���t���b�V�����s��
    // @ MEMO : �b��I�����B�v���O���X�o�[�Ȃǂ̕\�����s��Ȃ�
    Refresh::RefreshStateType Refresh::AssemblyRefresh(void) {
        //----- ���Ƀ��t���b�V�����s���Ă��邩
        if (ms_cmd != nullptr) {
            return RefreshStateType::CurrentlyRefresh;
        }

        //----- �܂��v���W�F�N�g�����ɓǂݍ��݂ł��邩(�K�[�h��
        if (ProjectMediation::Get()->GetVcxproj().Get() == "") return RefreshStateType::NoneLoadProject;
        
        //----- �r���h���s��
        try {
            ms_cmd = std::make_unique<CommandPrompt>();
            ms_cmd->CD(ProjectMediation::Get()->GetVcxproj());
            ms_cmd->Write(std::string("MSBuild.exe ") + ProjectMediation::Get()->GetSln().Get() + " && " +
                +"if %ERRORLEVEL%==0 (echo " + EditorDefine::EDITOR_BUILD_OK + ")" + " ELSE " + "echo " + EditorDefine::EDITOR_BUILD_ERROR + ")");
        }
        catch (...) {
            return RefreshStateType::InputCommandFailed;
        }

        //----- �v���O���X�o�[�o��

        //----- �r���h�J�n
        ms_isBuildEnd = false;
        ms_isBuildSuccess = false;
        return RefreshStateType::StartRefresh;
    }


    // ���݂̃��t���b�V���󋵂��擾����
    Refresh::RefreshStateType Refresh::GetRefreshState(void) {
        //----- ���O���擾����
        Refresh::GetRefreshLog();

        //----- ���t���b�V������
        if (ms_isBuildEnd == false) return RefreshStateType::CurrentlyRefresh;

        //----- ���t���b�V��������������
        if (ms_isBuildSuccess) {
            return RefreshStateType::Ok;
        }
        else {
            return RefreshStateType::CompileError;
        }
    }
    // �r���h���O��ǂݎ��
    std::string Refresh::GetRefreshLog(void) {
        //----- ���O�擾
        auto logText = ms_cmd->Read();

        //----- ����̃��b�Z�[�W���o�͂���Ă��邩
        if (logText.find(EditorDefine::EDITOR_BUILD_OK) != std::string::npos) {
            ms_isBuildEnd = true;
            ms_isBuildSuccess = true;
        }
        if (logText.find(EditorDefine::EDITOR_BUILD_ERROR) != std::string::npos) {
            ms_isBuildEnd = true;
            ms_isBuildSuccess = false;
        }

        //----- ���O��ǉ�
        ms_buildLog += logText;

        //----- �R�}���h�v�����v�g���폜
        if (ms_isBuildEnd) {
            ms_cmd.reset();
        }

        //----- ���O�̕ԋp
        return ms_buildLog;
    }


    std::unique_ptr<CommandPrompt> Refresh::ms_cmd;   // �ێ����Ă���R�}���h�v�����v�g
    std::string Refresh::ms_buildLog;        // �r���h���O
    bool Refresh::ms_isBuildEnd = true;      // �r���h���I��������
    bool Refresh::ms_isBuildSuccess = false; // �r���h������������
}
