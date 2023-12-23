#include <EngineLibrary/WrapperComponent.h>
#include <Base/BaseDefines.h>
#include <Base/EditorException.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/ConvertManageToUnmanage.h>


namespace EtherEngine {
    // コンストラクタ
    // @ Memo : コンポーネントが生成できなければ例外を送出します
    // @ Arg1 : 親ゲームオブジェクト
    // @ Arg2 : 生成コンポーネント名
    WrapperComponent::WrapperComponent(NativeGameObject* gameObject, const std::string& componentName) 
        : ComponentBase(gameObject, componentName) 
        , m_componentName(componentName) {
        // @ MEMO : 名前からの生成
        System::Type^ type = System::Type::GetType(UNMANAGE_TO_MANAGE_STRING(componentName));
        auto component = dynamic_cast<Component^>(System::Activator::CreateInstance(type));

        if (component == nullptr) throw EditorException("Error! Non UserComponent");

        m_component = component;

        // @ MEMO : GameObjectがNeitiveGameObjectのポインタを持つべきだろうか?
        //m_component->SetGameObject(gameObject);
    }


    // 開始処理
    void WrapperComponent::Start(void) {
        m_component->Start();
    }
    // 更新処理
    void WrapperComponent::Update(void) {
        m_component->Update();
    }
    // 削除時処理
    void WrapperComponent::Delete(void) {
        m_component->Delete();
    }
    // 衝突開始処理
    void WrapperComponent::CollisionStart(void) {
        m_component->CollisionStart();
    }
    // 衝突終了処理
    void WrapperComponent::CollisionEnd(void) {
        m_component->CollisionEnd();
    }
    // 衝突処理
    void WrapperComponent::CollisionHit(void) {
        m_component->CollisionHit();
    }


    // 外部出力
    Json WrapperComponent::Output(void) {
        // @ MEMO : 後で修正する
        //auto ret = Json(Json::parse(m_component->Serialize()));
        //ret["ComponentName"] = this->GetId();
        //ret["Active"] = this->GetActive();
        //return ret;
    }
    // 外部入力
    void WrapperComponent::Input(const Json& input) {
        // @ MEMO : 後で修正する
        //m_component->Deserialize(input.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES));
        SetActive(input["Active"]);
    }
}
