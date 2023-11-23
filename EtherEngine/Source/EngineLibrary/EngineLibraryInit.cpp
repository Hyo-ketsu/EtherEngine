#include <EngineLibrary/EngineLibraryInit.h>
#include <Base/GameObject.h>
#include <EngineLibrary/GameComponent.h>
#include <EngineLibrary/GameDrawComponent.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/AssemblyHolder.h>


//----- 関数定義
namespace EtherEngine {
    // コンポーネント生成関数
    std::shared_ptr<GameComponent> GetComponent(GameObject* gameObject, const std::string& createName) {
        return std::move(std::make_shared<GameComponent>(gameObject, GetFullName(createName)));
    }


    // AddComponentメニュー表示関数
    std::shared_ptr<ComponentBase> AddComponentMenu(GameObject* gameObject) {
        //----- 各サブクラス取得
        // @ MEMO : あたり判定だけ別枠？
        auto assembly = AssemblyHolder::GetAssembly();
        auto types = assembly->GetTypes();
        std::vector<std::pair<std::string,std::string>> showTypeName;

        //----- Component追加
        for each (auto type in types) {
            if (UserBaseComponent::typeid->IsAssignableFrom(type) && UserBaseComponent::typeid != type && UserDrawBaseComponent::typeid != type) {
                showTypeName.push_back(std::make_pair<std::string, std::string>(ManageToUnmanage::String(type->Name), ManageToUnmanage::String(type->FullName)));
            }
        }

        //----- 表示
        // @ MEMO : ソートは後程実装
        for (auto&& it : showTypeName) {
            if (ImGui::MenuItem(it.first.c_str())) {
                return std::move(std::dynamic_pointer_cast<ComponentBase>(GetComponent(gameObject, it.second)));
            }
        }

        //----- 選択されない。nullptr返却
        return nullptr;
    }
}


//----- 初期化・終了処理定義
namespace EtherEngine {
    // 初期化処理
    void EngineLibrary::Init(void) {
        GameObject::ms_getComponent = GetComponent;
        GameObject::ms_addComponentMenu = AddComponentMenu;
        GameObject::ms_getFullName = [](const std::string& name, const uint index = 0, const bool isSystem = false) -> std::string { 
            return GetFullName(name, index, isSystem);
        };
    }
    // 終了処理
    void EngineLibrary::Uninit(void) {
    }
}
