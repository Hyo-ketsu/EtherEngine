#include <EtherEngine/EditorAssemblyRefresh.h>
#include <EtherEngine/ProjectMediation.h>
#include <EtherEngine/MSVCMediation.h>
#include <EtherEngine/EditorProgressBar.h>


//----- �A�Z���u���̃��t���b�V���֐�
namespace EtherEngine {
    namespace Refresh {
        // ���t���b�V�����s��
        // @ MEMO : �b��I�����B�v���O���X�o�[�Ȃǂ̕\�����s��Ȃ�
        RefreshError AssemblyRefresh(void) {
        //----- �ÓI�ϐ��錾
        static std::shared_ptr<ProgressClass> s_progress;

        //----- ���Ƀ��t���b�V�����s���Ă��邩
        if (s_progress != nullptr && s_progress->IsEnd() == false) {
            return RefreshError::CurrentlyRefresh;
        }

        //----- ���t���b�V���͍s���Ă��Ȃ��B�V�������t���b�V��

        //----- �܂��v���W�F�N�g�����ɓǂݍ��݂ł��邩(�K�[�h��
        if (ProjectMediation::Get()->GetVcxproj().Get() == "") return RefreshError::NoneLoadProject;

        //----- �r���h
        try {
            MSVCMediation::Get()->WriteCmd(std::string("msbuild ") + ProjectMediation::Get()->GetSln().Get());
        }
        catch (...) {
            return RefreshError::InputCommandFailed;
        }

        //----- �v���O���X�o�[�o��

        }
    } 
}
