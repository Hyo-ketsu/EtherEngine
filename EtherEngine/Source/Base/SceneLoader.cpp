#include <Base/SceneLoader.h>
#include <Base/BaseDefines.h>   
#include <Base/DirectoryNameDefine.h>
#include <Base/GameObjectUpdater.h>
#include <Base/GameObjectStorage.h>
#include <Base/EtherEngineUtility.h>


namespace EtherEngine {
    // コンストラクタ
    SceneLoader::SceneLoader(void) {
    }
    // デストラクタ
    SceneLoader::~SceneLoader(void) {
    }


    // シーン情報登録
    void SceneLoader::RegistryScene(const SceneData data, const bool isSubScene) {
        //----- シーン情報追加
        m_sceneData.push_back(data);

        //----- 現在シーン設定
        if (isSubScene == false) m_currentSceneData = data;
    }


    // シーン追加
    void SceneLoader::AddScene(const SceneData data, const bool isSubScene) {
        //----- 読み込みディレクトリ修飾
        // @ Memo : Hoge -> Scene/Hoge.sceneData
        std::string loadSceneName;
        if (data.rfind(FileDefine::SCENE) == std::string::npos) {
            loadSceneName = data + FileDefine::SCENE;
        }
        else {
            loadSceneName = data;
        }

        //----- 生成
        auto hoge = RoadFileAll(loadSceneName);
        nlohmann::json json = nlohmann::json::parse(hoge);
        for (auto& it : json["GameObjects"]) {
            auto gameObject = GameObjectStorage::Get()->CreateGameObject();
            gameObject.GetNoAtomicData().Input(it);
        }

        //----- 現在シーン設定
        if (isSubScene == false) m_currentSceneData = data;
    }
    // シーン削除
    void SceneLoader::DeleteScene(const SceneData data) {
        //----- 削除シーンのみ保持シーン情報から削除
        bool isDelete = false;
        for (auto it = m_sceneData.begin(); it != m_sceneData.end(); it++) {
            if (*it == data) {
                //----- 削除
                m_sceneData.erase(it);
                isDelete = true;
                break;
            }
        }

        //----- 現在保持シーンに入力シーンが存在する(= 上で削除されている)か
        if (isDelete == false) return;

        //----- 現在シーン削除
        if (m_currentSceneData == data) m_currentSceneData.reset();

        //----- ゲームオブジェクト削除
        for (auto&& it : GameObjectStorage::Get()->GetGameObjectAll()) {
            if (it.GetNoAtomicData().GetScene() == data) {
                GameObjectStorage::Get()->DeleteGameObject(it);
            }
        }
    }
    // シーン削除
    void SceneLoader::DeleteScene(void) {
        //----- シーン完全消去
        m_sceneData.clear();

        //----- 現在シーン削除
        m_currentSceneData.reset();

        //----- 全ゲームオブジェクト削除
        for (auto&& it : GameObjectStorage::Get()->GetGameObjectAll()) {
            GameObjectStorage::Get()->DeleteGameObject(it);
        }
    }
    // シーン移動
    void SceneLoader::MoveScene(const SceneData data) {
        DeleteScene();
        AddScene(data);
    }
}
