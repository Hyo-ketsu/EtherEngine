#ifndef I_EDITORDEFINE_H
#define I_EDITORDEFINE_H
#include <Base/BaseInput.h>


namespace EtherEngine {
    // エディター定数定義
    namespace EditorDefine {
        const std::string EDITOR_DEFAULT_SCENE_NAME = "UndefineScene";  // シーンを開いていなかった際につけるシーン名
        const std::string EDITOR_BUILD_TOOKEN = "@@@";
        const std::string EDITOR_BUILD_OK = EDITOR_BUILD_TOOKEN + "OK!" + EDITOR_BUILD_TOOKEN;
        const std::string EDITOR_BUILD_ERROR = EDITOR_BUILD_TOOKEN + "Error!" + EDITOR_BUILD_TOOKEN;
    }


    // エディターのDefault設定
    namespace EditorDefaultConfig {
        const float EDITOR_CAMERA_SPEED = 0.025f;   // エディターのカメラの初期速度
    }


    // エディターの入力キー
    namespace EditorKey {
        const KeyboardInput INPUT_DECISION = VK_RETURN; // 決定キー
        const KeyboardInput INPUT_CANCEL = VK_ESCAPE;   // キャンセルキー
        
        const KeyboardInput INPUT_RENAME = VK_F2;   // リネームキー
    }


    // エディターのファイル構成
    namespace EditorFileDefine {
        namespace Directory {
            const PathClass EDITOR_SETTING = "EditorSetting"; // エディターについての設定を保持しているディレクトリ
            const PathClass EDITOR_MIDDLE_DATA = "Object";    // エディターの中間ファイル(アセンブリやプロジェクト自体の中間ファイル等)が格納されているディレクトリ
        }

        const std::string PROJECT_DATA = "ProjectSetting.setting";     // プロジェクトの設定を保持しているファイル
        const std::string EDITOR_SETTING = "EditorSetting.setting";    // エディターの設定を保持しているファイル
    }
}


#endif // !I_EDITORDEFINE_H
