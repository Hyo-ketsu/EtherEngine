#include <Base/NativeGameObject.h>
#include <Base/NativeGameObjectStorage.h>
#include <Base/CollisionHelper.h>


namespace EtherEngine {
    // コンストラクタ
    NativeGameObject::NativeGameObject(const Transform& transform, const std::string& name)
        : NativeBaseObject(name)
        , m_transform(transform) {
    }


    // 描画処理を行う
    void NativeGameObject::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        //----- 描画コンポーネントの描画処理
        for (auto& component : m_drawComponents) {
            component->SetView(view);
            component->SetProjection(projection);
            component->DrawFuntion();
        }
        DeleteComponentsDelete();
    }


    // 削除されたコンポーネントを削除する
    void NativeGameObject::DeleteComponentsDelete(void) {
        for (auto it = m_drawComponents.begin(); it != m_drawComponents.end();) {
            //----- 削除するか
            if ((*it)->GetDelete()) {
                //----- 削除されてる。削除
                it = m_drawComponents.erase(it);
            }
            else {
                it++;
            }
        }
        for (auto it = m_collisions.begin(); it != m_collisions.end();) {
            //----- 削除するか
            if ((*it)->GetDelete()) {
                //----- 削除されてる。削除
                it = m_collisions.erase(it);
            }
            else {
                it++;
            }
        }
    }


    // 相対座標ゲッター
    const Transform& NativeGameObject::GetLocalTransform(void) const {
        return m_transform;
    }
    // 相対座標セッター
    void NativeGameObject::SetLocalTransform(const Transform& in) {
        m_transform = in;
    }


    // 衝突情報を削除・スタッキングする
    void NativeGameObject::SidelineCollisionData(void) {
        m_oldHitData = std::move(m_hitData);
        m_hitData = decltype(m_hitData)();
    }
    // 衝突情報を追加する
    void NativeGameObject::AddCollisionData(const CollisionHitData data) {
        m_hitData.push_back(data);
    }
}
