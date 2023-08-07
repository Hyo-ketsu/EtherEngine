#include <C++CLI/GameComponent.h>
#include <C++CLI/C++CLIUtility.h>


namespace EtherEngine {
    // �R���X�g���N�^
    // @ Memo : �R���|�[�l���g�������ł��Ȃ���Η�O�𑗏o���܂�
    // @ Arg1 : �e�Q�[���I�u�W�F�N�g
    // @ Arg2 : �����R���|�[�l���g��
    GameComponent::GameComponent(GameObject* gameObject, const std::string& componentName) 
        : ComponentBase(gameObject, componentName) 
        , m_componentName(componentName) {
        // @ MEMO : ���O����̐���
        Type^ type = Type::GetType(UnToManage(componentName));
        auto component = dynamic_cast<UserBaseComponent^>(Activator::CreateInstance(type));

        if (component == nullptr) throw std::exception("Error! Non UserComponent");

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
    std::string GameComponent::Output(void) {
        return m_component->Serialize();
    }
    // �O������
    void GameComponent::Input(const std::string& input) {
        m_component->Deserialize(input);
    }
}
