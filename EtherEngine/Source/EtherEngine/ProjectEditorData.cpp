#include <EtherEngine/ProjectEditorData.h>
#include <Base/DirectoryNameDefine.h>
#include <Base/BaseDefines.h>
#include <Base/BaseUtility.h>
#include <Base/EditorException.h>
#include <EtherEngine/EditorDefine.h>


//----- ProjectEditorData 定義
namespace EtherEngine {
    // コンストラクタ
    EditorData::EditorData(const PathClass& path) {
        //----- ファイルから読み込み
        if (path.IsExists() == false) throw EditorException("Error! ProjectData NonFile!");
        if (path.HasExtension() && path.GetExtension() != FileDefine::Extended::PROJECT_DATA) throw EditorException("Error! Is File ProjectData File?");

        //----- 読み込み
        Input(EtherEngine::Utility::RoadFileAll(path.Get()));
        m_path = path;
    }

    // デストラクタ
    EditorData::~EditorData(void) {
        std::ofstream ofs(m_path);
        
        ofs << Output();
    }


    // 外部出力
    Json EditorData::Output(void) {
        nlohmann::json json;

        json["ProjectEditorData"]["CurrentScene"] = m_currentScene;

        return json;
    }
    // 外部入力
    void EditorData::Input(const Json& input) {
        //----- 変数宣言
        nlohmann::json json;

        //----- 読み込み
        try {
            json = Utility::RoadFileAll(input);
        }
        catch (...) {
            goto END;
        }

        //----- Json読み込み
        // シーン読込
        if (json.contains("ProjectEditorData") && json["ProjectEditorData"].contains("CurrentScene")) {
            m_currentScene = json["ProjectEditorData"]["CurrentScene"];
        }
        else {
            goto END;
        }

        //----- 正常終了
        return;

        //----- 読み込めなかった・もしくは項目が存在しなかった場合の処理
        END: {
        }
    }
}
