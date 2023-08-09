#include <EtherEngine/ProjectEditorData.h>
#include <Base/DirectoryNameDefine.h>
#include <Base/SceneLoader.h>
#include <EtherEngine/EditorDefine.h>


//----- ProjectEditorData ��`
namespace EtherEngine {
    // �R���X�g���N�^
    ProjectEditorData::ProjectEditorData(const PathClass& path) {

    }


    // �O���o��
    std::string ProjectEditorData::Output(void) {
        nlohmann::json json;

        if (m_currentScene.has_value()) json["ProjectEditorData"]["CurrentScene"] = m_currentScene.value();

        return json.dump(msc_dump);
    }
    // �O������
    void ProjectEditorData::Input(const std::string& input) {
        nlohmann::json json = nlohmann::json::parse(input);

        //----- Json�ǂݍ���
        // �V�[���Ǎ�
        if (json.contains("ProjectEditorData") && json["ProjectEditorData"].contains("CurrentScene")) {
            m_currentScene.value() = json["ProjectEditorData"]["CurrentScene"];
            SceneLoader::Get()->MoveScene(m_currentScene.value());
        }
        else {
            //----- ���݂��Ȃ����߃f�t�H���g�V�[�����쐬
            m_currentScene.value() = SceneData(DirectoryDefine::SCENE_DATA + EditorDefine::EDITOR_DEFAULT_SCENE_NAME);
        }
    }
}
