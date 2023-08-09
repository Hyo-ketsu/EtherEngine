#include <EtherEngine/ProjectEditorData.h>
#include <Base/DirectoryNameDefine.h>
#include <Base/SceneLoader.h>
#include <EtherEngine/EditorDefine.h>


//----- ProjectEditorData 定義
namespace EtherEngine {
    // コンストラクタ
    ProjectEditorData::ProjectEditorData(const PathClass& path) {

    }


    // 外部出力
    std::string ProjectEditorData::Output(void) {
        nlohmann::json json;

        if (m_currentScene.has_value()) json["ProjectEditorData"]["CurrentScene"] = m_currentScene.value();

        return json.dump(msc_dump);
    }
    // 外部入力
    void ProjectEditorData::Input(const std::string& input) {
        nlohmann::json json = nlohmann::json::parse(input);

        //----- Json読み込み
        // シーン読込
        if (json.contains("ProjectEditorData") && json["ProjectEditorData"].contains("CurrentScene")) {
            m_currentScene.value() = json["ProjectEditorData"]["CurrentScene"];
            SceneLoader::Get()->MoveScene(m_currentScene.value());
        }
        else {
            //----- 存在しないためデフォルトシーンを作成
            m_currentScene.value() = SceneData(DirectoryDefine::SCENE_DATA + EditorDefine::EDITOR_DEFAULT_SCENE_NAME);
        }
    }
}
