#ifndef I_EDITOROBJECT_H
#define I_EDITOROBJECT_H
#include <Base/ConceptUtility.h>
#include <Base/Transform.h>
#include <Base/Handle.h>
#include <EtherEngine/EditorComponentBase.h>


//----- EditorObject宣言
namespace EtherEngine {
    class EditorObject {
    public:
        // 更新処理を行う
        void Update(void);
        // 描画処理を行う
        void Draw(void);


        // Transformアクセサー
        Transform& AccessTransform(void) { return m_transform; }

        // ハンドルゲッター
        BaseHandle<EditorObject> GetHandle(void) const { return m_handle; }


        // コンポーネントを追加する
        // @ Temp1: 追加するコンポーネント
        // @ Temps: 追加コンポーネントのコンストラクタに使用する引数
        // @ Args : 追加コンポーネントのコンストラクタに使用する引数
        template <Concept::BaseOfConcept<EditorComponentBase> ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddComponent(ArgsType... args);

    private:
        // コンストラクタ
        // @ Arg1 : 生成座標
        EditorObject(const Transform& transform);

        friend class EditorObjectStorage;


        Transform m_transform;  // 座標
        BaseHandle<EditorObject> m_handle;  // 自身のハンドル
        std::vector<std::shared_ptr<EditorComponentBase>> m_component;  // 保持しているコンポーネント
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
        m_component.push_back(ptr);

        //----- 返却
        return std::weak_ptr<ComponentType>(ptr);
    }
}


#endif // !I_EDITOROBJECT_H
