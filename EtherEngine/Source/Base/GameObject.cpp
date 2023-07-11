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
        if (IsUnvalidObject()) return;

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
    // 物理更新処理を行う
    void GameObject::FixedUpdate(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        //----- 通常コンポーネントの物理更新処理
        for (auto& component : m_components) {
            component->FixedUpdateFunction();
        }
        DeleteComponentsDelete();

        //----- 描画コンポーネントの物理更新処理
        for (auto& component : m_drawComponents) {
            component->FixedUpdateFunction();
        }
        DeleteComponentsDelete();
    }
    // 描画処理を行う
    void GameObject::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

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
        if (IsUnvalidObject()) return;

        for (auto& component : m_components) {
            component->CollisionStartFunction();
        }
        DeleteComponentsDelete();
    }
    // 衝突開始処理を行う
    void GameObject::CollsionStart(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        for (auto& component : m_components) {
            component->CollisionEndFunction();
        }
        DeleteComponentsDelete();
    }
    // 衝突終了処理を行う
    void GameObject::CollsionEnd(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        for (auto& component : m_components) {
            component->CollisionHitFunction();
        }
        DeleteComponentsDelete();
    }
    // 衝突処理を行う
    void GameObject::CollsionHit(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

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


    // 衝突情報を削除する
    void GameObject::DeleteCollisionData(void) {
        //----- コンポーネント全てから衝突情報を削除
        for (auto& component : m_components) {
            component->SetCollisionHitData({});
        }
    }
    // 衝突情報を追加する
    void GameObject::AddCollisionData(const CollisionHitData data) {
        //----- コンポーネント全てに衝突情報を追加
        for (auto& component : m_components) {
            component->AccessCollisionHitData().push_back(data);
        }
    }
}
