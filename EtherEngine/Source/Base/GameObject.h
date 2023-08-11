#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/BaseDefines.h>
#include <Base/BaseObject.h>
#include <Base/ComponentBase.h>
#include <Base/ComponentHelper.h>
#include <Base/CollisionComponent.h>
#include <Base/ConceptUtility.h>
#include <Base/DrawComponent.h> 
#include <Base/HandleHelper.h>
#include <Base/Handle.h>
#include <Base/Transform.h>
#include <Base/Scene.h>
#include <Base/ParentAndChildObject.h>
#include <Base/EtherEngineUtility.h>


//----- GameObject 宣言
namespace EtherEngine {
    // シーン上のゲームを構成するオブジェクトを表現する
    class GameObject : public BaseObject, public IInOuter {
    public:
        // 更新処理を行う
        void Update(void);
        // 物理更新処理を行う
        void FixedUpdate(void);
        // 描画処理を行う
        void Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection);
        // 削除時処理を行う
        void Delete(void);
        // 衝突開始処理を行う
        void CollisionStart(void);
        // 衝突終了処理を行う
        void CollisionEnd(void);
        // 衝突処理を行う
        void CollisionHit(void);


        // 座標ゲッター
        // @ Ret  : 絶対座標
        const Transform& GetTransform(void) const { return m_transform; }
        // 座標セッター
        // @ Arg1 : 絶対座標
        void SetTransform(const Transform& in) { m_transform = in; }
        // 座標アクセサー
        // @ Ret  : 絶対座標
        Transform& AccessTransform(void) { return m_transform; }

        // 相対座標ゲッター
        // @ MEMO : 未実装
        // @ Ret  : 相対座標
        const Transform& GetLocalTransform(void) const;
        // 相対座標セッター
        // @ MEMO : 未実装
        // @ Arg1 : 相対座標
        void SetLocalTransform(const Transform& in);


        // シーン情報ゲッター
        const SceneData& GetScene(void) const { return m_scene; }
        // シーン情報セッター
        void SetScene(const SceneData& in) { m_scene = in; }

        // 親子関係ゲッター
        const ParentAndChildObject<GameObject> GetParentAndChild(void) const { return m_parentAndChild; }
        // 親子関係セッター
        void SetParentAndChild(const ParentAndChildObject<GameObject>& in) { m_parentAndChild = in; }
        // 親子関係アクセサー
        ParentAndChildObject<GameObject>& AccessParentAndChild(void) { return m_parentAndChild; }


        // ハンドルゲッター
        const BaseHandle<GameObject>& GetHandle(void) const { return m_handle; }


        // 衝突情報を削除・スタッキングする
        void SidelineCollisionData(void);
        // 衝突情報を追加する
        // @ Arg1 : 追加する当たり判定情報
        void AddCollisionData(const CollisionHitData data);


        // コンポーネント追加
        // @ Temp1: 追加するコンポーネントの型
        // @ Temps: 追加コンポーネントのコンストラクタに使用する引数
        // @ Args : 追加コンポーネントのコンストラクタに使用する引数
        template <Concept::SubClassOnly<ComponentBase> ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddComponent(ArgsType&& ...args);
        // コンポーネント削除
        // @ Temp : 削除するコンポーネントの型
        // @ Ret  : 削除したか
        template <Concept::SubClassOnly<ComponentBase> ComponentType>
        bool DeleteComponent(void);
        // コンポーネントを取得する
        // @ Temp : 取得するコンポーネント型(ComponentBaseは使用不可)
        // @ Ret  : 取得したコンポーネント
        // @ Arg1 : 何番目のコンポーネントを使用するか(Default : 0)
        template <Concept::SubClassOnly<ComponentBase> ComponentType>
        std::weak_ptr<ComponentType> GetComponent(uint index = 0);
        // コンポーネントを複数取得する
        // @ Temp : 取得するコンポーネント型(ComponentBaseは使用不可)
        // @ Ret  : 取得したコンポーネント（複数）
        template <Concept::SubClassOnly<ComponentBase> ComponentType>
        std::vector<std::weak_ptr<ComponentType>> GetComponents(void);


        // 外部出力
        Json Output(void) override;
        // 外部入力
        void Input(const Json& input) override;

    protected:
        // コンストラクタ
        // @ Arg1 : 座標
        // @ Arg2 : オブジェクト名(Default : GameObject)
        GameObject(const Transform& transform, const std::string& name = "GameObject");

    private:
        // 削除されたコンポーネントを削除する
        void DeleteComponentsDelete(void);


        friend class GameObjectStorage;
        friend class CPPCLI;

        Transform m_transform;  // 座標
        SceneData m_scene;      // 現在所属シーン
        BaseHandle<GameObject> m_handle;    // 自身のハンドル
        ParentAndChildObject<GameObject> m_parentAndChild;  // このゲームオブジェクトの親子関係
        std::vector<std::shared_ptr<ComponentBase>> m_components;     // 通常のコンポーネント
        std::vector<std::shared_ptr<CollisionComponent>> m_collisions;// 当たり判定コンポーネント
        std::vector<std::shared_ptr<DrawComponent>> m_drawComponents; // 描画コンポーネント
        std::vector<CollisionHitData> m_hitData;     // 保持しているそのフレームの当たり判定情報
        std::vector<CollisionHitData> m_oldHitData;  // 保持している前フレームの当たり判定情報

