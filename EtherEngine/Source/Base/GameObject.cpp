#include <Base/GameObject.h>
#include <Base/GameObjectStorage.h>


namespace EtherEngine {
    // コンストラクタ
    GameObject::GameObject(const Transform& transform, const std::string& name)
        : BaseObject(name)
        , m_transform(transform) {
    }


    // 更新処理を行う
    void GameObject::Update(void) {
        //----- アクティブチェック
        if (GetActive() == false) return;
        if (GetDelete()) return;

        //----- 通常コンポーネントの更新処理
        for (auto& component : m_components) {
            component->UpdateFuntion();
        }
        DeleteComponentsDelete();

        //----- 描画コンポーネントの更新処理
        for (auto& component : m_drawComponents) {
            component->UpdateFuntion();
        }
        DeleteComponentsDelete();
    }
    // 描画処理を行う
    void GameObject::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        //----- アクティブチェック
        if (GetActive() == false) return;
        if (GetDelete()) return;

        //----- 描画コンポーネントの描画処理
        for (auto& component : m_drawComponents) {
            component->SetView(view);
            component->SetProjection(projection);
            component->DrawFuntion();
        }
        DeleteComponentsDelete();
    }
    // 削除時処理を行う
    void GameObject::Delete(void) {
        //----- アクティブチェック
        if (GetActive() == false) return;
        if (GetDelete()) return;

        for (auto& component : m_components) {
            component->DeleteFuntion();
        }
        DeleteComponentsDelete();
    }


    // 削除されたコンポーネントを削除する
    void GameObject::DeleteComponentsDelete(void) {
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
        for (auto it = m_drawComponents.begin(); it != m_drawComponents.end();) {
            //----- 削除するか
            if ((*it)->GetDelete()) {
                //----- 削除されてる。削除
                it = m_drawComponents.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
