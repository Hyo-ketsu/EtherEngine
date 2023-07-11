#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H
#include <Base/CollisionBase.h>
#include <Base/BaseObject.h>
#include <Base/Handle.h>


//----- ComponentBase 宣言
namespace EtherEngine {
    // コンポーネントの基礎となるクラス
    class ComponentBase : public BaseObject {
    public:
        // コンストラクタ
        // @ Arg1 : ゲームオブジェクト
        // @ Arg2 : コンポーネント名(Default : "Conponent")
        ComponentBase(void* gameObject, const std::string& name = "Conponent");
        // 純粋仮想デストラクタ
        virtual ~ComponentBase(void) = 0 {}
        ComponentBase(const ComponentBase& copy) = delete;
        // ムーブコンストラクタ
        ComponentBase(ComponentBase&& move) = default;


        // 衝突コリジョンデータゲッター
        const std::vector<CollisionHitData>& GetCollisionHitData(void) const { return m_hitData; }
        // 衝突コリジョンデータセッター
        void SetCollisionHitData(const std::vector<CollisionHitData>& in) { m_hitData = in; }
        // 衝突コリジョンデータアクセサー
        std::vector<CollisionHitData>& AccessCollisionHitData(void) { return m_hitData; }


        // 所属ゲームオブジェクトの取得
        // @ Memo : 循環参照の関係上面倒なことになっています。ヘルパーをご使用ください。
        // @ Arg1 : ゲームオブジェクトを格納する
        void GetParentObject(void** gameObject) const;


        // 更新処理を行う
        void UpdateFuntion(void);
        // 物理更新処理を行う
        // @ MEMO : しばらく実装予定なし
        void FixedUpdateFunction(void) {}
        // 削除時処理を行う
        void DeleteFuntion(void);
        // 衝突開始時処理を行う
        void CollisionStartFunction(void);
        // 衝突終了時処理を行う
        void CollisionEndFunction(void);
        // 衝突時処理を行う
        void CollisionHitFunction(void);


    protected:
        virtual void Start(void) {}
        virtual void Update(void) {}
        virtual void Delete(void) {}
        virtual void CollisionStart(void) {}
        virtual void CollisionEnd(void) {}
        virtual void CollisionHit(void) {}

    private:
        class GameObject* m_gameObject;   // 所属ゲームオブジェクト
        std::vector<CollisionHitData> m_hitData;    // 衝突コリジョンデータ
        bool m_isStart; // 既にStart処理を行っているか
    };
}


#endif // !I_COMPONENTBASE_H
