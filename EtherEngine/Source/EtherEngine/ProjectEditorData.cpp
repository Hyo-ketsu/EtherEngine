#include <EtherEngine/ProjectEditorData.h>
#include <Base/DirectoryNameDefine.h>
#include <Base/BaseDefines.h>
#include <Base/SceneLoader.h>
#include <Base/EtherEngineUtility.h>
#include <EtherEngine/EditorDefine.h>


//----- ProjectEditorData ��`
namespace EtherEngine {
    // �R���X�g���N�^
    ProjectEditorData::ProjectEditorData(const PathClass& path) {
        Input(path);
    }


    // �O���o��
    std::string ProjectEditorData::Output(void) {
        nlohmann::json json;

        if (m_currentScene.has_value()) json["ProjectEditorData"]["CurrentScene"] = m_currentScene.value();

        return json.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES);
    }
    // �O������
    void ProjectEditorData::Input(const std::string& input) {
        //----- �ϐ��錾
        nlohmann::json json;

        //----- �ǂݍ���
        try {
            json = nlohmann::json::parse(RoadFileAll(input));
        }
        catch (...) {
            goto END;
        }

        //----- Json�ǂݍ���
        // �V�[���Ǎ�
        if (json.contains("ProjectEditorData") && json["ProjectEditorData"].contains("CurrentScene")) {
            m_currentScene.value() = json["ProjectEditorData"]["CurrentScene"];
            SceneLoader::Get()->MoveScene(m_currentScene.value());
        }
        else {
            goto END;
        }

        //----- ����I��
        return;

        //----- �ǂݍ��߂Ȃ������E�������͍��ڂ����݂��Ȃ������ꍇ�̏���
        END: {
            //----- ���݂��Ȃ����߃f�t�H���g�V�[�����쐬�A�o�^
            m_currentScene = SceneData(DirectoryDefine::SCENE_DATA + '\\' + EditorDefine::EDITOR_DEFAULT_SCENE_NAME);
            SceneLoader::Get()->RegistryScene(m_currentScene.value());
        }
    }
}
