#include <EtherEngine/EditorObject.h>


//----- EditorObject定義
namespace EtherEngine {
    // コンストラクタ
    EditorObject::EditorObject(const Transform& transform)
        : m_transform(transform) {
    }


    // 更新処理を行う
    void EditorObject::Update(void) {
        for (auto&& it : m_component) {
            it->UpdateFunction();
        }
    }
    // 描画処理を行う
    void EditorObject::Draw(void) {
        for (auto&& it : m_component) {
            it->DrawFunction();
        }
    }
}
