#include <EtherEngine/EditorAssemblyRefresh.h>
#include <EtherEngine/ProjectMediation.h>
#include <EtherEngine/MSVCMediation.h>


//----- �A�Z���u���̃��t���b�V���֐�
namespace EtherEngine {
    // ���t���b�V�����s��
    RefreshError AssemblyRefresh(void) {
        //----- �܂��v���W�F�N�g�����ɓǂݍ��݂ł��邩(�K�[�h��
        if (ProjectMediation::Get()->GetVcxproj().Get() == "") return RefreshError::NoneLoadProject;

        //----- �r���h
        try {
            if (MSVCMediation::Get()->Command(std::string("msbuild ") + ProjectMediation::Get()->GetSln().Get())) {
                return RefreshError::InputCommandFailed;
            }
        }
        catch(...) {
            return RefreshError::NoneMSVCMediationInit;
        }

        //----- �v���O���X�o�[�o��

    }
}
