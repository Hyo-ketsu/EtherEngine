#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/Transform.h>
#include <Base/ComponentBase.h>
#include <Base/HandleHelper.h>
#include <Base/Handle.h>
#include <Base/Scene.h>
// @ MEMO : ゲームオブジェクト側としてはComponentBaseのハンドルを保持したいが登録する際はサブクラスで登録される矛盾


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
        // @ Args : コンストラクタに渡す引数
        template <ComponentConcept ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddConponent(ArgsType&& ...args);


    private:
        Transform m_transform;  // 座標

        std::vector<std::shared_ptr<ComponentBase>> m_components; // 通常のコンポーネント
    };
}




//----- GameObject定義
namespace EtherEngine {
    // コンポーネント追加
    // @ Temp : 追加する通常コンポーネント
    template <ComponentConcept ComponentType, typename ...ArgsType>
    std::weak_ptr<ComponentType> GameObject::AddConponent(ArgsType&& ...args) {
        auto ptr = std::make_shared<ComponentType>(args...);
        m_components.push_back(ptr);
        return std::weak_ptr<ComponentType>(ptr);
    }
}

#endif
