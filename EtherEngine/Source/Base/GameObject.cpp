#include <Base/GameObject.h>
#include <Base/GameObjectStorage.h>
#include <Base/CollisionHelper.h>
#include <ImGUI/ImGUIWrapFunction.h>


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
            component->DeleteFuntion();
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


    // コンポーネント追加
    std::weak_ptr<ComponentBase> GameObject::AddComponent(const std::string& componentTypeName) {
        //----- コンポーネント生成
        auto component = ms_getComponent(this, componentTypeName);
        if (component == nullptr) return std::weak_ptr<ComponentBase>();

        //----- 通常コンポーネント生成
        if (component->GetComponentTypeName() == Component::TYPE_COMPONENT) {
            m_components.push_back(component);
            return std::weak_ptr<ComponentBase>(component);
        }
        //----- 描画コンポーネント生成
        if (component->GetComponentTypeName() == Component::TYPE_DRAW_COMPONENT) {
            auto drawComponent = std::dynamic_pointer_cast<DrawComponent>(component);
            m_drawComponents.push_back(drawComponent);
            return std::weak_ptr<ComponentBase>(drawComponent);
        }
        //----- 当たり判定コンポーネント生成
        // @ MEMO : 後回し
        //if (type == Component::TYPE_DRAW_COMPONENT) {
        //    m_collisions.push_back(std::make_shared<CollisionComponent>(CollisionComponent<>()));
        //}

        return std::weak_ptr<ComponentBase>();
    }
    // コンポーネント削除
    bool GameObject::DeleteComponent(const std::string& componentTypeName) {
        //----- 各コンポーネントから走査、削除
        for (auto&& it : m_components) {
            if (it->GetComponentName() == componentTypeName) {
                it->DeleteFuntion();
                it->DeleteObject();
                return true;
            }
        }
        for (auto&& it : m_drawComponents) {
            if (it->GetComponentName() == componentTypeName) {
                it->DeleteFuntion();
                it->DeleteObject();
                return true;
            }
        }
        for (auto&& it : m_collisions) {
            if (it->GetComponentName() == componentTypeName) {
                it->DeleteFuntion();
                it->DeleteObject();
                return true;
            }
        }

        return false;
    }
    // コンポーネントを取得する
    std::weak_ptr<ComponentBase> GameObject::GetComponent(const std::string& componentTypeName, uint index) {
        //----- 各コンポーネントから走査、取得
        for (auto&& it : m_components) {
            if (it->GetComponentName() == componentTypeName) {
                return std::weak_ptr<ComponentBase>(it);
            }
        }
        for (auto&& it : m_drawComponents) {
            if (it->GetComponentName() == componentTypeName) {
                return std::weak_ptr<ComponentBase>(it);
            }
        }
        for (auto&& it : m_collisions) {
            if (it->GetComponentName() == componentTypeName) {
                return std::weak_ptr<ComponentBase>(it);
            }
        }

        return std::weak_ptr<ComponentBase>();
    }
    // コンポーネントを取得する
    std::vector<std::weak_ptr<ComponentBase>> GameObject::GetComponents(const std::string& componentTypeName) {
        //----- 変数宣言
        std::vector<std::weak_ptr<ComponentBase>> ret;

        //----- コンポーネントが取得できなくなるまで取得
        for (uint i = 0;; i++) {
            auto component = GetComponent(componentTypeName);
            if (component.expired()) {
                break;
            }
            else {
                ret.push_back(component);
            }
        }

        //----- 返却
        return ret;
    }


    // 外部出力
    Json GameObject::Output(void) {
        //----- 変数宣言
        nlohmann::json json;

        //----- ゲームオブジェクト自身の情報出力
        json["GameObject"]["ID"] = GetId().Get();
        json["GameObject"]["Name"] = GetName().c_str();

        //----- コンポーネント出力
        auto components = nlohmann::json::array();
        for (auto& it : m_components) {
            components.push_back(it->Output());
        }
        //----- 描画コンポーネント出力
        for (auto& it : m_drawComponents) {
            components.push_back(it->Output());
        }
        //----- 当たり判定コンポーネント出力
        // @ MEMO : 現在は未実装
        //for (auto& it : m_collisions) {
        //    components[it->GetComponentName()] = it->Output();
        //    components[it->GetComponentName()]["ComponentType"] = it->GetComponentTypeName();
        //}

        //----- 配列出力
        json["GameObject"]["Components"] = components;

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
        auto hoge = input["GameObject"]["Components"].dump(2);
        if (input["GameObject"].contains("Components") == false) goto NO_CREATE_COMPONENT;
        for (auto& it : input["GameObject"]["Components"].items()) {            
            //----- コンポーネント生成
            auto ret = AddComponent(it.value()["ComponentName"]);
            if (ret.expired()) continue;
            
            //----- 入力値入力
            ret.lock()->Input(it.value());
        }

        NO_CREATE_COMPONENT: {}
    }


    // Inspector表示
    void GameObject::ShowInspector(void) {
        //----- 名前表示
        ImGuiFunction::ImGuiShow(this->AccessName(), "Name");

        //----- 各コンポーネント表示
        for (auto&& it : m_components) {
            ImGui::Text(it->GetName().c_str());
            it->ShowInspector();
        }
        for (auto&& it : m_drawComponents) {
            ImGui::Text(it->GetName().c_str());
            it->ShowInspector();
        }
        for (auto&& it : m_collisions) {
            ImGui::Text(it->GetName().c_str());
            it->ShowInspector();
        }

        //----- コンポーネント追加ボタン
        if (ImGui::Button("Add Component")) {
            ImGui::OpenPopup("AddComponent Popup");
        }

        //----- コンポーネント追加ボタンメニュー表示
        if (ImGui::BeginPopup("AddComponent Popup")) {
            //----- メニュー表示
            auto component = ms_addComponentMenu(this);

            //----- コンポーネント追加
            if (component != nullptr) {
                if (component->GetComponentTypeName() == Component::TYPE_COMPONENT) {
                    m_components.push_back(component);
                } 
                else if (component->GetComponentTypeName() == Component::TYPE_DRAW_COMPONENT) {
                    auto drawComponent = std::dynamic_pointer_cast<DrawComponent>(component);
                    m_drawComponents.push_back(drawComponent);
                }
                else if (component->GetComponentTypeName() == Component::TYPE_COLLISION_COMPONENT) {
                    auto collisionComponent = std::dynamic_pointer_cast<CollisionComponent>(component);
                    m_collisions.push_back(collisionComponent);
                }
            }

            //----- メニュー表示終了
            ImGui::EndPopup();
        }
    }


    std::function<std::shared_ptr<ComponentBase>(GameObject*, const std::string&)> GameObject::ms_getComponent = nullptr; // C++CLIのGameComponentなどを取得するためのラムダ
    std::function<std::shared_ptr<ComponentBase>(GameObject*)> GameObject::ms_addComponentMenu; // C++CLIのGameDrawComponentなどを取得するためのラムダ
    std::function<std::string(const std::string&, const uint, const bool)> GameObject::ms_getFullName; // 各コンポーネント名の完全修飾名取得ラムダ
}
