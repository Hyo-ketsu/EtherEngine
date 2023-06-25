#include <EtherEngine/EditorComponentBase.h>


//----- EditorComponent実装
namespace EtherEngine {
    // コンストラクタ
    EditorComponentBase::EditorComponentBase(void* editorObject)
        : m_eidtorObject(editorObject) 
        , m_isStart(false) {
    }


    // 親エディターオブジェクト取得
    void EditorComponentBase::GetEditorObject(void** editerObject) const {
        *editerObject = m_eidtorObject;
    }


    // 更新処理
    void EditorComponentBase::UpdateFunction(void) {
        if (m_isStart) {
            Update();
        }
        else {
            Start();
            m_isStart = true;
        }
    }
    // 描画処理
    void EditorComponentBase::DrawFunction(void) {
        Draw();
    }
}
