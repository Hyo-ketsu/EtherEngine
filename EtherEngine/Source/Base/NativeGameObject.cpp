#include <Base/NativeGameObject.h>
#include <Base/NativeGameObjectStorage.h>
#include <Base/CollisionHelper.h>


namespace EtherEngine {
    // �R���X�g���N�^
    NativeGameObject::NativeGameObject(const Transform& transform, const std::string& name)
        : NativeBaseObject(name)
        , m_transform(transform) {
    }


    // �`�揈�����s��
    void NativeGameObject::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
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


    // �폜���ꂽ�R���|�[�l���g���폜����
    void NativeGameObject::DeleteComponentsDelete(void) {
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
        for (auto it = m_collisions.begin(); it != m_collisions.end();) {
            //----- �폜���邩
            if ((*it)->GetDelete()) {
                //----- �폜����Ă�B�폜
                it = m_collisions.erase(it);
            }
            else {
                it++;
            }
        }
    }


    // ���΍��W�Q�b�^�[
    const Transform& NativeGameObject::GetLocalTransform(void) const {
        return m_transform;
    }
    // ���΍��W�Z�b�^�[
    void NativeGameObject::SetLocalTransform(const Transform& in) {
        m_transform = in;
    }


    // �Փˏ����폜�E�X�^�b�L���O����
    void NativeGameObject::SidelineCollisionData(void) {
        m_oldHitData = std::move(m_hitData);
        m_hitData = decltype(m_hitData)();
    }
    // �Փˏ���ǉ�����
    void NativeGameObject::AddCollisionData(const CollisionHitData data) {
        m_hitData.push_back(data);
    }
}
