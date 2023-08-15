#ifndef I_GAMECOMPONENT_H
#define I_GAMECOMPONENT_H
#include <Base/GameObject.h>
#include <C++CLI/UserComponent.h>


//----- GameCompnent 宣言
namespace EtherEngine {
    // 
    class GameComponent : public ComponentBase {
    public:
        // コンストラクタ
        // @ Memo : コンポーネントが生成できなければ例外を送出します
        // @ Arg1 : 親ゲームオブジェクト
        // @ Arg2 : 生成コンポーネント名
        GameComponent(GameObject* gameObject, const std::string& componentName);


        // 自身のコンポーネント名の取得
        std::string GetComponentName(void) const override { return m_componentName; }


        // 開始処理
        void Start(void);
        // 更新処理
        void Update(void);
        // 削除時処理
        void Delete(void);
        // 衝突開始処理
        void CollisionStart(void);
        // 衝突終了処理
        void CollisionEnd(void);
        // 衝突処理
        void CollisionHit(void);


        // 外部出力
        Json Output(void) override;
        // 外部入力
        void Input(const Json& input) override;

        // Inspector表示
        void ShowInspector(void) override;

    protected:
        std::string m_componentName;    // 自身のコンポーネント名
        msclr::gcroot<UserBaseComponent^> m_component;  // 保持しているコンポーネント
    };
}


#endif // !I_GAMECOMPONENT_H
