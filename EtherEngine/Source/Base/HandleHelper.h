#ifndef I_HANDLEHELPER_H
#define I_HANDLEHELPER_H

#include <Base/Handle.h>


//----- Helper宣言
namespace EtherEngine {
    class HandleHelper {
    public:
        // HandleSystemに追加、要素を取得する
        // @ Temp1: 追加する要素の型
        // @ Temp2: 取得したハンドルが参照カウントを行うか
        // @ Ret  : 追加した要素のハンドル
        // @ Arg1 : 追加する要素
        template <HandleSystemConcept Type, HandleCountType Count = HandleCountType::Count>
        static Handle<Type, Count> AddItem(Type&& item);


        // 参照カウントハンドルから参照ハンドルを作成する
        // @ Temp : 要素の型
        // @ Ret  : 参照ハンドル
        // @ Arg1 : 参照カウントハンドル
        template <HandleSystemConcept Type>
        static RefHandle<Type> GetRefHandle(const Handle<Type>& handle);
    };
}




//----- Helper宣言
namespace EtherEngine {
    // HandleSystemに追加、要素を取得する
    // @ Temp1: 追加する要素の型
    // @ Temp2: 取得したハンドルが参照カウントを行うか
    // @ Ret  : 追加した要素のハンドル
    // @ Arg1 : 追加する要素
    template <HandleSystemConcept Type, HandleCountType Count>
    Handle<Type, Count> HandleHelper::AddItem(Type&& item) {
        return Handle<Type, Count>(HandleSystem<Type>::Get()->AddItem(std::move(item)));
    }


    // 参照カウントハンドルから参照ハンドルを作成する
    // @ Temp : 要素の型
    // @ Ret  : 参照ハンドル
    // @ Arg1 : 参照カウントハンドル
    template <HandleSystemConcept Type>
    RefHandle<Type> HandleHelper::GetRefHandle(const Handle<Type>& handle) {
        return RefHandle<Type>(handle.GetHandleNumberType());
    }
}


#endif // !I_HANDLEHELPER_H
