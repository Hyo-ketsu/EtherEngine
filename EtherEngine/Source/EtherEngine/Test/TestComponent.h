#ifndef I_TESTCOMPONENT_H
#define I_TESTCOMPONENT_H
#include <C++CLI/UserComponent.h>


//----- TestComponent êÈåæ
namespace EtherEngine {
    public ref class TestComponent : public UserBaseComponent {
    public:
        void Update(void) override {
            System::Type^ type = System::Type::GetType(UnToManage("TestComponent"));
        }
    };
}


#endif // !I_TESTCOMPONENT_H
