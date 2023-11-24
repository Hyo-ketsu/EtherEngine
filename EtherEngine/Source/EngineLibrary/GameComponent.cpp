#include <EngineLibrary/GameComponent.h>
#include <Base/BaseDefines.h>
#include <Base/EditorException.h>
#include <EngineLibrary/EngineLibraryUtility.h>


namespace EtherEngine {
    // �R���X�g���N�^
    // @ Memo : �R���|�[�l���g�������ł��Ȃ���Η�O�𑗏o���܂�
    // @ Arg1 : �e�Q�[���I�u�W�F�N�g
    // @ Arg2 : �����R���|�[�l���g��
    GameComponent::GameComponent(GameObject* gameObject, const std::string& componentName) 
        : ComponentBase(gameObject, componentName) 
        , m_componentName(componentName) {
        // @ MEMO : ���O����̐���
        System::Type^ type = System::Type::GetType(UNMANAGE_TO_MANAGE_STRING(componentName));
        auto component = dynamic_cast<UserBaseComponent^>(System::Activator::CreateInstance(type));

        if (component == nullptr) throw EditorException("Error! Non UserComponent");

        m_component = component;

        m_component->SetGameObject(gameObject);
    }


    // �J�n����
    void GameComponent::Start(void) {
        m_component->Start();
    }
    // �X�V����
    void GameComponent::Update(void) {
        m_component->Update();
    }
    // �폜������
    void GameComponent::Delete(void) {
        m_component->Delete();
    }
    // �ՓˊJ�n����
    void GameComponent::CollisionStart(void) {
        m_component->CollisionStart();
    }
    // �ՓˏI������
    void GameComponent::CollisionEnd(void) {
        m_component->CollisionEnd();
    }
    // �Փˏ���
    void GameComponent::CollisionHit(void) {
        m_component->CollisionHit();
    }


    // �O���o��
    Json GameComponent::Output(void) {
        auto ret = Json(Json::parse(m_component->Serialize()));
        ret["ComponentName"] = this->GetComponentName();
        ret["Active"] = this->GetActive();
        return ret;
    }
    // �O������
    void GameComponent::Input(const Json& input) {
        m_component->Deserialize(input.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES));
        SetActive(input["Active"]);
    }
    // Inspector�\��
    void GameComponent::ShowInspector(void) {
        m_component->DrawInspector();
    }
}
