#ifndef I_HANDLEHELPER_H
#define I_HANDLEHELPER_H

#include <Base/Handle.h>


//----- HelperéŒ¾
namespace EtherEngine {
    static class HandleHelper {
    public:
        template <HandleSystemConcept Type>
        Handle<Type> AddItem(Type&& item);
    };
}




//----- HelperéŒ¾
namespace EtherEngine {
    template <HandleSystemConcept Type>
    Handle<Type> HandleHelper::AddItem(Type&& item) {
        return Handle<Type>(HandleSystem<Type>::Get()->AddItem(item));
    }
}


#endif // !I_HANDLEHELPER_H
