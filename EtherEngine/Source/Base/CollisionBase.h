#ifndef I_COLLISIONBASE_H
#define I_COLLISIONBASE_H
#include <Base/BaseDefines.h>
#include <Base/StorageSystem.h>


//----- 列挙体 定義
namespace EtherEngine {
    //----- 当たり判定の形状
    enum class CollisionShape {
        Ray = 0,   // レイ(直線)
        Sphere,    // 球
        Capsule,   // カプセル
        Box,       // 箱(OBB)
        Mesh,      // メッシュ
    };

    //----- 衝突タイミング
    enum class CollisionHitTiming {
        Start = 0,  // 衝突開始
        End,        // 衝突終了
        Hit,        // 衝突中
    };


    //----- 当たり判定の種類
    enum class CollisionType {
        Substance = 0,  // 実体 (= 引き戻しを行う)
        Transparent,    // 透明 (= 引き戻しを行わない)
    };
}


//----- CollisionHitData 宣言
namespace EtherEngine {
    // 衝突情報
    class CollisionHitData {
    public:
        // コンストラクタ
        // @ Arg1 : 当たった対象
        CollisionHitData(void* gameObject);


        // 衝突対象ゲッター
        // @ Memo : ヘルパーをご使用ください。
        // @ Arg1 : 格納するポインタ
        void GetHitTarget(void** gameObject) const;

    private:
        class NativeGameObject* m_hitTarget; // 衝突対象
    };
}


//----- CollisionBase 宣言
namespace EtherEngine {
    //----- 当たり判定を表現するクラス
    class CollisionBase {
    public:
        // コンストラクタ
        // @ Arg1 : 当たり判定の形状
        // @ Arg2 : 当たり判定の種類
        // @ Arg3 : 当たり判定の移動量(Default : 全て0.0f)
        CollisionBase(const CollisionShape& shape, const CollisionType& type, const Eigen::Vector3f& offset = Eigen::Vector3f::Zero());
        // デストラクタ
        virtual ~CollisionBase(void) {}
        // コピーコンストラクタ
        CollisionBase(const CollisionBase& copy) = default;
        // ムーブコンストラクタ
        CollisionBase(CollisionBase&& move) = default;


        // 当たり判定形状ゲッター
        CollisionShape GetShape(void) const { return mc_shape; }

        // 当たり判定種類ゲッター
        CollisionType GetType(void) const { return m_type; }
        // 当たり判定種類セッター
        void SetType(const CollisionType& in) { m_type = in; }
        // 当たり判定種類アクセサー
        CollisionType& AccessType(void) { return m_type; }

        // 当たり判定の移動量ゲッター
        Eigen::Vector3f GetOffset(void) const { return m_offset; }
        // 当たり判定の移動量セッター
        void SetOffset(const Eigen::Vector3f& in) { m_offset = in; }
        // 当たり判定の移動量アクセサー
        Eigen::Vector3f& AccessOffSet(void) { return m_offset; }

        // IDゲッター
        const IDNumberType& GetId(void) const { return m_id; }

    private:
        const CollisionShape     mc_shape;  // この当たり判定の形状
        CollisionType            m_type;    // この当たり判定の種類
        Eigen::Vector3f          m_offset;  // 当たり判定の移動量
        IDNumberType             m_id;      // 自身のID
    };
}


#endif // !I_COLLISIONBASE_H
