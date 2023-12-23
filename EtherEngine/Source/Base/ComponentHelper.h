#ifndef I_COMPONENTHELPER_H
#define I_COMPONENTHELPER_H
#include <Base/NativeGameObject.h>


//----- ComponentHelper宣言
namespace EtherEngine {
    // Componentのヘルパー
    namespace ComponentHelper {
        // コンポーネントの所属ゲームオブジェクト取得
        // @ Ret  : 所属ゲームオブジェクト
        // @ Arg1 : 所属ゲームオブジェクトを取得したいコンポーネント
        NativeGameObject* const GetParentObject(const ComponentBase& component);
        // コンポーネントの所属ゲームオブジェクト取得
        // @ Ret  : 所属ゲームオブジェクト
        // @ Arg1 : 所属ゲームオブジェクトを取得したいコンポーネント
        NativeGameObject* const GetParentObject(const ComponentBase* const component);
    };
}


#endif // !I_COMPONENTHELPER_H
