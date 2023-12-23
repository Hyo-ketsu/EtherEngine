#include <Base/ComponentHelper.h>


namespace EtherEngine {
    // コンポーネントの所属ゲームオブジェクト取得
    NativeGameObject* const ComponentHelper::GetParentObject(const ComponentBase& component) {
        //----- 変数宣言
        void* ret = nullptr;
        component.GetParentObject(&ret);
        return static_cast<NativeGameObject*>(ret);
    }
    // コンポーネントの所属ゲームオブジェクト取得
    NativeGameObject* const ComponentHelper::GetParentObject(const ComponentBase* const component) {
        //----- 変数宣言
        void* ret = nullptr;
        component->GetParentObject(&ret);
        return static_cast<NativeGameObject*>(ret);
    }
}
