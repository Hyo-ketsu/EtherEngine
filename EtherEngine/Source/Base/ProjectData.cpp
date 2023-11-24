#include <Base/ProjectData.h>
#include <Base/BaseDefines.h>
#include <Base/EditorException.h>


//----- ProjectData ��`
namespace EtherEngine {
    // �R���X�g���N�^
    ProjectData::ProjectData(const PathClass& path) {
        //----- �t�@�C������ǂݍ���
        if (path.IsExists() == false) throw EditorException("Error! ProjectData NonFile!");
        if (path.HasExtension() && path.GetExtension() != FileDefine::Extended::PROJECT_DATA) throw EditorException("Error! Is File ProjectData File?");

        //----- �ǂݍ���
        Input(EtherEngine::RoadFileAll(path.Get()));
    }


    // �o�͂���
    Json ProjectData::Output(void) {
        Json json;

        json["ProjectData"]["cmdPath"] = m_cmdPath;
        json["ProjectData"]["msvcPath"] = m_msvcPath;
        json["ProjectData"]["visualStudioPath"] = m_visualStudioPath;

        return json;
    }
    // ���͂���
    void ProjectData::Input(const Json& input) {
        auto& projectData = input["ProjectData"];

        m_cmdPath.Access() = projectData["cmdPath"];
        m_msvcPath.Access() = projectData["msvcPath"];
        m_visualStudioPath.Access() = projectData["visualStudioPath"];
    }
}
