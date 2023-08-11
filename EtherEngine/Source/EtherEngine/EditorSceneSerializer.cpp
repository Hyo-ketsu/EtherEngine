#include <EtherEngine/EditorSceneSerializer.h>
#include <Base/BaseDefines.h>
#include <Base/GameObjectStorage.h>


//----- EditorSceneSerialize 定義
namespace EtherEngine {
    // 現在のシーン状態を出力する関数
    void EditorSceneSerialize(const PathClass& path, const SceneData& sceneData) {
        //----- 変数宣言
        nlohmann::json json;
        std::ofstream scene;

        //----- 常に新規作成する
        (path /= sceneData).GetDirectory().CreateDirectories();
        scene.open(path /= std::string(sceneData) += FileDefine::SCENE, std::ios::out);

        //----- シーン情報出力
        json["SceneName"] = sceneData.c_str();

        //----- ゲームオブジェクト取得・シーン別振り分け
        auto gameObjects = GameObjectStorage::Get()->GetGameObjectAll();
        decltype(gameObjects) sceneObject;
        for (auto& it : gameObjects) {
            if (it.GetNoAtomicData().GetScene() == sceneData) {
                sceneObject.push_back(it);
            }
        }

        //----- ゲームオブジェクト出力
        nlohmann::json gameObjectArray;
        for (auto& it : sceneObject) {
            gameObjectArray.push_back(it.GetAtomicData().Output());
        }
        auto fuga = gameObjectArray.dump(4);
        json["GameObjects"] = gameObjectArray;
        auto hoge = json.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES);
        scene << hoge;
    }
}
