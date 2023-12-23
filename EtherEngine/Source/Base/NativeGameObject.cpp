#include <Base/NativeGameObject.h>
#include <Base/GameObjectStorage.h>
#include <Base/CollisionHelper.h>


namespace EtherEngine {
    // コンストラクタ
    NativeGameObject::NativeGameObject(const Transform& transform, const std::string& name)
        : NativeBaseObject(name)
        , m_transform(transform) {
    }


    // 更新処理を行う
    void NativeGameObject::Update(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        //----- 通常コンポーネントの更新処理
        for (auto& component : m_components) {
            component->UpdateFuntion();
        }
        DeleteComponentsDelete();

        //----- 描画コンポーネントの更新処理
        for (auto& component : m_drawComponents) {
            component->UpdateFuntion();
        }
        DeleteComponentsDelete();
    }
    // 物理更新処理を行う
    void NativeGameObject::FixedUpdate(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        //----- 通常コンポーネントの物理更新処理
        for (auto& component : m_components) {
            component->FixedUpdateFunction();
        }
        DeleteComponentsDelete();

        //----- 描画コンポーネントの物理更新処理
        for (auto& component : m_drawComponents) {
            component->FixedUpdateFunction();
        }
        DeleteComponentsDelete();
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
    // 削除時処理を行う
    void NativeGameObject::Delete(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        for (auto& component : m_components) {
            component->DeleteFuntion();
        }
        DeleteComponentsDelete();
    }
    // 衝突開始処理を行う
    void NativeGameObject::CollisionStart(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        //----- 変数宣言
        std::vector<CollisionHitData> hitDatas; // タイミングにあった衝突判定

        //----- データ判定
        for (auto&& hitData : m_hitData) {
            bool isNewOldHit = false;
            for (auto&& oldHitData : m_oldHitData) {
                //----- 過去と現在に衝突している( = Hit)なのでスルーする
                if (CollisionHelper::GetParentObject(hitData)->GetId() == CollisionHelper::GetParentObject(oldHitData)->GetId()) {
                    isNewOldHit = true;
                    break;
                }
            }

            if (isNewOldHit == false) hitDatas.push_back(hitData);
        }

        //----- データが空であれば何もしない
        if (hitDatas.empty()) return;

        //----- コンポーネントに情報を与える
        for (auto& component : m_components) {
            component->SetCollisionHitData(hitDatas);
        }

        //----- 処理を行う
        for (auto& component : m_components) {
            component->CollisionStartFunction();
        }
        DeleteComponentsDelete();
    }
    // 衝突終了処理を行う
    void NativeGameObject::CollisionEnd(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        //----- 変数宣言
        std::vector<CollisionHitData> hitDatas; // タイミングにあった衝突判定

        //----- データ判定
        for (auto&& oldHitData : m_oldHitData) {
            bool isNewOldHit = false;
            for (auto&& hitData : m_hitData) {
                //----- 過去と現在に衝突している( = Hit)なのでスルーする
                if (CollisionHelper::GetParentObject(oldHitData)->GetId() == CollisionHelper::GetParentObject(hitData)->GetId()) {
                    isNewOldHit = true;
                    break;
                }
            }

            if (isNewOldHit == false) hitDatas.push_back(oldHitData);
        }

        //----- データが空であれば何もしない
        if (hitDatas.empty()) return;

        //----- コンポーネントに情報を与える
        for (auto& component : m_components) {
            component->SetCollisionHitData(hitDatas);
        }

        for (auto& component : m_components) {
            component->CollisionEndFunction();
        }
        DeleteComponentsDelete();
    }
    // 衝突処理を行う
    void NativeGameObject::CollisionHit(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        //----- 変数宣言
        std::vector<CollisionHitData> hitDatas; // タイミングにあった衝突判定

        //----- データ判定
        for (auto&& hitData : m_hitData) {
            for (auto&& oldHitData : m_oldHitData) {
                //----- 過去と現在に衝突しているのでそれを代入する
                if (CollisionHelper::GetParentObject(hitData)->GetId() == CollisionHelper::GetParentObject(oldHitData)->GetId()) {
                    hitDatas.push_back(hitData);
                    break;
                }
            }
        }

        //----- データがからであれば何もしない
        if (hitDatas.empty()) return;

        //----- コンポーネントに情報を与える
        for (auto& component : m_components) {
            component->SetCollisionHitData(hitDatas);
        }

        for (auto& component : m_components) {
            component->CollisionHitFunction();
        }
        DeleteComponentsDelete();
    }


    // 削除されたコンポーネントを削除する
    void NativeGameObject::DeleteComponentsDelete(void) {
        for (auto it = m_components.begin(); it != m_components.end();) {
            //----- 削除するか
            if ((*it)->GetDelete()) {
                //----- 削除されてる。削除
                it = m_components.erase(it);
            }
            else {
                it++;
            }
        }
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


    std::function<std::shared_ptr<ComponentBase>(NativeGameObject*, const std::string&)> NativeGameObject::ms_getComponent = nullptr; // C++CLIのGameComponentなどを取得するためのラムダ
    std::function<std::shared_ptr<ComponentBase>(NativeGameObject*)> NativeGameObject::ms_addComponentMenu = nullptr; // C++CLIのGameDrawComponentなどを取得するためのラムダ
    std::function<std::string(const std::string&, const uint, const bool)> NativeGameObject::ms_getFullName = nullptr; // 各コンポーネント名の完全修飾名取得ラムダ
}
