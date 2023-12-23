#ifndef I_COLLISIONHELPER_H
#define I_COLLISIONHELPER_H
#include <Base/CollisionBase.h>
#include <Base/NativeGameObject.h>


//----- CollisionHelper 宣言
namespace EtherEngine {
    class CollisionHelper {
    public:
        CollisionHelper(void) = delete;


        // 衝突対象ゲームオブジェクト取得
        // @ Ret  : 衝突対象ゲームオブジェクト
        // @ Arg1 : 衝突対象ゲームオブジェクトを取得したいコンポーネント
        static NativeGameObject* const GetParentObject(const CollisionHitData& hitData);
        // 衝突対象ゲームオブジェクト取得
        // @ Ret  : 衝突対象ゲームオブジェクト
        // @ Arg1 : 衝突対象ゲームオブジェクトを取得したいコンポーネント
        static NativeGameObject* const GetParentObject(const CollisionHitData* const hitData);
    };
}


#endif // !I_COLLISIONHELPER_H
