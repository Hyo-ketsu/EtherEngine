#include <EngineLibrary/GameDrawComponent.h>
#include <EngineLibrary/UserDrawComponent.h>


//----- GameDrawComponent 定義
namespace EtherEngine {
    // コンストラクタ
    GameDrawComponent::GameDrawComponent(GameObject* gameObject, const std::string& componentName)
        : GameComponent(gameObject, componentName) 
        , DrawComponent(gameObject, componentName) {
    }
    // 開始処理
    void GameDrawComponent::Start(void) {
        GameComponent::Start();
    }
    // 更新処理
    void GameDrawComponent::Update(void) {
        GameComponent::Update();
    }
    // 削除時処理
    void GameDrawComponent::Delete(void) {
        GameComponent::Delete();
    }
    // 衝突開始処理
    void GameDrawComponent::CollisionStart(void) {
        GameComponent::CollisionStart();
    }
    // 衝突終了処理
    void GameDrawComponent::CollisionEnd(void) {
        GameComponent::CollisionEnd();
    }
    // 衝突処理
    void GameDrawComponent::CollisionHit(void) {
        GameComponent::CollisionHit();
    }
    // 描画
    void GameDrawComponent::Draw(void) {    
        //----- キャスト
        auto userBaseComponent = safe_cast<UserBaseComponent^>(m_component);
        auto userDrawBaseComponent = dynamic_cast<UserDrawBaseComponent^>(userBaseComponent);

        //----- 描画
        userDrawBaseComponent->Bind();
        userDrawBaseComponent->Draw();
    }


    // 外部出力
    Json GameDrawComponent::Output(void) {
        return GameComponent::Output();
    }
    // 外部入力
    void GameDrawComponent::Input(const Json& input) {
        GameComponent::Input(input);
    }
}
