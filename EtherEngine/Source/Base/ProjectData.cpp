#include <Base/ProjectData.h>


//----- ProjectData ��`
namespace EtherEngine {
    // �R���X�g���N�^
    // @ MEMO : �ЂƂ܂��e�X�g�ł���悤�ɐ[�JPC�̃p�X��ł��Ă��܂�
    ProjectData::ProjectData(const PathClass& path) 
        : m_cmdPath("C:\\Windows\\System32\\cmd.exe") 
        , m_msvcPath("/k \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat\"") 
        , m_visualStudioPath("C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\devenv.com") {
    }
}
