#include <EtherEngine/EditorInspectorWindow.h>


//----- 表示用オブジェクト 宣言
namespace EtherEngine {
    // デフォルトコンストラクタ
    EditorInspectorObject::EditorInspectorObject(void) 
        : EditorInspectorObject(nullptr, []() -> bool {return false; }) {
    }
    // コンストラクタ
    EditorInspectorObject::EditorInspectorObject(IInspectorShow* showObject, const std::function<bool(void)>& deleteObject)
        : m_showObject(showObject)
        , m_deleteObject(deleteObject) {
    }


    // 表示オブジェクト取得
    // @ Ret  : 表示オブジェクト(既に削除されていればnullptr)
    IInspectorShow* EditorInspectorObject::GetShowObject(void) const {
        if (m_showObject == nullptr || m_deleteObject() == false) {
            return nullptr;
        }
        else {
            return m_showObject;
        }
    }
}


//----- EditorInspectorWindow 定義
namespace EtherEngine {
    // 描画処理
    void EditorInspectorWindow::DrawWindow(void) {
        auto ptr = ms_showObject.GetShowObject();
        if (ptr != nullptr) ptr->ShowInspector();
    }


    EditorInspectorObject EditorInspectorWindow::ms_showObject = EditorInspectorObject();
}
