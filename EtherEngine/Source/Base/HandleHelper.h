#ifndef I_HANDLEHELPER_H
#define I_HANDLEHELPER_H

#include <Base/Handle.h>


//----- Helper�錾
namespace EtherEngine {
    class HandleHelper {
    public:
        // HandleSystem�ɒǉ��A�v�f���擾����
        // @ Temp1: �ǉ�����v�f�̌^
        // @ Temp2: �擾�����n���h�����Q�ƃJ�E���g���s����
        // @ Ret  : �ǉ������v�f�̃n���h��
        // @ Arg1 : �ǉ�����v�f
        template <HandleSystemConcept Type, HandleCountType Count = HandleCountType::Count>
        static Handle<Type, Count> AddItem(Type&& item);


        // �Q�ƃJ�E���g�n���h������Q�ƃn���h�����쐬����
        // @ Temp : �v�f�̌^
        // @ Ret  : �Q�ƃn���h��
        // @ Arg1 : �Q�ƃJ�E���g�n���h��
        template <HandleSystemConcept Type>
        static RefHandle<Type> GetRefHandle(const Handle<Type>& handle);
    };
}




//----- Helper�錾
namespace EtherEngine {
    // HandleSystem�ɒǉ��A�v�f���擾����
    // @ Temp1: �ǉ�����v�f�̌^
    // @ Temp2: �擾�����n���h�����Q�ƃJ�E���g���s����
    // @ Ret  : �ǉ������v�f�̃n���h��
    // @ Arg1 : �ǉ�����v�f
    template <HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count> HandleHelper::AddItem(Type&& item) {
        return Handle<Type, Count>(HandleSystem<Type>::Get()->AddItem(std::move(item)));
    }


    // �Q�ƃJ�E���g�n���h������Q�ƃn���h�����쐬����
    // @ Temp : �v�f�̌^
    // @ Ret  : �Q�ƃn���h��
    // @ Arg1 : �Q�ƃJ�E���g�n���h��
    template <HandleSystemConcept Type>
    RefHandle<Type> HandleHelper::GetRefHandle(const Handle<Type>& handle) {
        return RefHandle<Type>(handle.GetHandleNumberType());
    }
}


#endif // !I_HANDLEHELPER_H
