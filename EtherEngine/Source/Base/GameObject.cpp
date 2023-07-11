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
        if (IsUnvalidObject()) return;

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
    // �����X�V�������s��
    void GameObject::FixedUpdate(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

        //----- �ʏ�R���|�[�l���g�̕����X�V����
        for (auto& component : m_components) {
            component->FixedUpdateFunction();
        }
        DeleteComponentsDelete();

        //----- �`��R���|�[�l���g�̕����X�V����
        for (auto& component : m_drawComponents) {
            component->FixedUpdateFunction();
        }
        DeleteComponentsDelete();
    }
    // �`�揈�����s��
    void GameObject::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

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
        if (IsUnvalidObject()) return;

        for (auto& component : m_components) {
            component->CollisionStartFunction();
        }
        DeleteComponentsDelete();
    }
    // �ՓˊJ�n�������s��
    void GameObject::CollsionStart(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

        for (auto& component : m_components) {
            component->CollisionEndFunction();
        }
        DeleteComponentsDelete();
    }
    // �ՓˏI���������s��
    void GameObject::CollsionEnd(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

        for (auto& component : m_components) {
            component->CollisionHitFunction();
        }
        DeleteComponentsDelete();
    }
    // �Փˏ������s��
    void GameObject::CollsionHit(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

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


    // �Փˏ����폜����
    void GameObject::DeleteCollisionData(void) {
        //----- �R���|�[�l���g�S�Ă���Փˏ����폜
        for (auto& component : m_components) {
            component->SetCollisionHitData({});
        }
    }
    // �Փˏ���ǉ�����
    void GameObject::AddCollisionData(const CollisionHitData data) {
        //----- �R���|�[�l���g�S�ĂɏՓˏ���ǉ�
        for (auto& component : m_components) {
            component->AccessCollisionHitData().push_back(data);
        }
    }
}
