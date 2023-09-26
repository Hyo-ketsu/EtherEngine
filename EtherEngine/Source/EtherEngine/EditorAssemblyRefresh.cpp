#include <EtherEngine/EditorAssemblyRefresh.h>
#include <EtherEngine/ProjectMediation.h>
#include <EtherEngine/MSVCMediation.h>


//----- アセンブリのリフレッシュ関数
namespace EtherEngine {
    // リフレッシュを行う
    RefreshError AssemblyRefresh(void) {
        //----- まずプロジェクトが既に読み込みできるか(ガード節
        if (ProjectMediation::Get()->GetVcxproj().Get() == "") return RefreshError::NoneLoadProject;

        //----- ビルド
        try {
            if (MSVCMediation::Get()->Command(std::string("msbuild ") + ProjectMediation::Get()->GetSln().Get())) {
                return RefreshError::InputCommandFailed;
            }
        }
        catch(...) {
            return RefreshError::NoneMSVCMediationInit;
        }

        //----- プログレスバー出力

    }
}
