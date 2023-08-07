#include <Base/SceneLoader.h>
#include <Base/BaseDefines.h>   
#include <Base/DirectoryNameDefine.h>
#include <Base/GameObjectUpdater.h>
#include <Base/GameObjectStorage.h>


namespace EtherEngine {
    // コンストラクタ
    SceneLoader::SceneLoader(void) {
    }
    // デストラクタ
    SceneLoader::~SceneLoader(void) {
    }


    // シーン追加
    void SceneLoader::AddScene(const SceneData data) {
        //----- 読み込みディレクトリ修飾
        // @ Memo : Hoge -> Scene/Hoge.sceneData
        std::string loadSceneName;
        if (data.rfind(FilenameExtensionDefine::SCENE) == std::string::npos) {
            loadSceneName = DirectoryDefine::SCENE_DATA + data + FilenameExtensionDefine::SCENE;
        }
        else {
            loadSceneName = DirectoryDefine::SCENE_DATA + data;
        }

        //----- ファイルオープン
        std::ifstream scene(loadSceneName);
        if (scene.is_open() == false) throw std::exception((std::string("Exception! SceneData : ") + loadSceneName + " Non file!").c_str());

        //----- 読み込み
        // @ Memo : EOFまで全て読み込みます
        std::string sceneString;
        std::string line;
        while (std::getline(scene, line)) {
            sceneString += line;
        }

        //----- 生成
        nlohmann::json json = nlohmann::json::parse(sceneString);
        for (auto& it : json["GameObejcts"]) {
            auto gameObject = GameObjectStorage::Get()->CreateGameObject();
            gameObject.GetNoAtomicData().Input(it);
        }
    }
    // シーン削除
    void SceneLoader::DeleteScene(const SceneData data) {

    }
    // シーン削除
    void SceneLoader::DeleteScene(void) {

    }
    // シーン移動
    void SceneLoader::MoveScene(const SceneData data) {

    }
}
