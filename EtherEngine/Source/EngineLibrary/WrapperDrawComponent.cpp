#include <EngineLibrary/WrapperDrawComponent.h>
#include <EngineLibrary/DrawComponent.h>


//----- WrapperDrawComponent 定義
namespace EtherEngine {
    // コンストラクタ
    WrapperDrawComponent::WrapperDrawComponent(NativeGameObject* gameObject, const std::string& componentName)
        : WrapperComponent(gameObject, componentName) 
        , DrawComponent(gameObject, componentName) {
    }
    // 開始処理
    void WrapperDrawComponent::Start(void) {
        WrapperComponent::Start();
    }
    // 更新処理
    void WrapperDrawComponent::Update(void) {
        WrapperComponent::Update();
    }
    // 削除時処理
    void WrapperDrawComponent::Delete(void) {
        WrapperComponent::Delete();
    }
    // 衝突開始処理
    void WrapperDrawComponent::CollisionStart(void) {
        WrapperComponent::CollisionStart();
    }
    // 衝突終了処理
    void WrapperDrawComponent::CollisionEnd(void) {
        WrapperComponent::CollisionEnd();
    }
    // 衝突処理
    void WrapperDrawComponent::CollisionHit(void) {
        WrapperComponent::CollisionHit();
    }
    // 描画
    void WrapperDrawComponent::Draw(void) {    
        //----- キャスト
        auto userBaseComponent = safe_cast<Component^>(m_component);
        auto userDrawBaseComponent = dynamic_cast<DrawBaseComponent^>(userBaseComponent);

        //----- 描画
        userDrawBaseComponent->Bind();
        userDrawBaseComponent->Draw();
    }


    // 外部出力
    Json WrapperDrawComponent::Output(void) {
        return WrapperComponent::Output();
    }
    // 外部入力
    void WrapperDrawComponent::Input(const Json& input) {
        WrapperComponent::Input(input);
    }
}
