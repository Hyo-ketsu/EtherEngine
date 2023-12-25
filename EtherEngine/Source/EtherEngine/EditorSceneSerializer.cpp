#include <EtherEngine/EditorSceneSerializer.h>
#include <Base/BaseDefines.h>
#include <Base/BaseUtility.h>
#include <Base/NativeGameObjectStorage.h>


//----- EditorSceneSerialize 定義
namespace EtherEngine {
    // 現在のシーン状態を出力する関数
    void EditorSceneSerialize(const PathClass& path, const SceneType& sceneData) {
        ////----- 変数宣言
        //nlohmann::json json;
        //std::ofstream scene;

        ////----- パス定義
        //(path / sceneData).GetDirectory().Create_Directorie(); // ディレクトリ作成
        //auto fileName = PathClass(sceneData).HasExtension() ?
        //    path / std::string(sceneData) :
        //    path / std::string(sceneData) += FileDefine::Extended::SCENE;

        ////----- ファイルの新規作成
        //scene.open(fileName, std::ios::out);

        ////----- シーン情報出力
        //json["SceneName"] = Utility::StringSubstitution(sceneData, "\\", "/");

        ////----- ゲームオブジェクト取得・シーン別振り分け
        //auto gameObjects = GameObjectStorage::Get()->GetGameObjectAll();
        //decltype(gameObjects) sceneObject;
        //for (auto& it : gameObjects) {
        //    if (it.GetData().GetScene() == sceneData) {
        //        sceneObject.push_back(it);
        //    }
        //}

        ////----- ゲームオブジェクト出力
        //for (auto& it : sceneObject) {
        //    json["GameObjects"] += it.GetAtomicData().Output();
        //}

        ////----- 文字列出力
        //auto data = json.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES);
        //scene << data;
    }
}
