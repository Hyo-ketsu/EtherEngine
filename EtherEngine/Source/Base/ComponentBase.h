#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H
#include <Base/CollisionBase.h>
#include <Base/EtherEngineUtility.h>
class NativeGameObject;
#include <Base/NativeBaseObject.h>
#include <Base/Handle.h>


//----- ComponentBase 宣言
namespace EtherEngine {
    // コンポーネントの基礎となるクラス
    class NativeComponent : public NativeBaseObject {
    public:
        // コンストラクタ
        // @ Arg1 : ゲームオブジェクト
        NativeComponent(NativeGameObject* gameObject);
        // デストラクタ
        virtual ~NativeComponent(void) {}
        // コピーコンストラクタ
        NativeComponent(const NativeComponent& copy) = delete;
        // ムーブコンストラクタ
        NativeComponent(NativeComponent&& move) = default;
        // コピー代入
        NativeComponent& operator =(const NativeComponent& copy) = delete;
        // ムーブ代入
        NativeComponent& operator =(NativeComponent&& move) = default;


        // 親オブジェクトゲッター
        NativeGameObject* GetParentObject(void) const { return m_gameObject; }

        // 衝突コリジョンデータゲッター
        const std::vector<CollisionHitData>& GetCollisionHitData(void) const { return m_hitData; }
        // 衝突コリジョンデータセッター
        void SetCollisionHitData(const std::vector<CollisionHitData>& in) { m_hitData = in; }
        // 衝突コリジョンデータアクセサー
        std::vector<CollisionHitData>& AccessCollisionHitData(void) { return m_hitData; }

    private:
        NativeGameObject* m_gameObject;             // 所属ゲームオブジェクト
        std::vector<CollisionHitData> m_hitData;    // 衝突コリジョンデータ
    };
}


#endif // !I_COMPONENTBASE_H
