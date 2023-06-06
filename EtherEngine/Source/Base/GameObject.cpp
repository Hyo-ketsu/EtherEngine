#include <Base/GameObject.h>


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
    }
    // 描画処理を行う
    void GameObject::Draw(void) {
        for (auto& component : m_components) {
            component->DrawFuntion();
        }
    }
}
