#include <EngineLibrary/WrapperDrawComponent.h>
#include <EngineLibrary/DrawComponent.h>


//----- WrapperDrawComponent ��`
namespace EtherEngine {
    // �R���X�g���N�^
    WrapperDrawComponent::WrapperDrawComponent(NativeGameObject* gameObject, const std::string& componentName)
        : WrapperComponent(gameObject, componentName) 
        , DrawComponent(gameObject, componentName) {
    }
    // �J�n����
    void WrapperDrawComponent::Start(void) {
        WrapperComponent::Start();
    }
    // �X�V����
    void WrapperDrawComponent::Update(void) {
        WrapperComponent::Update();
    }
    // �폜������
    void WrapperDrawComponent::Delete(void) {
        WrapperComponent::Delete();
    }
    // �ՓˊJ�n����
    void WrapperDrawComponent::CollisionStart(void) {
        WrapperComponent::CollisionStart();
    }
    // �ՓˏI������
    void WrapperDrawComponent::CollisionEnd(void) {
        WrapperComponent::CollisionEnd();
    }
    // �Փˏ���
    void WrapperDrawComponent::CollisionHit(void) {
        WrapperComponent::CollisionHit();
    }
    // �`��
    void WrapperDrawComponent::Draw(void) {    
        //----- �L���X�g
        auto userBaseComponent = safe_cast<Component^>(m_component);
        auto userDrawBaseComponent = dynamic_cast<DrawBaseComponent^>(userBaseComponent);

        //----- �`��
        userDrawBaseComponent->Bind();
        userDrawBaseComponent->Draw();
    }


    // �O���o��
    Json WrapperDrawComponent::Output(void) {
        return WrapperComponent::Output();
    }
    // �O������
    void WrapperDrawComponent::Input(const Json& input) {
        WrapperComponent::Input(input);
    }
}
