#ifndef I_TESTCOMPONENT_H
#define I_TESTCOMPONENT_H
#include <Base/ComponentBase.h>


//----- TestComponent êÈåæ
namespace EtherEngine {
    class TestComponent : public ComponentBase {
    public:
        using ComponentBase::ComponentBase;

    protected:
        virtual void Start(void) override;
        virtual void Update(void) override;
        virtual void Delete(void) override;
        virtual void CollisionStart(void) override;
        virtual void CollisionEnd(void) override;
        virtual void CollisionHit(void) override;
    };
}


#endif // !I_TESTCOMPONENT_H
