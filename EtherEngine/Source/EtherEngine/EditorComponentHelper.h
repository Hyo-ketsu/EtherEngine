#ifndef I_EDITORCOMPONENTHELPER_H
#define I_EDITORCOMPONENTHELPER_H
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorComponentBase.h>


namespace EtherEngine {
    // EditorComponentのヘルパー
    namespace EditorComponentHelper {
        // コンポーネントの所属ゲームオブジェクト取得
        // @ Ret  : 所属ゲームオブジェクト
        // @ Arg1 : 所属ゲームオブジェクトを取得したいコンポーネント
        EditorObject* const GetEditorObject(const EditorComponentBase& component);
        // コンポーネントの所属ゲームオブジェクト取得
        // @ Ret  : 所属ゲームオブジェクト
        // @ Arg1 : 所属ゲームオブジェクトを取得したいコンポーネント
        EditorObject* const GetEditorObject(const EditorComponentBase* const component);
    };
}


#endif // !I_EDITORCOMPONENTHELPER_H