        static std::function<std::shared_ptr<ComponentBase>&&(GameObject*, const std::string&)> ms_getComponent; // C++CLIのGameComponentなどを取得するためのラムダ
        static std::function<std::shared_ptr<DrawComponent>&&(GameObject*, const std::string&)> ms_getDrawComponent; // C++CLIのGameDrawComponentなどを取得するためのラムダ
    };
}




//----- GameObject 定義
namespace EtherEngine {
    // コンポーネント追加
    // @ Temp1: 追加するコンポーネントの型
    // @ Temps: 追加コンポーネントのコンストラクタに使用する引数
    // @ Args : 追加コンポーネントのコンストラクタに使用する引数
    template <Concept::SubClassOnly<ComponentBase> ComponentType, typename ...ArgsType>
    std::weak_ptr<ComponentType> GameObject::AddComponent(ArgsType&& ...args) {
        //----- 警告表示
        static_assert((std::is_constructible_v<ComponentType, GameObject*, ArgsType...>), "Error! AddComponent Args");

        //----- 生成
        auto ptr = std::make_shared<ComponentType>(this, args...);

        //----- 追加
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            m_drawComponents.push_back(ptr);
        }
        else if constexpr (Concept::BaseOfConcept<ComponentType, CollisionComponent>) {
            m_collisions.push_back(ptr);
        } else {
            m_components.push_back(ptr);
        }

        //----- 返却
        return std::weak_ptr<ComponentType>(ptr);
    }
    // コンポーネント削除
    // @ Temp : 削除するコンポーネントの型
    // @ Ret  : 削除したか
    template <Concept::SubClassOnly<ComponentBase> ComponentType>
    bool GameObject::DeleteComponent(void) {
        //------ 捜索
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            for (auto& component : m_drawComponents) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- 削除
                    component->DeleteFuntion();
                    component->SetDelete(true);
                }
            }
        }
        else if constexpr (Concept::BaseOfConcept<ComponentType, CollisionComponent>) {
            for (auto& component : m_collisions) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- 削除
                    component->DeleteFuntion();
                    component->SetDelete(true);
                }
            }
        }
        else {
            for (auto& component : m_components) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- 削除
                    component->DeleteFuntion();
                    component->SetDelete(true);
                }
            }
        }
    }
    // コンポーネントを取得する
    // @ Temp : 取得するコンポーネント型(ComponentBaseは使用不可)
    // @ Ret  : 取得したコンポーネント
    // @ Arg1 : 何番目のコンポーネントを使用するか(Default : 0)
    template <Concept::SubClassOnly<ComponentBase> ComponentType>
    std::weak_ptr<ComponentType> GameObject::GetComponent(uint index) {
        //----- 取得
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            for (auto& component : m_drawComponents) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- 指定番号か
                    if (index != 0) {
                        //----- 指定の番号まで達していない。番号を1削減して取得を継続する
                        index--;
                        continue;
                    }

                    //----- 返却
                    return std::weak_ptr<ComponentType>(component);
                }
            }
        }
        else if constexpr (Concept::BaseOfConcept<ComponentType, CollisionComponent>) {
            for (auto& component : m_collisions) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- 指定番号か
                    if (index != 0) {
                        //----- 指定の番号まで達していない。番号を1削減して取得を継続する
                        index--;
                        continue;
                    }

                    //----- 返却
                    return std::weak_ptr<ComponentType>(component);
                }
            }
        }
        else {
            for (auto& component : m_components) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- 指定番号か
                    if (index != 0) {
                        //----- 指定の番号まで達していない。番号を1削減して取得を継続する
                        index--;
                        continue;
                    }

                    //----- 返却
                    return std::weak_ptr<ComponentType>(component);
                }
            }
        }

        //----- 無効値返却
        return std::weak_ptr<ComponentType>();
    }
    // コンポーネントを複数取得する
    // @ Temp : 取得するコンポーネント型(ComponentBaseは使用不可)
    // @ Ret  : 取得したコンポーネント（複数）
    template <Concept::SubClassOnly<ComponentBase> ComponentType>
    std::vector<std::weak_ptr<ComponentType>> GameObject::GetComponents(void) {
        //----- 返却用変数宣言
        std::vector<std::weak_ptr<ComponentType>> ret;

        //----- 取得
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            for (auto& component : m_drawComponents) {
                if (dynamic_cast<ComponentType*>(component.get()) != nullptr) {
                    //----- 返却用変数に追加
                    ret.push_back(std::weak_ptr<ComponentType>(component));
                }
            }
        }
        else if constexpr (Concept::BaseOfConcept<ComponentType, CollisionComponent>) {
            for (auto& component : m_collisions) {
                if (dynamic_cast<ComponentType*>(component.get()) != nullptr) {
                    //----- 返却用変数に追加
                    ret.push_back(std::weak_ptr<ComponentType>(component));
                }
            }
        }
        else {
            for (auto& component : m_components) {
                if (dynamic_cast<ComponentType*>(component.get()) != nullptr) {
                    //----- 返却用変数に追加
                    ret.push_back(std::weak_ptr<ComponentType>(component));
                }
            }
        }

        //----- 返却
        return ret;
    }
}

#endif
