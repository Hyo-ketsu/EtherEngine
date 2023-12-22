#include <EtherEngine/ProjectEditorData.h>
#include <Base/DirectoryNameDefine.h>
#include <Base/BaseDefines.h>
#include <Base/BaseUtility.h>
#include <Base/EditorException.h>
#include <EtherEngine/EditorDefine.h>


//----- ProjectEditorData ��`
namespace EtherEngine {
    // �R���X�g���N�^
    EditorData::EditorData(const PathClass& path) {
        //----- �t�@�C������ǂݍ���
        if (path.IsExists() == false) throw EditorException("Error! ProjectData NonFile!");
        if (path.HasExtension() && path.GetExtension() != FileDefine::Extended::PROJECT_DATA) throw EditorException("Error! Is File ProjectData File?");

        //----- �ǂݍ���
        Input(EtherEngine::Utility::RoadFileAll(path.Get()));
        m_path = path;
    }

    // �f�X�g���N�^
    EditorData::~EditorData(void) {
        std::ofstream ofs(m_path);
        
        ofs << Output();
    }


    // �O���o��
    Json EditorData::Output(void) {
        nlohmann::json json;

        json["ProjectEditorData"]["CurrentScene"] = m_currentScene;

        return json;
    }
    // �O������
    void EditorData::Input(const Json& input) {
        //----- �ϐ��錾
        nlohmann::json json;

        //----- �ǂݍ���
        try {
            json = Utility::RoadFileAll(input);
        }
        catch (...) {
            goto END;
        }

        //----- Json�ǂݍ���
        // �V�[���Ǎ�
        if (json.contains("ProjectEditorData") && json["ProjectEditorData"].contains("CurrentScene")) {
            m_currentScene = json["ProjectEditorData"]["CurrentScene"];
        }
        else {
            goto END;
        }

        //----- ����I��
        return;

        //----- �ǂݍ��߂Ȃ������E�������͍��ڂ����݂��Ȃ������ꍇ�̏���
        END: {
        }
    }
}
