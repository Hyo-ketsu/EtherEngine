#include <EtherEngine/EditorComponentHelper.h>


//----- EditorComponentHelper定義
namespace EtherEngine {
    // コンポーネントの所属ゲームオブジェクト取得
    EditorObject* const EditorComponentHelper::GetEditorObject(const EditorComponentBase& component) {
        void* ret = nullptr;
        component.GetEditorObject(&ret);
        return static_cast<EditorObject*>(ret);
    }
    // コンポーネントの所属ゲームオブジェクト取得
    EditorObject* const EditorComponentHelper::GetEditorObject(const EditorComponentBase* const component) {
        void* ret = nullptr;
        component->GetEditorObject(&ret);
        return static_cast<EditorObject*>(ret);
    }
}
