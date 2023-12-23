#include <EtherEngine/EditorComponentBase.h>


//----- EditorComponent実装
namespace EtherEngine {
    // コンストラクタ
    EditorComponentBase::EditorComponentBase(void* editorObject)
        : NativeBaseObject("EditorComponent")
        , m_eidtorObject(editorObject) 
        , m_isStart(false) {
    }


    // 親エディターオブジェクト取得
    void EditorComponentBase::GetEditorObject(void** editerObject) const {
        *editerObject = m_eidtorObject;
    }


    // 更新処理
    void EditorComponentBase::UpdateFunction(void) {
        //----- アクティブチェッカー
        if (GetActive() == false) return;

        //----- 更新処理・若しくは初期化処理
        if (m_isStart) {
            //----- 更新処理
            Update();
        }
        else {
            //----- 初期化処理
            Start();
            m_isStart = true;
        }
    }
    // 描画処理
    void EditorComponentBase::DrawFunction(void) {
        //----- アクティブチェッカー
        if (GetActive() == false) return;

        //----- 描画処理
        Draw();
    }
    // 削除時処理
    void EditorComponentBase::DeleteFunction(void) {
        //----- アクティブチェッカー
        if (GetActive() == false) return;

        //----- 削除時処理
        Delete();
    }
}
