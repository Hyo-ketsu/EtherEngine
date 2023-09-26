#include <EtherEngine/EditorAssemblyRefresh.h>
#include <EtherEngine/ProjectMediation.h>
#include <EtherEngine/MSVCMediation.h>
#include <EtherEngine/EditorProgressBar.h>


//----- アセンブリのリフレッシュ関数
namespace EtherEngine {
    namespace Refresh {
        // リフレッシュを行う
        // @ MEMO : 暫定的処理。プログレスバーなどの表示を行わない
        RefreshError AssemblyRefresh(void) {
        //----- 静的変数宣言
        static std::shared_ptr<ProgressClass> s_progress;

        //----- 既にリフレッシュを行っているか
        if (s_progress != nullptr && s_progress->IsEnd() == false) {
            return RefreshError::CurrentlyRefresh;
        }

        //----- リフレッシュは行われていない。新しくリフレッシュ

        //----- まずプロジェクトが既に読み込みできるか(ガード節
        if (ProjectMediation::Get()->GetVcxproj().Get() == "") return RefreshError::NoneLoadProject;

        //----- ビルド
        try {
            MSVCMediation::Get()->WriteCmd(std::string("msbuild ") + ProjectMediation::Get()->GetSln().Get());
        }
        catch (...) {
            return RefreshError::InputCommandFailed;
        }

        //----- プログレスバー出力

        }
    } 
}
