#ifndef I_EDITOROBJECT_H
#define I_EDITOROBJECT_H
#include <Base/ConceptUtility.h>
#include <Base/GameObject.h>
#include <Base/Transform.h>
#include <Base/Handle.h>
#include <EtherEngine/EditorComponentBase.h>


//----- EditorObject宣言
namespace EtherEngine {
    class EditorObject : public BaseObject {
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
        Handle<EditorObject> GetHandle(void) const { return m_handle; }


        // コンポーネントを追加する
        // @ Temp1: 追加するコンポーネントの型
        // @ Temps: 追加コンポーネントのコンストラクタに使用する引数
        // @ Args : 追加コンポーネントのコンストラクタに使用する引数
        template <Concept::SubClassOnly<EditorComponentBase> ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddComponent(ArgsType ...args);
        // コンポーネント削除
        // @ Temp : 削除するコンポーネントの型
        // @ Ret  : 削除したか
        template <Concept::SubClassOnly<EditorComponentBase> ComponentType>
        bool DeleteComponent(void);
        // コンポーネントを取得する
        // @ Temp : 取得するコンポーネント型(EditorComponentBaseは使用不可)
        // @ Ret  : 取得したコンポーネント
        // @ Arg1 : 何番目のコンポーネントを使用するか(Default : 0)
        template <Concept::SubClassOnly<EditorComponentBase> ComponentType>
        std::weak_ptr<ComponentBase> GetComponent(uint index = 0);
        // コンポーネントを複数取得する
        // @ Temp : 取得するコンポーネント型(EditorComponentBaseは使用不可)
        // @ Ret  : 取得したコンポーネント（複数）
        template <Concept::SubClassOnly<EditorComponentBase> ComponentType>
        std::vector<std::weak_ptr<ComponentBase>> GetComponents(void);


        // 外部出力
        Json Output(void) override { return Json(); }
        // 外部入力
        void Input(const Json& json) override {}


        // Inspector表示
        void ShowInspector(void) override {}

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
        Handle<EditorObject> m_handle;  // 自身のハンドル
        std::vector<std::shared_ptr<EditorComponentBase>> m_components;  // 保持しているコンポーネント
    };
}


//----- EditorObject定義
namespace EtherEngine {
    // コンポーネントを追加する
    template <Concept::SubClassOnly<EditorComponentBase> ComponentType, typename ...ArgsType>
    std::weak_ptr<ComponentType> EditorObject::AddComponent(ArgsType ...args) {
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
    template <Concept::SubClassOnly<EditorComponentBase> ComponentType>
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
    // @ Temp : 取得するコンポーネント型(EditorComponentBaseは使用不可)
    // @ Ret  : 取得したコンポーネント
    // @ Arg1 : 何番目のコンポーネントを使用するか(Default : 0)
    template <Concept::SubClassOnly<EditorComponentBase> ComponentType>
    std::weak_ptr<ComponentBase> EditorObject::GetComponent(uint index) {
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
        //----- 無効値返却
        return std::weak_ptr<ComponentType>();
    }
    // コンポーネントを複数取得する
    // @ Temp : 取得するコンポーネント型(EditorComponentBaseは使用不可)
    // @ Ret  : 取得したコンポーネント（複数）
    template <Concept::SubClassOnly<EditorComponentBase> ComponentType>
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
