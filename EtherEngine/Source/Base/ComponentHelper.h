#ifndef I_COMPONENTHELPER_H
#define I_COMPONENTHELPER_H
#include <Base/GameObject.h>


//----- ComponentHelper宣言
namespace EtherEngine {
    // Componentのヘルパー
    namespace ComponentHelper {
        // コンポーネントの所属ゲームオブジェクト取得
        // @ Ret  : 所属ゲームオブジェクト
        // @ Arg1 : 所属ゲームオブジェクトを取得したいコンポーネント
        GameObject* const GetParentObject(const ComponentBase& component);
        // コンポーネントの所属ゲームオブジェクト取得
        // @ Ret  : 所属ゲームオブジェクト
        // @ Arg1 : 所属ゲームオブジェクトを取得したいコンポーネント
        GameObject* const GetParentObject(const ComponentBase* const component);
    };
}


#endif // !I_COMPONENTHELPER_H
