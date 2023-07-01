#include <Base/GameObject.h>
#include <Base/GameObjectStorage.h>


namespace EtherEngine {
    // �R���X�g���N�^
    GameObject::GameObject(const Transform& transform, const std::string& name)
        : BaseObject(name)
        , m_transform(transform) {
    }


    // �X�V�������s��
    void GameObject::Update(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (GetActive() == false) return;
        if (GetDelete()) return;

        //----- �ʏ�R���|�[�l���g�̍X�V����
        for (auto& component : m_components) {
            component->UpdateFuntion();
        }
        DeleteComponentsDelete();

        //----- �`��R���|�[�l���g�̍X�V����
        for (auto& component : m_drawComponents) {
            component->UpdateFuntion();
        }
        DeleteComponentsDelete();
    }
    // �`�揈�����s��
    void GameObject::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        //----- �A�N�e�B�u�`�F�b�N
        if (GetActive() == false) return;
        if (GetDelete()) return;

        //----- �`��R���|�[�l���g�̕`�揈��
        for (auto& component : m_drawComponents) {
            component->SetView(view);
            component->SetProjection(projection);
            component->DrawFuntion();
        }
        DeleteComponentsDelete();
    }
    // �폜���������s��
    void GameObject::Delete(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (GetActive() == false) return;
        if (GetDelete()) return;

        for (auto& component : m_components) {
            component->DeleteFuntion();
        }
        DeleteComponentsDelete();
    }


    // �폜���ꂽ�R���|�[�l���g���폜����
    void GameObject::DeleteComponentsDelete(void) {
        for (auto it = m_components.begin(); it != m_components.end();) {
            //----- �폜���邩
            if ((*it)->GetDelete()) {
                //----- �폜����Ă�B�폜
                it = m_components.erase(it);
            }
            else {
                it++;
            }
        }
        for (auto it = m_drawComponents.begin(); it != m_drawComponents.end();) {
            //----- �폜���邩
            if ((*it)->GetDelete()) {
                //----- �폜����Ă�B�폜
                it = m_drawComponents.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
