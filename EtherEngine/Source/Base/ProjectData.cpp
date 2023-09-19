#include <Base/ProjectData.h>
#include <Base/BaseDefines.h>


//----- ProjectData 定義
namespace EtherEngine {
    // コンストラクタ
    // @ MEMO : ひとまずテストできるように深谷PCのパスを打っています
    ProjectData::ProjectData(const PathClass& path) {
        //----- ファイルから読み込み
        if (path.IsExists() == false) throw std::exception("Error! ProjectData NonFile!");
        if (path.HasExtension() && path.GetExtension() != FileDefine::Extended::PROJECT_DATA) throw std::exception("Error! Is File ProjectData File?");

        //----- 読み込み
        Input(EtherEngine::RoadFileAll(path.Get()));
    }


    // 出力する
    Json ProjectData::Output(void) {
        Json json;

        json["ProjectData"]["cmdPath"] = m_cmdPath;
        json["ProjectData"]["msvcPath"] = m_msvcPath;
        json["ProjectData"]["visualStudioPath"] = m_visualStudioPath;

        return json;
    }
    // 入力する
    void ProjectData::Input(const Json& input) {
        auto& projectData = input["ProjectData"];

        m_cmdPath.Access() = projectData["cmdPath"];
        m_msvcPath.Access() = projectData["msvcPath"];
        m_visualStudioPath.Access() = projectData["visualStudioPath"];
    }
}
