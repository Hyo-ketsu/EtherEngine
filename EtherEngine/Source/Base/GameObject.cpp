#include <Base/GameObject.h>
#include <Base/GameObjectStorage.h>
#include <Base/CollisionHelper.h>


namespace EtherEngine {
    // コンストラクタ
    GameObject::GameObject(const Transform& transform, const std::string& name)
        : BaseObject(name)
        , m_transform(transform) {
    }


    // 更新処理を行う
    void GameObject::Update(void) {
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
    void GameObject::FixedUpdate(void) {
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
    void GameObject::Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
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
    void GameObject::Delete(void) {
        //----- アクティブチェック
        if (IsUnvalidObject()) return;

        for (auto& component : m_components) {
            component->CollisionStartFunction();
        }
        DeleteComponentsDelete();
    }
    // 衝突開始処理を行う
    void GameObject::CollisionStart(void) {
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
    void GameObject::CollisionEnd(void) {
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
    void GameObject::CollisionHit(void) {
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
    void GameObject::DeleteComponentsDelete(void) {
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
    const Transform& GameObject::GetLocalTransform(void) const {
        return m_transform;
    }
    // 相対座標セッター
    void GameObject::SetLocalTransform(const Transform& in) {
        m_transform = in;
    }


    // 衝突情報を削除・スタッキングする
    void GameObject::SidelineCollisionData(void) {
        m_oldHitData = std::move(m_hitData);
        m_hitData = decltype(m_hitData)();
    }
    // 衝突情報を追加する
    void GameObject::AddCollisionData(const CollisionHitData data) {
        m_hitData.push_back(data);
    }


    // 外部出力
    Json GameObject::Output(void) {
        //----- 変数宣言
        nlohmann::json json;

        //----- ゲームオブジェクト自身の情報出力
        json["GameObject"]["ID"] = 0;// GetId().Get();
        json["GameObject"]["Name"] = GetName().c_str();

        //----- コンポーネント出力
        for (auto& it : m_components) {
            json["GameObject"]["Components"][it->GetComponentName()] = it->Output();
            json["GameObject"]["Components"][it->GetComponentName()]["ComponentType"] = it->GetComponentTypeName();
        }
        //----- 描画コンポーネント出力
        for (auto& it : m_drawComponents) {
            json["GameObject"]["Components"][it->GetComponentName()] = it->Output();
            json["GameObject"]["Components"][it->GetComponentName()]["ComponentType"] = it->GetComponentTypeName();
        }
        //----- 当たり判定コンポーネント出力
        // @ MEMO : 現在は未実装
        //for (auto& it : m_collisions) {
        //    json["GameObject"]["Components"][it->GetComponentName()] = it->Output();
        //    json["GameObject"]["Components"][it->GetComponentName()]["ComponentType"] = it->GetComponentTypeName();
        //}

        //----- 返却
        return json;
    }
    // 外部入力
    void GameObject::Input(const Json& input) {
        //----- ゲームオブジェクト自身の情報取得
        // @ MEMO : IDは保留
        //this->SetId(json["GameObject"]["ID"])
        SetName(input["GameObject"]["Name"]);

        //----- コンポーネント入力
        for (auto& it : input["GameObject"]["Components"]) {
            //----- タイプに沿ったコンポーネント生成
            std::string type = input["GameObject"]["Components"]["ComponentType"];
            
            do {
                //----- 通常コンポーネント生成
                // @ MEMO : ここをのちにAddComponentに換装？
                if (type == Component::TYPE_COMPONENT) {
                    m_components.push_back(ms_getComponent(this, type));
                    m_components.back()->Input(it);
                    break;
                }
                //----- 描画コンポーネント生成
                if (type == Component::TYPE_DRAW_COMPONENT) {
                    m_drawComponents.push_back(ms_getDrawComponent(this, type));
                    m_drawComponents.back()->Input(it);
                    break;
                }
                //----- 当たり判定コンポーネント生成
                // @ MEMO : 後回し
                //if (type == Component::TYPE_DRAW_COMPONENT) {
                //    m_collisions.push_back(std::make_shared<CollisionComponent>(CollisionComponent<>()));
                //}
            } while (false);
        }
    }


    std::function<std::shared_ptr<ComponentBase>&&(GameObject*, const std::string&)> GameObject::ms_getComponent = nullptr; // C++CLIのGameComponentなどを取得するためのラムダ
    std::function<std::shared_ptr<DrawComponent>&&(GameObject*, const std::string&)> GameObject::ms_getDrawComponent = nullptr; // C++CLIのGameDrawComponentなどを取得するためのラムダ
}
