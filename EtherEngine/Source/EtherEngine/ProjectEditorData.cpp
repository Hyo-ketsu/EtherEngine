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
    Json ProjectEditorData::Output(void) {
        nlohmann::json json;

        json["ProjectEditorData"]["CurrentScene"] = m_currentScene;

        return json;
    }
    // �O������
    void ProjectEditorData::Input(const Json& input) {
        //----- �ϐ��錾
        nlohmann::json json;

        //----- �ǂݍ���
        try {
            json = RoadFileAll(input);
        }
        catch (...) {
            goto END;
        }

        //----- Json�ǂݍ���
        // �V�[���Ǎ�
        if (json.contains("ProjectEditorData") && json["ProjectEditorData"].contains("CurrentScene")) {
            m_currentScene = json["ProjectEditorData"]["CurrentScene"];
            SceneLoader::Get()->MoveScene(m_currentScene);
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
            SceneLoader::Get()->RegistryScene(m_currentScene);
        }
    }
}
