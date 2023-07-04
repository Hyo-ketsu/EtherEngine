#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
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


//----- GameObject 宣言
namespace EtherEngine {
    // シーン上のゲームを構成するオブジェクトを表現する
    class GameObject : public BaseObject {
    public:
        // 更新処理を行う
        void Update(void);
        // 描画処理を行う
        void Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection);
        // 削除時処理を行う
        void Delete(void);


        // 座標ゲッター
        const Transform& GetTransform(void) const { return m_transform; }
        // 座標セッター
        void SetTransform(const Transform& in) { m_transform = in; }
        // 座標アクセサー
        Transform& AccessTransform(void) { return m_transform; }


        // ハンドルゲッター
        const BaseHandle<GameObject>& GetHandle(void) const { return m_handle; }


        // コンポーネント追加
        // @ Temp1: 追加するコンポーネントの型
        // @ Temps: 追加コンポーネントのコンストラクタに使用する引数
        // @ Args : 追加コンポーネントのコンストラクタに使用する引数
        template <Concept::BaseOfConcept<ComponentBase> ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddConponent(ArgsType&& ...args);
        // コンポーネント削除
        // @ Temp : 削除するコンポーネントの型
        // @ Ret  : 削除したか
        template <Concept::BaseOfConcept<ComponentBase> ComponentType>
        bool DeleteComponent(void);
        // コンポーネントを取得する
        // @ Temp : 取得するコンポーネント型(ComponentBaseは使用不可)
        // @ Ret  : 取得したコンポーネント
        template <typename ComponentType>
            requires Concept::BaseOfConcept<ComponentType, ComponentBase> && Concept::NotSameConcept<ComponentBase, ComponentType>
        std::weak_ptr<ComponentBase> GetComponent(void);
        // コンポーネントを複数取得する
        // @ Temp : 取得するコンポーネント型(ComponentBaseは使用不可)
        // @ Ret  : 取得したコンポーネント（複数）
        template <typename ComponentType>
            requires Concept::BaseOfConcept<ComponentType, ComponentBase> && Concept::NotSameConcept<ComponentBase, ComponentType>
        std::vector<std::weak_ptr<ComponentBase>> GetComponents(void);

    protected:
        // コンストラクタ
        // @ Arg1 : 座標
        // @ Arg2 : オブジェクト名(Default : GameObject)
        GameObject(const Transform& transform, const std::string& name = "GameObject");

    private:
        // 削除されたコンポーネントを削除する
        void DeleteComponentsDelete(void);


        friend class GameObjectStorage;

        Transform m_transform;  // 座標
        BaseHandle<GameObject> m_handle;    // 自身のハンドル
        std::vector<std::shared_ptr<ComponentBase>> m_components;     // 通常のコンポーネント
        std::vector<std::shared_ptr<CollisionComponent>> m_collision; // 当たり判定コンポーネント
        std::vector<std::shared_ptr<DrawComponent>> m_drawComponents; // 描画コンポーネント
    };
}




//----- GameObject 定義
namespace EtherEngine {
    // コンポーネント追加
    // @ Temp1: 追加するコンポーネントの型
    // @ Temps: 追加コンポーネントのコンストラクタに使用する引数
    // @ Args : 追加コンポーネントのコンストラクタに使用する引数
    template <Concept::BaseOfConcept<ComponentBase> ComponentType, typename ...ArgsType>
    std::weak_ptr<ComponentType> GameObject::AddConponent(ArgsType&& ...args) {
        //----- 警告表示
        static_assert((std::is_constructible_v<ComponentType, GameObject*, ArgsType...>), "Error! AddComponent Args");

        //----- 生成
        auto ptr = std::make_shared<ComponentType>(this, args...);

        //----- 追加
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            m_drawComponents.push_back(ptr);
        }
        else {
            m_components.push_back(ptr);
        }

        //----- 返却
        return std::weak_ptr<ComponentType>(ptr);
    }
    // コンポーネント削除
    // @ Temp : 削除するコンポーネントの型
    // @ Ret  : 削除したか
    template <Concept::BaseOfConcept<ComponentBase> ComponentType>
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
    template <typename ComponentType>
        requires Concept::BaseOfConcept<ComponentType, ComponentBase>&& Concept::NotSameConcept<ComponentBase, ComponentType>
    std::weak_ptr<ComponentBase> GameObject::GetComponent(void) {
        //----- 取得
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            for (auto& component : m_drawComponents) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- 返却
                    return std::weak_ptr<ComponentType>(component);
                }
            }
        }
        else {
            for (auto& component : m_components) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
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
    template <typename ComponentType>
        requires Concept::BaseOfConcept<ComponentType, ComponentBase>&& Concept::NotSameConcept<ComponentBase, ComponentType>
    std::vector<std::weak_ptr<ComponentBase>> GameObject::GetComponents(void) {
        //----- 返却用変数宣言
        std::vector<std::weak_ptr<ComponentBase>> ret;

        //----- 取得
        if constexpr (Concept::BaseOfConcept<ComponentType, DrawComponent>) {
            for (auto& component : m_drawComponents) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
                    //----- 返却用変数に追加
                    ret.push_back(std::weak_ptr<ComponentType>(component));
                }
            }
        }
        else {
            for (auto& component : m_components) {
                if (dynamic_cast<ComponentType>(component) != nullptr) {
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
