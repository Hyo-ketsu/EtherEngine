#include <Base/GameObject.h>
#include <Base/GameObjectStorage.h>
#include <Base/CollisionHelper.h>


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
    void GameObject::CollisionStart(void) {
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
    void GameObject::CollisionEnd(void) {
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
    void GameObject::CollisionHit(void) {
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


    // ���΍��W�Q�b�^�[
    const Transform& GameObject::GetLocalTransform(void) const {
        return m_transform;
    }
    // ���΍��W�Z�b�^�[
    void GameObject::SetLocalTransform(const Transform& in) {
        m_transform = in;
    }


    // �Փˏ����폜�E�X�^�b�L���O����
    void GameObject::SidelineCollisionData(void) {
        m_oldHitData = std::move(m_hitData);
        m_hitData = decltype(m_hitData)();
    }
    // �Փˏ���ǉ�����
    void GameObject::AddCollisionData(const CollisionHitData data) {
        m_hitData.push_back(data);
    }


    // �O���o��
    Json GameObject::Output(void) {
        //----- �ϐ��錾
        nlohmann::json json;

        //----- �Q�[���I�u�W�F�N�g���g�̏��o��
        json["GameObject"]["ID"] = 0;// GetId().Get();
        json["GameObject"]["Name"] = GetName().c_str();

        //----- �R���|�[�l���g�o��
        for (auto& it : m_components) {
            json["GameObject"]["Components"][it->GetComponentName()] = it->Output();
            json["GameObject"]["Components"][it->GetComponentName()]["ComponentType"] = it->GetComponentTypeName();
        }
        //----- �`��R���|�[�l���g�o��
        for (auto& it : m_drawComponents) {
            json["GameObject"]["Components"][it->GetComponentName()] = it->Output();
            json["GameObject"]["Components"][it->GetComponentName()]["ComponentType"] = it->GetComponentTypeName();
        }
        //----- �����蔻��R���|�[�l���g�o��
        // @ MEMO : ���݂͖�����
        //for (auto& it : m_collisions) {
        //    json["GameObject"]["Components"][it->GetComponentName()] = it->Output();
        //    json["GameObject"]["Components"][it->GetComponentName()]["ComponentType"] = it->GetComponentTypeName();
        //}

        //----- �ԋp
        return json;
    }
    // �O������
    void GameObject::Input(const Json& input) {
        //----- �Q�[���I�u�W�F�N�g���g�̏��擾
        // @ MEMO : ID�͕ۗ�
        //this->SetId(json["GameObject"]["ID"])
        SetName(input["GameObject"]["Name"]);

        //----- �R���|�[�l���g����
        for (auto& it : input["GameObject"]["Components"]) {
            //----- �^�C�v�ɉ������R���|�[�l���g����
            std::string type = input["GameObject"]["Components"]["ComponentType"];
            
            do {
                //----- �ʏ�R���|�[�l���g����
                // @ MEMO : �������̂���AddComponent�Ɋ����H
                if (type == Component::TYPE_COMPONENT) {
                    m_components.push_back(ms_getComponent(this, type));
                    m_components.back()->Input(it);
                    break;
                }
                //----- �`��R���|�[�l���g����
                if (type == Component::TYPE_DRAW_COMPONENT) {
                    m_drawComponents.push_back(ms_getDrawComponent(this, type));
                    m_drawComponents.back()->Input(it);
                    break;
                }
                //----- �����蔻��R���|�[�l���g����
                // @ MEMO : ���
                //if (type == Component::TYPE_DRAW_COMPONENT) {
                //    m_collisions.push_back(std::make_shared<CollisionComponent>(CollisionComponent<>()));
                //}
            } while (false);
        }
    }


    std::function<std::shared_ptr<ComponentBase>&&(GameObject*, const std::string&)> GameObject::ms_getComponent = nullptr; // C++CLI��GameComponent�Ȃǂ��擾���邽�߂̃����_
    std::function<std::shared_ptr<DrawComponent>&&(GameObject*, const std::string&)> GameObject::ms_getDrawComponent = nullptr; // C++CLI��GameDrawComponent�Ȃǂ��擾���邽�߂̃����_
}
