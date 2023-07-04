#ifndef I_COLLISIONBASE_H
#define I_COLLISIONBASE_H


//----- 列挙体 定義
namespace EtherEngine {
    //----- 当たり判定の形状
    enum class CollisionShape {
        Ray = 0,   // レイ(直線)
        Sphere,    // 球
        Capsule,   // カプセル
        Box,       // 箱
        Mesh,      // メッシュ
    };


    //----- 当たり判定の種類
    enum class CollisionType {
        Substance = 0,  // 実体 (= 引き戻しを行う)
        Transparent,    // 透明 (= 引き戻しを行わない)
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
        CollisionBase(const CollisionShape& shape, const CollisionType& type);
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

    private:
        const CollisionShape mc_shape;  // この当たり判定の形状
        CollisionType m_type;           // この当たり判定の種類
    };
}


#endif // !I_COLLISIONBASE_H
