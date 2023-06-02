#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/Transform.h>
#include <Base/ComponentBase.h>
#include <Base/HandleHelper.h>
#include <Base/Handle.h>
#include <Base/Scene.h>


namespace EtherEngine {
    // コンポーネントから継承されているか判定するコンセプト
    template <typename T>
    concept ComponentConcept = std::is_base_of_v<ComponentBase, T>;
}


//----- GameObject宣言
namespace EtherEngine {
    // シーン上のゲームを構成するオブジェクトを表現する
    class GameObject {
    public:
        // コンストラクタ
        // @ Arg1 : 座標
        GameObject(const Transform& transform);


        // 更新処理を行う
        void Update(void);
        // 描画処理を行う
        void Draw(void);


        // コンポーネント追加
        // @ Temp : 追加する通常コンポーネント
        template <ComponentConcept ComponentType>
        RefHandle<ComponentType> AddConponent(void);


    private:
        Transform m_transform;  // 座標

        std::vector<Handle<ComponentBase>> m_component; // 通常のコンポーネント
    };
}




//----- GameObject定義
namespace EtherEngine {
    // コンポーネント追加
    // @ Temp : 追加する通常コンポーネント
    template <ComponentConcept ComponentType>
    RefHandle<ComponentType> GameObject::AddConponent(void) {
        ComponentType component;
        auto handle = HandleHelper::AddItem(std::move(component), HandleCountType::Count);
        m_component.push_back(std::move(handle));
        return HandleHelper::GetRefHandle(handle);
    }
    // コンポーネント追加
    // @ Temp : 追加する描画用コンポーネント
    template <DrawComponentConcept ComponentType>
    RefHandle<ComponentType> GameObject::AddConponent(void) {
        ComponentType component;
        auto handle = HandleHelper::AddItem(std::move(component), HandleCountType::Count);
        m_drawComponent.push_back(std::move(handle));
        return HandleHelper::GetRefHandle(handle);
    }
}

#endif
