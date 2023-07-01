#include <Base/ComponentHelper.h>


namespace EtherEngine {
    // コンポーネントの所属ゲームオブジェクト取得
    GameObject* const ComponentHelper::GetParentObject(const ComponentBase& component) {
        //----- 変数宣言
        void* ret = nullptr;
        component.GetParentObject(&ret);
        return static_cast<GameObject*>(ret);
    }
    // コンポーネントの所属ゲームオブジェクト取得
    GameObject* const ComponentHelper::GetParentObject(const ComponentBase* const component) {
        //----- 変数宣言
        void* ret = nullptr;
        component->GetParentObject(&ret);
        return static_cast<GameObject*>(ret);
    }
}
