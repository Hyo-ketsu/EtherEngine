#include <Base/GameObject.h>
#include <Base/GameObjectStorage.h>
#include <Base/CollisionHelper.h>
#include <ImGUI/ImGUIWrapFunction.h>


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
            component->DeleteFuntion();
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


    // �R���|�[�l���g�ǉ�
    std::weak_ptr<ComponentBase> GameObject::AddComponent(const std::string& componentTypeName) {
        //----- �R���|�[�l���g����
        auto component = ms_getComponent(this, componentTypeName);
        if (component == nullptr) return std::weak_ptr<ComponentBase>();

        //----- �ʏ�R���|�[�l���g����
        if (component->GetComponentTypeName() == Component::TYPE_COMPONENT) {
            m_components.push_back(component);
            return std::weak_ptr<ComponentBase>(component);
        }
        //----- �`��R���|�[�l���g����
        if (component->GetComponentTypeName() == Component::TYPE_DRAW_COMPONENT) {
            auto drawComponent = std::dynamic_pointer_cast<DrawComponent>(component);
            m_drawComponents.push_back(drawComponent);
            return std::weak_ptr<ComponentBase>(drawComponent);
        }
        //----- �����蔻��R���|�[�l���g����
        // @ MEMO : ���
        //if (type == Component::TYPE_DRAW_COMPONENT) {
        //    m_collisions.push_back(std::make_shared<CollisionComponent>(CollisionComponent<>()));
        //}

        return std::weak_ptr<ComponentBase>();
    }
    // �R���|�[�l���g�폜
    bool GameObject::DeleteComponent(const std::string& componentTypeName) {
        //----- �e�R���|�[�l���g���瑖���A�폜
        for (auto&& it : m_components) {
            if (it->GetComponentName() == componentTypeName) {
                it->DeleteFuntion();
                it->DeleteObject();
                return true;
            }
        }
        for (auto&& it : m_drawComponents) {
            if (it->GetComponentName() == componentTypeName) {
                it->DeleteFuntion();
                it->DeleteObject();
                return true;
            }
        }
        for (auto&& it : m_collisions) {
            if (it->GetComponentName() == componentTypeName) {
                it->DeleteFuntion();
                it->DeleteObject();
                return true;
            }
        }

        return false;
    }
    // �R���|�[�l���g���擾����
    std::weak_ptr<ComponentBase> GameObject::GetComponent(const std::string& componentTypeName, uint index) {
        //----- �e�R���|�[�l���g���瑖���A�擾
        for (auto&& it : m_components) {
            if (it->GetComponentName() == componentTypeName) {
                return std::weak_ptr<ComponentBase>(it);
            }
        }
        for (auto&& it : m_drawComponents) {
            if (it->GetComponentName() == componentTypeName) {
                return std::weak_ptr<ComponentBase>(it);
            }
        }
        for (auto&& it : m_collisions) {
            if (it->GetComponentName() == componentTypeName) {
                return std::weak_ptr<ComponentBase>(it);
            }
        }

        return std::weak_ptr<ComponentBase>();
    }
    // �R���|�[�l���g���擾����
    std::vector<std::weak_ptr<ComponentBase>> GameObject::GetComponents(const std::string& componentTypeName) {
        //----- �ϐ��錾
        std::vector<std::weak_ptr<ComponentBase>> ret;

        //----- �R���|�[�l���g���擾�ł��Ȃ��Ȃ�܂Ŏ擾
        for (uint i = 0;; i++) {
            auto component = GetComponent(componentTypeName);
            if (component.expired()) {
                break;
            }
            else {
                ret.push_back(component);
            }
        }

        //----- �ԋp
        return ret;
    }


    // �O���o��
    Json GameObject::Output(void) {
        //----- �ϐ��錾
        nlohmann::json json;

        //----- �Q�[���I�u�W�F�N�g���g�̏��o��
        json["GameObject"]["ID"] = GetId().Get();
        json["GameObject"]["Name"] = GetName().c_str();

        //----- �R���|�[�l���g�o��
        auto components = nlohmann::json::array();
        for (auto& it : m_components) {
            components.push_back(it->Output());
        }
        //----- �`��R���|�[�l���g�o��
        for (auto& it : m_drawComponents) {
            components.push_back(it->Output());
        }
        //----- �����蔻��R���|�[�l���g�o��
        // @ MEMO : ���݂͖�����
        //for (auto& it : m_collisions) {
        //    components[it->GetComponentName()] = it->Output();
        //    components[it->GetComponentName()]["ComponentType"] = it->GetComponentTypeName();
        //}

        //----- �z��o��
        json["GameObject"]["Components"] = components;

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
        auto hoge = input["GameObject"]["Components"].dump(2);
        if (input["GameObject"].contains("Components") == false) goto NO_CREATE_COMPONENT;
        for (auto& it : input["GameObject"]["Components"].items()) {            
            //----- �R���|�[�l���g����
            auto ret = AddComponent(it.value()["ComponentName"]);
            if (ret.expired()) continue;
            
            //----- ���͒l����
            ret.lock()->Input(it.value());
        }

        NO_CREATE_COMPONENT: {}
    }


    // Inspector�\��
    void GameObject::ShowInspector(void) {
        //----- ���O�\��
        ImGuiFunction::ImGuiShow(this->AccessName(), "Name");

        //----- �e�R���|�[�l���g�\��
        for (auto&& it : m_components) {
            ImGui::Text(it->GetName().c_str());
            it->ShowInspector();
        }
        for (auto&& it : m_drawComponents) {
            ImGui::Text(it->GetName().c_str());
            it->ShowInspector();
        }
        for (auto&& it : m_collisions) {
            ImGui::Text(it->GetName().c_str());
            it->ShowInspector();
        }

        //----- �R���|�[�l���g�ǉ��{�^��
        if (ImGui::Button("Add Component")) {
            ImGui::OpenPopup("AddComponent Popup");
        }

        //----- �R���|�[�l���g�ǉ��{�^�����j���[�\��
        if (ImGui::BeginPopup("AddComponent Popup")) {
            //----- ���j���[�\��
            auto component = ms_addComponentMenu(this);

            //----- �R���|�[�l���g�ǉ�
            if (component != nullptr) {
                if (component->GetComponentTypeName() == Component::TYPE_COMPONENT) {
                    m_components.push_back(component);
                } 
                else if (component->GetComponentTypeName() == Component::TYPE_DRAW_COMPONENT) {
                    auto drawComponent = std::dynamic_pointer_cast<DrawComponent>(component);
                    m_drawComponents.push_back(drawComponent);
                }
                else if (component->GetComponentTypeName() == Component::TYPE_COLLISION_COMPONENT) {
                    auto collisionComponent = std::dynamic_pointer_cast<CollisionComponent>(component);
                    m_collisions.push_back(collisionComponent);
                }
            }

            //----- ���j���[�\���I��
            ImGui::EndPopup();
        }
    }


    std::function<std::shared_ptr<ComponentBase>(GameObject*, const std::string&)> GameObject::ms_getComponent = nullptr; // C++CLI��GameComponent�Ȃǂ��擾���邽�߂̃����_
    std::function<std::shared_ptr<ComponentBase>(GameObject*)> GameObject::ms_addComponentMenu; // C++CLI��GameDrawComponent�Ȃǂ��擾���邽�߂̃����_
    std::function<std::string(const std::string&, const uint, const bool)> GameObject::ms_getFullName; // �e�R���|�[�l���g���̊��S�C�����擾�����_
}
