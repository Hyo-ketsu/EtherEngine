#include <Base/GameObject.h>
#include <Base/GameObjectStorage.h>


namespace EtherEngine {
    // �R���X�g���N�^
    GameObject::GameObject(const Transform& transform)
        : m_transform(transform) {
    }


    // �X�V�������s��
    void GameObject::Update(void) {
        for (auto& component : m_components) {
            component->UpdateFuntion();
        }
        for (auto& component : m_drawComponents) {
            component->UpdateFuntion();
        }
    }
    // �`�揈�����s��
    void GameObject::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        for (auto& component : m_drawComponents) {
            component->SetView(view);
            component->SetProjection(projection);
            component->DrawFuntion();
        }
    }
}
