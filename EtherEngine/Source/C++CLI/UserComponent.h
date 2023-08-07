#ifndef I_USERCOMPONENT_H
#define I_USERCOMPONENT_H
// @ MEMO : 実際にユーザーが記述するためのもととなるクラス
#include <C++CLI/ComponentInterface.h>
#include <C++CLI/C++CLIUtility.h>
#include <Base/GameObject.h>


//----- UseBaseComponent 宣言
namespace EtherEngine {
    public ref class UserBaseComponent : Serializer {
    public:
        // コンストラクタ
        // @ MEMO : 仮措置
        UserBaseComponent(void)
            : m_gameObject(nullptr) {
        }


        // 親ゲームオブジェクトゲッター
        GameObject* const GetGameObject(void) { return m_gameObject; }
        // 親ゲームオブジェクトセッター
        void SetGameObject(GameObject* in) { m_gameObject = in; }


        // 開始処理
        virtual void Start(void) {}
        // 更新処理
        virtual void Update(void) {}
        // 削除時処理
        virtual void Delete(void) {}
        // 衝突開始処理
        virtual void CollisionStart(void) {}
        // 衝突終了処理
        virtual void CollisionEnd(void) {}
        // 衝突処理
        virtual void CollisionHit(void) {}

    private:
        GameObject* m_gameObject; // 自身を保持しているゲームオブジェクト
    };
}


#endif // !I_USERCOMPONENT_H
