#include <Base/ProjectData.h>
#include <Base/BaseDefines.h>


//----- ProjectData ��`
namespace EtherEngine {
    // �R���X�g���N�^
    // @ MEMO : �ЂƂ܂��e�X�g�ł���悤�ɐ[�JPC�̃p�X��ł��Ă��܂�
    ProjectData::ProjectData(const PathClass& path) {
        //----- �t�@�C������ǂݍ���
        if (path.IsExists() == false) throw std::exception("Error! ProjectData NonFile!");
        if (path.HasExtension() && path.GetExtension() != FileDefine::Extended::PROJECT_DATA) throw std::exception("Error! Is File ProjectData File?");

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
