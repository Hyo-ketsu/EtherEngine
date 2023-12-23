#include <Base/CollisionHelper.h>


//----- CollisionHelper 定義
namespace EtherEngine {
    // 衝突対象ゲームオブジェクト取得
    // @ Ret  : 衝突対象ゲームオブジェクト
    // @ Arg1 : 衝突対象ゲームオブジェクトを取得したいコンポーネント
    NativeGameObject* const CollisionHelper::GetParentObject(const CollisionHitData& hitData) {
        void* ret = nullptr;
        hitData.GetHitTarget(&ret);
        return static_cast<NativeGameObject*>(ret);
    }
    // 衝突対象ゲームオブジェクト取得
    // @ Ret  : 衝突対象ゲームオブジェクト
    // @ Arg1 : 衝突対象ゲームオブジェクトを取得したいコンポーネント
    NativeGameObject* const CollisionHelper::GetParentObject(const CollisionHitData* const hitData) {
        return GetParentObject(*hitData);
    }
}
