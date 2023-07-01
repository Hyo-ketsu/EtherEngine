#ifndef I_HANDLEHELPER_H
#define I_HANDLEHELPER_H

#include <Base/Handle.h>


//----- Helper宣言
namespace EtherEngine {
    class HandleHelper {
    public:
        // 参照カウントハンドルから参照ハンドルを作成する
        // @ Temp : 要素の型
        // @ Ret  : 参照ハンドル
        // @ Arg1 : 参照カウントハンドル
        template <HandleSystemConcept Type>
        static RefHandle<Type> GetRefHandle(const BaseHandle<Type>& handle);
    };
}




//----- Helper宣言
namespace EtherEngine {
    // 参照カウントハンドルから参照ハンドルを作成する
    // @ Temp : 要素の型
    // @ Ret  : 参照ハンドル
    // @ Arg1 : 参照カウントハンドル
    template <HandleSystemConcept Type>
    RefHandle<Type> HandleHelper::GetRefHandle(const BaseHandle<Type>& handle) {
        return RefHandle<Type>(handle.GetHandleNumber());
    }
}


#endif // !I_HANDLEHELPER_H
