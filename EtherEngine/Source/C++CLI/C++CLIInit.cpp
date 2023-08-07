#include <C++CLI/C++CLIInit.h>
#include <Base/GameObject.h>
#include <C++CLI/GameComponent.h>
#include <C++CLI/GameDrawComponent.h>


//----- 関数定義
namespace EtherEngine {
    // コンポーネント生成関数
    template <Concept::BaseOfConcept<ComponentBase> ComponentType, Concept::BaseOfConcept<ComponentBase> CreateType>
    std::shared_ptr<ComponentType>&& GetComponent(GameObject* gameObject, const std::string& createName) {
        return std::move(std::make_shared<CreateType>(gameObject, createName));
    }
}


//----- 初期化・終了処理定義
namespace EtherEngine {
    // 初期化処理
    void CPPCLI::Init(void) {
        GameObject::ms_getComponent = GetComponent<ComponentBase, GameComponent>;
        GameObject::ms_getDrawComponent = GetComponent<DrawComponent, GameDrawComponent>;
    }
    // 終了処理
    void CPPCLI::Uninit(void) {
    }
}
