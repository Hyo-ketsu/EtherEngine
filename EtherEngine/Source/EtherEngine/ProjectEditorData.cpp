#include <EtherEngine/ProjectEditorData.h>
#include <Base/DirectoryNameDefine.h>
#include <Base/BaseDefines.h>
#include <Base/SceneLoader.h>
#include <Base/EtherEngineUtility.h>
#include <EtherEngine/EditorDefine.h>


//----- ProjectEditorData 定義
namespace EtherEngine {
    // コンストラクタ
    ProjectEditorData::ProjectEditorData(const PathClass& path) {
        Input(path);
    }


    // 外部出力
    std::string ProjectEditorData::Output(void) {
        nlohmann::json json;

        if (m_currentScene.has_value()) json["ProjectEditorData"]["CurrentScene"] = m_currentScene.value();

        return json.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES);
    }
    // 外部入力
    void ProjectEditorData::Input(const std::string& input) {
        //----- 変数宣言
        nlohmann::json json;

        //----- 読み込み
        try {
            json = nlohmann::json::parse(RoadFileAll(input));
        }
        catch (...) {
            goto END;
        }

        //----- Json読み込み
        // シーン読込
        if (json.contains("ProjectEditorData") && json["ProjectEditorData"].contains("CurrentScene")) {
            m_currentScene.value() = json["ProjectEditorData"]["CurrentScene"];
            SceneLoader::Get()->MoveScene(m_currentScene.value());
        }
        else {
            goto END;
        }

        //----- 正常終了
        return;

        //----- 読み込めなかった・もしくは項目が存在しなかった場合の処理
        END: {
            //----- 存在しないためデフォルトシーンを作成、登録
            m_currentScene = SceneData(DirectoryDefine::SCENE_DATA + '\\' + EditorDefine::EDITOR_DEFAULT_SCENE_NAME);
            SceneLoader::Get()->RegistryScene(m_currentScene.value());
        }
    }
}
