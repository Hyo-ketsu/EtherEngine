#include <Base/ProjectData.h>


//----- ProjectData 定義
namespace EtherEngine {
    // コンストラクタ
    // @ MEMO : ひとまずテストできるように深谷PCのパスを打っています
    ProjectData::ProjectData(const PathClass& path) 
        : m_cmdPath("C:\\Windows\\System32\\cmd.exe") 
        , m_msvcPath("/k \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat\"") 
        , m_visualStudioPath("C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\devenv.com") {
    }
}
