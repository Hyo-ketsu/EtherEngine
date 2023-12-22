#include <EngineLibrary/GameDrawComponent.h>
#include <EngineLibrary/UserDrawComponent.h>


//----- GameDrawComponent ��`
namespace EtherEngine {
    // �R���X�g���N�^
    GameDrawComponent::GameDrawComponent(GameObject* gameObject, const std::string& componentName)
        : GameComponent(gameObject, componentName) 
        , DrawComponent(gameObject, componentName) {
    }
    // �J�n����
    void GameDrawComponent::Start(void) {
        GameComponent::Start();
    }
    // �X�V����
    void GameDrawComponent::Update(void) {
        GameComponent::Update();
    }
    // �폜������
    void GameDrawComponent::Delete(void) {
        GameComponent::Delete();
    }
    // �ՓˊJ�n����
    void GameDrawComponent::CollisionStart(void) {
        GameComponent::CollisionStart();
    }
    // �ՓˏI������
    void GameDrawComponent::CollisionEnd(void) {
        GameComponent::CollisionEnd();
    }
    // �Փˏ���
    void GameDrawComponent::CollisionHit(void) {
        GameComponent::CollisionHit();
    }
    // �`��
    void GameDrawComponent::Draw(void) {    
        //----- �L���X�g
        auto userBaseComponent = safe_cast<UserBaseComponent^>(m_component);
        auto userDrawBaseComponent = dynamic_cast<UserDrawBaseComponent^>(userBaseComponent);

        //----- �`��
        userDrawBaseComponent->Bind();
        userDrawBaseComponent->Draw();
    }


    // �O���o��
    Json GameDrawComponent::Output(void) {
        return GameComponent::Output();
    }
    // �O������
    void GameDrawComponent::Input(const Json& input) {
        GameComponent::Input(input);
    }
}
