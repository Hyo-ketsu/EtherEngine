#ifndef I_COMPONENTHELPER_H
#define I_COMPONENTHELPER_H
#include <Base/GameObject.h>
#include <Base/ComponentBase.h>


//----- ComponentHelper宣言
namespace EtherEngine {
    // Componentのヘルパー
    class ComponentHelper {
    public:
        ComponentHelper(void) = delete;


        // コンポーネントの所属ゲームオブジェクト取得
        // @ Ret  : 所属ゲームオブジェクト
        // @ Arg1 : 所属ゲームオブジェクトを取得したいコンポーネント
        static GameObject* const GetParentObject(const ComponentBase& component);
        // コンポーネントの所属ゲームオブジェクト取得
        // @ Ret  : 所属ゲームオブジェクト
        // @ Arg1 : 所属ゲームオブジェクトを取得したいコンポーネント
        static GameObject* const GetParentObject(const ComponentBase* const component);
    };
}


#endif // !I_COMPONENTHELPER_H
