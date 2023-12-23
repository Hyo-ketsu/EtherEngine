#include <Base/NativeGameObject.h>
#include <Base/GameObjectStorage.h>
#include <Base/CollisionHelper.h>


namespace EtherEngine {
    // �R���X�g���N�^
    NativeGameObject::NativeGameObject(const Transform& transform, const std::string& name)
        : NativeBaseObject(name)
        , m_transform(transform) {
    }


    // �X�V�������s��
    void NativeGameObject::Update(void) {
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
    void NativeGameObject::FixedUpdate(void) {
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
    // �폜���������s��
    void NativeGameObject::Delete(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

        for (auto& component : m_components) {
            component->DeleteFuntion();
        }
        DeleteComponentsDelete();
    }
    // �ՓˊJ�n�������s��
    void NativeGameObject::CollisionStart(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

        //----- �ϐ��錾
        std::vector<CollisionHitData> hitDatas; // �^�C�~���O�ɂ������Փ˔���

        //----- �f�[�^����
        for (auto&& hitData : m_hitData) {
            bool isNewOldHit = false;
            for (auto&& oldHitData : m_oldHitData) {
                //----- �ߋ��ƌ��݂ɏՓ˂��Ă���( = Hit)�Ȃ̂ŃX���[����
                if (CollisionHelper::GetParentObject(hitData)->GetId() == CollisionHelper::GetParentObject(oldHitData)->GetId()) {
                    isNewOldHit = true;
                    break;
                }
            }

            if (isNewOldHit == false) hitDatas.push_back(hitData);
        }

        //----- �f�[�^����ł���Ή������Ȃ�
        if (hitDatas.empty()) return;

        //----- �R���|�[�l���g�ɏ���^����
        for (auto& component : m_components) {
            component->SetCollisionHitData(hitDatas);
        }

        //----- �������s��
        for (auto& component : m_components) {
            component->CollisionStartFunction();
        }
        DeleteComponentsDelete();
    }
    // �ՓˏI���������s��
    void NativeGameObject::CollisionEnd(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

        //----- �ϐ��錾
        std::vector<CollisionHitData> hitDatas; // �^�C�~���O�ɂ������Փ˔���

        //----- �f�[�^����
        for (auto&& oldHitData : m_oldHitData) {
            bool isNewOldHit = false;
            for (auto&& hitData : m_hitData) {
                //----- �ߋ��ƌ��݂ɏՓ˂��Ă���( = Hit)�Ȃ̂ŃX���[����
                if (CollisionHelper::GetParentObject(oldHitData)->GetId() == CollisionHelper::GetParentObject(hitData)->GetId()) {
                    isNewOldHit = true;
                    break;
                }
            }

            if (isNewOldHit == false) hitDatas.push_back(oldHitData);
        }

        //----- �f�[�^����ł���Ή������Ȃ�
        if (hitDatas.empty()) return;

        //----- �R���|�[�l���g�ɏ���^����
        for (auto& component : m_components) {
            component->SetCollisionHitData(hitDatas);
        }

        for (auto& component : m_components) {
            component->CollisionEndFunction();
        }
        DeleteComponentsDelete();
    }
    // �Փˏ������s��
    void NativeGameObject::CollisionHit(void) {
        //----- �A�N�e�B�u�`�F�b�N
        if (IsUnvalidObject()) return;

        //----- �ϐ��錾
        std::vector<CollisionHitData> hitDatas; // �^�C�~���O�ɂ������Փ˔���

        //----- �f�[�^����
        for (auto&& hitData : m_hitData) {
            for (auto&& oldHitData : m_oldHitData) {
                //----- �ߋ��ƌ��݂ɏՓ˂��Ă���̂ł����������
                if (CollisionHelper::GetParentObject(hitData)->GetId() == CollisionHelper::GetParentObject(oldHitData)->GetId()) {
                    hitDatas.push_back(hitData);
                    break;
                }
            }
        }

        //----- �f�[�^������ł���Ή������Ȃ�
        if (hitDatas.empty()) return;

        //----- �R���|�[�l���g�ɏ���^����
        for (auto& component : m_components) {
            component->SetCollisionHitData(hitDatas);
        }

        for (auto& component : m_components) {
            component->CollisionHitFunction();
        }
        DeleteComponentsDelete();
    }


    // �폜���ꂽ�R���|�[�l���g���폜����
    void NativeGameObject::DeleteComponentsDelete(void) {
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


    std::function<std::shared_ptr<ComponentBase>(NativeGameObject*, const std::string&)> NativeGameObject::ms_getComponent = nullptr; // C++CLI��GameComponent�Ȃǂ��擾���邽�߂̃����_
    std::function<std::shared_ptr<ComponentBase>(NativeGameObject*)> NativeGameObject::ms_addComponentMenu = nullptr; // C++CLI��GameDrawComponent�Ȃǂ��擾���邽�߂̃����_
    std::function<std::string(const std::string&, const uint, const bool)> NativeGameObject::ms_getFullName = nullptr; // �e�R���|�[�l���g���̊��S�C�����擾�����_
}
