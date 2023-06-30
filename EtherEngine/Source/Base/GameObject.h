#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/BaseObject.h>
#include <Base/ComponentBase.h>
#include <Base/ComponentHelper.h>
#include <Base/ConceptUtility.h>
#include <Base/DrawComponent.h> 
#include <Base/HandleHelper.h>
#include <Base/Handle.h>
#include <Base/Transform.h>
#include <Base/Scene.h>


//----- GameObject宣言
namespace EtherEngine {
    // シーン上のゲームを構成するオブジェクトを表現する
    class GameObject : public BaseObject {
    public:
        // 更新処理を行う
        void Update(void);
        // 描画処理を行う
        void Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection);


        // コンポーネント追加
        // @ Temp : 追加する通常コンポーネント
        // @ Args : コンストラクタに渡す引数
        template <Concept::BaseOfConcept<ComponentBase> ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddConponent(ArgsType&& ...args);

        // 座標取得
        Transform& AccessTransform(void) { return m_transform; }

    protected:
        // コンストラクタ
        // @ Arg1 : 座標
        // @ Arg2 : オブジェクト名(Default : GameObject)
        GameObject(const Transform& transform, const std::string& name = "GameObject");


        // 通常コンポーネントとして追加する
        // @ Temp : コンポーネントの種類
        // @ Arg1 : 追加するコンポーネント
        template <Concept::NotBaseOfConcept<DrawComponent> ComponentType>
        void AddConponent(std::shared_ptr<ComponentType>& component);
        // 描画コンポーネントとして追加する
        // @ Temp : コンポーネントの種類
        // @ Arg1 : 追加するコンポーネント
        template <Concept::BaseOfConcept<DrawComponent> ComponentType>
        void AddConponent(std::shared_ptr<ComponentType>& component);


    private:
        friend class GameObjectStorage;

        Transform m_transform;  // 座標
        BaseHandle<GameObject> m_handle;    // 自身のハンドル
        std::vector<std::shared_ptr<ComponentBase>> m_components;     // 通常のコンポーネント
        std::vector<std::shared_ptr<DrawComponent>> m_drawComponents; // 描画コンポーネント
    };
}




//----- GameObject定義
namespace EtherEngine {
    // コンポーネント追加
    // @ Temp : 追加する通常コンポーネント
    template <Concept::BaseOfConcept<ComponentBase> ComponentType, typename ...ArgsType>
    std::weak_ptr<ComponentType> GameObject::AddConponent(ArgsType&& ...args) {
        //----- 警告表示
        static_assert((std::is_constructible_v<ComponentType, GameObject*, ArgsType...>), "Error! AddComponent Args");

        //----- 生成
        auto ptr = std::make_shared<ComponentType>(this, args...);

        //----- 追加
        AddConponent<ComponentType>(ptr);

        //----- 返却
        return std::weak_ptr<ComponentType>(ptr);
    }


    // 通常コンポーネントとして追加する
    // @ Temp : コンポーネントの種類
    // @ Arg1 : 追加するコンポーネント
    template <Concept::NotBaseOfConcept<DrawComponent> ComponentType>
    void GameObject::AddConponent(std::shared_ptr<ComponentType>& component) {
        m_components.push_back(component);
    }
    // 描画コンポーネントとして追加する
    // @ Temp : コンポーネントの種類
    // @ Arg1 : 追加するコンポーネント
    template <Concept::BaseOfConcept<DrawComponent> ComponentType>
    void GameObject::AddConponent(std::shared_ptr<ComponentType>& component) {
        m_drawComponents.push_back(component);
    }
}

#endif
