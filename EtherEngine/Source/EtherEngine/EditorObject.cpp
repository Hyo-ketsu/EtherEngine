#include <EtherEngine/EditorObject.h>


//----- EditorObject定義
namespace EtherEngine {
    // コンストラクタ
    EditorObject::EditorObject(const Transform& transform, const std::string& name)
        : BaseObject(name)
        , m_transform(transform) {
    }


    // 更新処理を行う
    void EditorObject::Update(void) {
        //----- アクティブチェッカー
        if (GetActive() == false) return;
        if (GetDelete()) return;

        //----- 更新処理
        for (auto&& component : m_components) {
            component->UpdateFunction();
        }
        DeleteComponentsDelete();
    }
    // 描画処理を行う
    void EditorObject::Draw(void) {
        //----- アクティブチェッカー
        if (GetActive() == false) return;
        if (GetDelete()) return;

        //----- 描画処理
        for (auto&& component : m_components) {
            component->DrawFunction();
        }
        DeleteComponentsDelete();
    }
    // 削除時処理を行う
    void EditorObject::Delete(void) {
        //----- アクティブチェッカー
        if (GetActive() == false) return;
        if (GetDelete()) return;

        //----- 削除時処理
        for (auto&& component : m_components) {
            component->DeleteFunction();
        }
        DeleteComponentsDelete();
    }


    // 削除されたコンポーネントを削除する
    void EditorObject::DeleteComponentsDelete(void) {
        if (m_components.empty()) return;
        for (auto it = m_components.begin(); it != m_components.end();) {
            //----- 削除するか
            if ((*it)->GetDelete()) {
                //----- 削除されてる。削除
                it = m_components.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
