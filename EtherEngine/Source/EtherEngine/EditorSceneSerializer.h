#ifndef I_EDITORSCENESERIALIZER_H
#define I_EDITORSCENESERIALIZER_H
#include <Base/BaseDefines.h>
#include <Base/PathClass.h>


//----- EditorSceneSerialize 宣言
namespace EtherEngine {
    // 現在のシーン状態を出力する関数
    // @ Arg1 : 出力先パス
    // @ Arg2 : 出力シーン
    void EditorSceneSerialize(const PathClass& path, const SceneType& sceneData);
}


#endif // !I_EDITORSCENESERIALIZER_H
