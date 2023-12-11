#include <Base/SceneLoader.h>
#include <Base/BaseDefines.h>   
#include <Base/DirectoryNameDefine.h>
#include <Base/GameObjectUpdater.h>
#include <Base/GameObjectStorage.h>
#include <Base/BaseUtility.h>


namespace EtherEngine {
    // �R���X�g���N�^
    SceneLoader::SceneLoader(void) {
    }
    // �f�X�g���N�^
    SceneLoader::~SceneLoader(void) {
    }


    // �V�[�����o�^
    void SceneLoader::RegistryScene(const SceneData data, const bool isSubScene) {
        //----- �V�[�����ǉ�
        m_sceneData.push_back(data);

        //----- ���݃V�[���ݒ�
        if (isSubScene == false) m_currentSceneData = data;
    }


    // �V�[���ǉ�
    void SceneLoader::AddScene(const SceneData data, const bool isSubScene) {
        //----- �ǂݍ��݃f�B���N�g���C��
        // @ Memo : Hoge -> Scene/Hoge.sceneData
        std::string loadSceneName;
        if (data.rfind(FileDefine::Extended::SCENE) == std::string::npos) {
            loadSceneName = data + FileDefine::Extended::SCENE;
        }
        else {
            loadSceneName = data;
        }

        //----- ����
        nlohmann::json json = nlohmann::json::parse(Utility::RoadFileAll(loadSceneName));
        for (auto& it : json["GameObjects"]) {
            auto gameObject = GameObjectStorage::Get()->CreateGameObject();
            gameObject.GetData().Input(it);
        }

        //----- ���݃V�[���ݒ�
        if (isSubScene == false) m_currentSceneData = data;
    }
    // �V�[���폜
    void SceneLoader::DeleteScene(const SceneData data) {
        //----- �폜�V�[���̂ݕێ��V�[����񂩂�폜
        bool isDelete = false;
        for (auto it = m_sceneData.begin(); it != m_sceneData.end(); it++) {
            if (*it == data) {
                //----- �폜
                m_sceneData.erase(it);
                isDelete = true;
                break;
            }
        }

        //----- ���ݕێ��V�[���ɓ��̓V�[�������݂���(= ��ō폜����Ă���)��
        if (isDelete == false) return;

        //----- ���݃V�[���폜
        if (m_currentSceneData == data) m_currentSceneData.reset();

        //----- �Q�[���I�u�W�F�N�g�폜
        for (auto&& it : GameObjectStorage::Get()->GetGameObjectAll()) {
            if (it.GetData().GetScene() == data) {
                GameObjectStorage::Get()->DeleteGameObject(it);
            }
        }
    }
    // �V�[���폜
    void SceneLoader::DeleteScene(void) {
        //----- �V�[�����S����
        m_sceneData.clear();

        //----- ���݃V�[���폜
        m_currentSceneData.reset();

        //----- �S�Q�[���I�u�W�F�N�g�폜
        for (auto&& it : GameObjectStorage::Get()->GetGameObjectAll()) {
            GameObjectStorage::Get()->DeleteGameObject(it);
        }
    }
    // �V�[���ړ�
    void SceneLoader::MoveScene(const SceneData data) {
        DeleteScene();
        AddScene(data);
    }
}
