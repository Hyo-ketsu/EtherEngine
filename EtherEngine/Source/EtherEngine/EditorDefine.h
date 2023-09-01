#ifndef I_EDITORDEFINE_H
#define I_EDITORDEFINE_H
#include <Base/BaseInput.h>


namespace EtherEngine {
    // エディター定数定義
    namespace EditorDefine {
        const std::string EDITOR_DEFAULT_SCENE_NAME = "UndefineScene";  // シーンを開いていなかった際につけるシーン名
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
}


#endif // !I_EDITORDEFINE_H
