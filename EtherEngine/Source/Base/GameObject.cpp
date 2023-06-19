#include <Base/GameObject.h>
#include <Base/GameObjectStorage.h>


namespace EtherEngine {
    // コンストラクタ
    GameObject::GameObject(const Transform& transform)
        : m_transform(transform) {
    }


    // 更新処理を行う
    void GameObject::Update(void) {
        for (auto& component : m_components) {
            component->UpdateFuntion();
        }
        for (auto& component : m_drawComponents) {
            component->UpdateFuntion();
        }
    }
    // 描画処理を行う
    void GameObject::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        for (auto& component : m_drawComponents) {
            component->SetView(view);
            component->SetProjection(projection);
            component->DrawFuntion();
        }
    }
}
