#include <Base/CollisionFunction.h>
#include <Base/ComponentHelper.h>


namespace EtherEngine {
    // 当たり判定を行う関数
    void AllCollisionCheck(std::vector<std::weak_ptr<CollisionComponent>> collisions) {
        //----- 衝突判定
        for (auto&& thisCollision : collisions) {
            //----- コンポーネントが有効か
            if (thisCollision.expired()) continue;

            for (auto&& subjectCollision : collisions) {
                //----- コンポーネントが有効か
                if (subjectCollision.expired()) continue;

                //----- 自身の当たり判定とは当たり判定を取らない 
                if (thisCollision.lock()->GetId() == subjectCollision.lock()->GetId()) continue;

                //----- 当たり判定をとる
                auto result = CollisionCheck(thisCollision.lock(), subjectCollision.lock());

                //----- 衝突していたら追加する
                if (result.has_value()) {
                    thisCollision.lock()->AccessCollisionHitData().push_back(result.value());
                }
            }
        }
    }


    // 当たり判定をとる
    std::optional<CollisionHitData> CollisionCheck(std::shared_ptr<CollisionComponent> thisCollision, std::shared_ptr<CollisionComponent> subjectCollision) {
        // @ MEMO : 実装途中
        return std::optional<CollisionHitData>();
    }
}
