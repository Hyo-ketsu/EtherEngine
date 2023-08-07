#include <Base/SceneLoader.h>
#include <Base/BaseDefines.h>   
#include <Base/DirectoryNameDefine.h>
#include <Base/GameObjectUpdater.h>
#include <Base/GameObjectStorage.h>


namespace EtherEngine {
    // �R���X�g���N�^
    SceneLoader::SceneLoader(void) {
    }
    // �f�X�g���N�^
    SceneLoader::~SceneLoader(void) {
    }


    // �V�[���ǉ�
    void SceneLoader::AddScene(const SceneData data) {
        //----- �ǂݍ��݃f�B���N�g���C��
        // @ Memo : Hoge -> Scene/Hoge.sceneData
        std::string loadSceneName;
        if (data.rfind(FilenameExtensionDefine::SCENE) == std::string::npos) {
            loadSceneName = DirectoryDefine::SCENE_DATA + data + FilenameExtensionDefine::SCENE;
        }
        else {
            loadSceneName = DirectoryDefine::SCENE_DATA + data;
        }

        //----- �t�@�C���I�[�v��
        std::ifstream scene(loadSceneName);
        if (scene.is_open() == false) throw std::exception((std::string("Exception! SceneData : ") + loadSceneName + " Non file!").c_str());

        //----- �ǂݍ���
        // @ Memo : EOF�܂őS�ēǂݍ��݂܂�
        std::string sceneString;
        std::string line;
        while (std::getline(scene, line)) {
            sceneString += line;
        }

        //----- ����
        nlohmann::json json = nlohmann::json::parse(sceneString);
        for (auto& it : json["GameObejcts"]) {
            auto gameObject = GameObjectStorage::Get()->CreateGameObject();
            gameObject.GetNoAtomicData().Input(it);
        }
    }
    // �V�[���폜
    void SceneLoader::DeleteScene(const SceneData data) {

    }
    // �V�[���폜
    void SceneLoader::DeleteScene(void) {

    }
    // �V�[���ړ�
    void SceneLoader::MoveScene(const SceneData data) {

    }
}
