#include <EngineLibrary/GameComponent.h>
#include <Base/BaseDefines.h>
#include <Base/EditorException.h>
#include <EngineLibrary/EngineLibraryUtility.h>


namespace EtherEngine {
    // コンストラクタ
    // @ Memo : コンポーネントが生成できなければ例外を送出します
    // @ Arg1 : 親ゲームオブジェクト
    // @ Arg2 : 生成コンポーネント名
    GameComponent::GameComponent(GameObject* gameObject, const std::string& componentName) 
        : ComponentBase(gameObject, componentName) 
        , m_componentName(componentName) {
        // @ MEMO : 名前からの生成
        System::Type^ type = System::Type::GetType(UNMANAGE_TO_MANAGE_STRING(componentName));
        auto component = dynamic_cast<UserBaseComponent^>(System::Activator::CreateInstance(type));

        if (component == nullptr) throw EditorException("Error! Non UserComponent");

        m_component = component;

        m_component->SetGameObject(gameObject);
    }


    // 開始処理
    void GameComponent::Start(void) {
        m_component->Start();
    }
    // 更新処理
    void GameComponent::Update(void) {
        m_component->Update();
    }
    // 削除時処理
    void GameComponent::Delete(void) {
        m_component->Delete();
    }
    // 衝突開始処理
    void GameComponent::CollisionStart(void) {
        m_component->CollisionStart();
    }
    // 衝突終了処理
    void GameComponent::CollisionEnd(void) {
        m_component->CollisionEnd();
    }
    // 衝突処理
    void GameComponent::CollisionHit(void) {
        m_component->CollisionHit();
    }


    // 外部出力
    Json GameComponent::Output(void) {
        auto ret = Json(Json::parse(m_component->Serialize()));
        ret["ComponentName"] = this->GetComponentName();
        ret["Active"] = this->GetActive();
        return ret;
    }
    // 外部入力
    void GameComponent::Input(const Json& input) {
        m_component->Deserialize(input.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES));
        SetActive(input["Active"]);
    }
    // Inspector表示
    void GameComponent::ShowInspector(void) {
        m_component->DrawInspector();
    }
}
