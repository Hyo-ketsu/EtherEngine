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
        m_path = path;
    }
    // �f�X�g���N�^
    ProjectData::~ProjectData(void) {
        std::ofstream ofs(m_path);

        ofs << Output();
    }


    // �o�͂���
    Json ProjectData::Output(void) {
        Json json;

        json["ProjectData"]["visualStudioPath"] = m_msbuildPath;

        return json;
    }
    // ���͂���
    void ProjectData::Input(const Json& input) {
        auto& projectData = input["ProjectData"];

        m_msbuildPath.Access() = projectData["visualStudioPath"];
    }
}
