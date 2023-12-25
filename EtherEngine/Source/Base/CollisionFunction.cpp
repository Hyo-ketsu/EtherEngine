#include <Base/CollisionFunction.h>
#include <Base/ComponentHelper.h>
#include <Base/NativeGameObject.h>

#include <Base/CollisionSphere.h>
#include <Base/CollisionSphereXSphereFunction.h>


namespace {
    using CollSphere = EtherEngine::CollisionFunction::CollisionCheckData<EtherEngine::CollisionSphere>;
}


namespace EtherEngine {
    // 当たり判定を行う関数
    void AllCollisionCheck(std::vector<std::weak_ptr<CollisionComponent>> collisions) {
        //----- 衝突判定
        for (auto&& thisCollision : collisions) {
            //----- 判定チェック(ガード節)
            // コンポーネントを指す弱参照ポインタが無効なら判定しない
            if (thisCollision.expired()) continue;
            // コンポーネント自体が生きていないなら判定しない
            if (thisCollision.lock()->IsUnvalidObject()) continue;

            for (auto&& subjectCollision : collisions) {
                //----- 判定チェック(ガード節)
                // コンポーネントを指す弱参照ポインタが無効なら判定しない
                if (subjectCollision.expired()) continue;
                // コンポーネント自体が生きていないなら判定しない
                if (subjectCollision.lock()->IsUnvalidObject()) continue;
                // 自身の当たり判定とは判定しない
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
    // 当たり判定を行う関数
    void AllCollisionCheck(std::vector<std::weak_ptr<CollisionComponent>> thisCollisions, std::vector<std::weak_ptr<CollisionComponent>> subjectCollisions) {
        //----- 衝突判定
        for (auto&& thisCollision : thisCollisions) {
            //----- 判定チェック(ガード節)
            // コンポーネントを指す弱参照ポインタが無効なら判定しない
            if (thisCollision.expired()) continue;
            // コンポーネント自体が生きていないなら判定しない
            if (thisCollision.lock()->IsUnvalidObject()) continue;

            for (auto&& subjectCollision : subjectCollisions) {
                //----- 判定チェック(ガード節)
                // コンポーネントを指す弱参照ポインタが無効なら判定しない
                if (subjectCollision.expired()) continue;
                // コンポーネント自体が生きていないなら判定しない
                if (subjectCollision.lock()->IsUnvalidObject()) continue;
                // 自身の当たり判定とは判定しない
                if (thisCollision.lock()->GetId() == subjectCollision.lock()->GetId()) continue;

                //----- 当たり判定をとる
                auto result = CollisionCheck(thisCollision.lock(), subjectCollision.lock());

                //----- 衝突していたら追加する
                if (result.has_value()) {
                    // @ MEMO : 後でやる
                    //thisCollision.lock()->GetParentObject()->AddCollisionData(result.value());
                }
            }
        }
    }


    // 当たり判定をとる
    std::optional<CollisionHitData> CollisionCheck(std::shared_ptr<CollisionComponent> thisCollision, std::shared_ptr<CollisionComponent> subjectCollision) {
        // @ MEMO : 未実装
        return std::optional<CollisionHitData>();
    }
}
