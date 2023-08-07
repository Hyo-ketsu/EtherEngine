#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H
#include <Base/CollisionBase.h>
#include <Base/EtherEngineUtility.h>
#include <Base/BaseObject.h>
#include <Base/Handle.h>


//----- コンポーネント用定数
namespace EtherEngine {
    namespace Component {
        const std::string TYPE_COMPONENT = "Component";                     // 通常コンポーネント定義名
        const std::string TYPE_DRAW_COMPONENT = "DrawComponent";            // 描画コンポーネント定義名
        const std::string TYPE_COLLISION_COMPONENT = "CollisionComponent";  // 当たり判定コンポーネント定義名
    }
}


//----- ComponentBase 宣言
namespace EtherEngine {
    // コンポーネントの基礎となるクラス
    class ComponentBase : public BaseObject, public IInOuter {
    public:
        // コンストラクタ
        // @ Arg1 : ゲームオブジェクト
        // @ Arg2 : コンポーネント名(Default : "Conponent")
        ComponentBase(void* gameObject, const std::string& name = "Component");
        // デストラクタ
        virtual ~ComponentBase(void) {}
        // コピーコンストラクタ
        ComponentBase(const ComponentBase& copy) = delete;
        // ムーブコンストラクタ
        ComponentBase(ComponentBase&& move) = default;
        // コピー代入
        ComponentBase& operator =(const ComponentBase& copy) = delete;
        // ムーブ代入
        ComponentBase& operator =(ComponentBase&& move) = default;


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


        // コンポーネント名の取得
        // @ Ret  : コンポーネント名
        virtual std::string GetComponentName(void) const;
        // コンポーネントタイプ名の取得
        // @ Ret  : コンポーネントのタイプ
        virtual std::string GetComponentTypeName(void) const;


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
        // 開始処理
        virtual void Start(void) = 0;
        // 更新処理
        virtual void Update(void) = 0;
        // 削除時処理
        virtual void Delete(void) = 0;
        // 衝突開始処理
        virtual void CollisionStart(void) = 0;
        // 衝突終了処理
        virtual void CollisionEnd(void) = 0;
        // 衝突処理
        virtual void CollisionHit(void) = 0;

    private:
        class GameObject* m_gameObject;   // 所属ゲームオブジェクト
        std::vector<CollisionHitData> m_hitData;    // 衝突コリジョンデータ
        bool m_isStart; // 既にStart処理を行っているか
    };
}


#endif // !I_COMPONENTBASE_H
