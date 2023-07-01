#ifndef I_EDITOROBJECT_H
#define I_EDITOROBJECT_H
#include <Base/ConceptUtility.h>
#include <Base/GameObject.h>
#include <Base/Transform.h>
#include <Base/Handle.h>
#include <EtherEngine/EditorComponentBase.h>


//----- EditorObject宣言
namespace EtherEngine {
    class EditorObject : BaseObject {
    public:
        // 更新処理を行う
        void Update(void);
        // 描画処理を行う
        void Draw(void);
        // 削除時処理を行う
        void Delete(void);


        // Transformゲッター
        const Transform& GetTransform(void) const { return m_transform; }
        // Transformセッター
        void SetTransform(const Transform& in) { m_transform = in; }
        // Transformアクセサー
        Transform& AccessTransform(void) { return m_transform; }


        // ハンドルゲッター
        BaseHandle<EditorObject> GetHandle(void) const { return m_handle; }


        // コンポーネントを追加する
        // @ Temp1: 追加するコンポーネントの型
        // @ Temps: 追加コンポーネントのコンストラクタに使用する引数
        // @ Args : 追加コンポーネントのコンストラクタに使用する引数
        template <Concept::BaseOfConcept<EditorComponentBase> ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddComponent(ArgsType... args);
        // コンポーネント削除
        // @ Temp : 削除するコンポーネントの型
        // @ Ret  : 削除したか
        template <Concept::BaseOfConcept<EditorComponentBase> ComponentType>
        bool DeleteComponent(void);
        // コンポーネントを取得する
        // @ Temp : 取得するコンポーネント型(ComponentBaseは使用不可)
        // @ Ret  : 取得したコンポーネント
        template <typename ComponentType>
            requires Concept::BaseOfConcept<EditorComponentBase, ComponentBase>&& Concept::NotSameConcept<EditorComponentBase, ComponentType>
        std::weak_ptr<ComponentBase> GetComponent(void);
        // コンポーネントを複数取得する
        // @ Temp : 取得するコンポーネント型(ComponentBaseは使用不可)
        // @ Ret  : 取得したコンポーネント（複数）
        template <typename ComponentType>
            requires Concept::BaseOfConcept<EditorComponentBase, ComponentBase>&& Concept::NotSameConcept<EditorComponentBase, ComponentType>
        std::vector<std::weak_ptr<ComponentBase>> GetComponents(void);

    protected:
        // コンストラクタ
        // @ Arg1 : 生成座標
        // @ Arg2 : オブジェクト名
        EditorObject(const Transform& transform, const std::string& name = "EditorObject");

    private:
        // 削除されたコンポーネントを削除する
        void DeleteComponentsDelete(void);


        friend class EditorObjectStorage;

        Transform m_transform;  // 座標
        BaseHandle<EditorObject> m_handle;  // 自身のハンドル
        std::vector<std::shared_ptr<EditorComponentBase>> m_components;  // 保持しているコンポーネント
    };
}


//----- EditorObject定義
namespace EtherEngine {
    // コンポーネントを追加する
    template <Concept::BaseOfConcept<EditorComponentBase> ComponentType, typename ...ArgsType>
    std::weak_ptr<ComponentType> EditorObject::AddComponent(ArgsType... args) {
        //----- 警告表示
        static_assert((std::is_constructible_v<ComponentType, EditorObject*, ArgsType...>), "Error! AddComponent Args");

        //----- 生成
        auto ptr = std::make_shared<ComponentType>(this, args...);

        //----- 追加
        m_components.push_back(ptr);

        //----- 返却
        return std::weak_ptr<ComponentType>(ptr);
    }
    // コンポーネント削除
    // @ Temp : 削除するコンポーネントの型
    // @ Ret  : 削除したか
    template <Concept::BaseOfConcept<EditorComponentBase> ComponentType>
    bool EditorObject::DeleteComponent(void) {
        for (auto& component : m_components) {
            if (dynamic_cast<ComponentType>(component) != nullptr) {
                //----- 削除
                component->DeleteFuntion();
                component->SetDelete(true);
            }
        }
    }
    // コンポーネントを取得する
    // @ Temp : 取得するコンポーネント型(ComponentBaseは使用不可)
    // @ Ret  : 取得したコンポーネント
    template <typename ComponentType>
        requires Concept::BaseOfConcept<EditorComponentBase, ComponentBase> && Concept::NotSameConcept<EditorComponentBase, ComponentType>
    std::weak_ptr<ComponentBase> EditorObject::GetComponent(void) {
        for (auto& component : m_components) {
            if (dynamic_cast<ComponentType>(component) != nullptr) {
                //----- 返却
                return std::weak_ptr<ComponentType>(component);
            }
        }
        //----- 無効値返却
        return std::weak_ptr<ComponentType>();
    }
    // コンポーネントを複数取得する
    // @ Temp : 取得するコンポーネント型(ComponentBaseは使用不可)
    // @ Ret  : 取得したコンポーネント（複数）
    template <typename ComponentType>
        requires Concept::BaseOfConcept<EditorComponentBase, ComponentBase> && Concept::NotSameConcept<EditorComponentBase, ComponentType>
    std::vector<std::weak_ptr<ComponentBase>> EditorObject::GetComponents(void) {
        //----- 返却用変数宣言
        std::vector<std::weak_ptr<ComponentBase>> ret;

        //----- 取得
        for (auto& component : m_components) {
            if (dynamic_cast<ComponentType>(component) != nullptr) {
                //----- 返却用変数に追加
                ret.push_back(std::weak_ptr<ComponentType>(component));
            }
        }

        //----- 返却
        return ret;
    }
}


#endif // !I_EDITOROBJECT_H
