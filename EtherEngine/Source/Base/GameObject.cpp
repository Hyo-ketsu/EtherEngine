#include <Base/GameObject.h>


namespace EtherEngine {
    // �R���X�g���N�^
    GameObject::GameObject(const Transform& transform)
        : m_transform(transform) {
    }


    // �X�V�������s��
    void GameObject::Update(void) {
        for (auto& component : m_components) {
            component.GetAtomicData().UpdateFuntion();
        }
    }
    // �`�揈�����s��
    void GameObject::Draw(void) {
        for (auto& component : m_components) {
            component.GetAtomicData().DrawFuntion();
        }
    }
}
