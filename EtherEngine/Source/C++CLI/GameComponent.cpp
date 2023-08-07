#include <C++CLI/GameComponent.h>
#include <C++CLI/C++CLIUtility.h>


namespace EtherEngine {
    // コンストラクタ
    // @ Memo : コンポーネントが生成できなければ例外を送出します
    // @ Arg1 : 親ゲームオブジェクト
    // @ Arg2 : 生成コンポーネント名
    GameComponent::GameComponent(GameObject* gameObject, const std::string& componentName) 
        : ComponentBase(gameObject, componentName) 
        , m_componentName(componentName) {
        // @ MEMO : 名前からの生成
        Type^ type = Type::GetType(UnToManage(componentName));
        auto component = dynamic_cast<UserBaseComponent^>(Activator::CreateInstance(type));

        if (component == nullptr) throw std::exception("Error! Non UserComponent");

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
    std::string GameComponent::Output(void) {
        return m_component->Serialize();
    }
    // 外部入力
    void GameComponent::Input(const std::string& input) {
        m_component->Deserialize(input);
    }
}
