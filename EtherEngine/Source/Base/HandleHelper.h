#ifndef I_HANDLEHELPER_H
#define I_HANDLEHELPER_H

#include <Base/Handle.h>


//----- Helper�錾
namespace EtherEngine {
    class HandleHelper {
    public:
        // �Q�ƃJ�E���g�n���h������Q�ƃn���h�����쐬����
        // @ Temp : �v�f�̌^
        // @ Ret  : �Q�ƃn���h��
        // @ Arg1 : �Q�ƃJ�E���g�n���h��
        template <HandleSystemConcept Type>
        static RefHandle<Type> GetRefHandle(const BaseHandle<Type>& handle);
    };
}




//----- Helper�錾
namespace EtherEngine {
    // �Q�ƃJ�E���g�n���h������Q�ƃn���h�����쐬����
    // @ Temp : �v�f�̌^
    // @ Ret  : �Q�ƃn���h��
    // @ Arg1 : �Q�ƃJ�E���g�n���h��
    template <HandleSystemConcept Type>
    RefHandle<Type> HandleHelper::GetRefHandle(const BaseHandle<Type>& handle) {
        return RefHandle<Type>(handle.GetHandleNumber());
    }
}


#endif // !I_HANDLEHELPER_H
