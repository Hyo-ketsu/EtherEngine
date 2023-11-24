#include <Base/ProjectData.h>
#include <Base/BaseDefines.h>
#include <Base/EditorException.h>


//----- ProjectData 定義
namespace EtherEngine {
    // コンストラクタ
    ProjectData::ProjectData(const PathClass& path) {
        //----- ファイルから読み込み
        if (path.IsExists() == false) throw EditorException("Error! ProjectData NonFile!");
        if (path.HasExtension() && path.GetExtension() != FileDefine::Extended::PROJECT_DATA) throw EditorException("Error! Is File ProjectData File?");

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
