#include <EtherEngine/Test/TestComponent.h>
#include <Base/LogSystem.h>
#include <Base/CollisionSphere.h>


//----- TestComponent íËã`
namespace EtherEngine {
    void TestComponent::Start(void) {
        auto gameObject = ComponentHelper::GetParentObject(this);
        gameObject->AddComponent<CollisionComponent>(CollisionSphere(CollisionType::Substance, 5));
    }
    void TestComponent::Update(void) {

    }
    void TestComponent::Delete(void) {

    }
    void TestComponent::CollisionStart(void) {
        LogSystem::AddLogWindowMessage(LogWindowMessage("è’ìÀäJén"));
    }
    void TestComponent::CollisionEnd(void) {

    }
    void TestComponent::CollisionHit(void) {
        LogSystem::AddLogWindowMessage(LogWindowMessage("è’ìÀÇµÇƒÇ¢Ç‹Ç∑"));
    }
}
