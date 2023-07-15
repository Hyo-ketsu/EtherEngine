#ifndef I_COLLISIONSPHERE_H
#define I_COLLISIONSPHERE_H
#include <Base/CollisionBase.h>
#include <Base/GameObject.h>


//----- CollisionSphere 宣言
namespace EtherEngine {
    class CollisionSphere : public CollisionBase {
    public:
        // コンストラクタ
        // @ Arg1 : 当たり判定の種類
        // @ Arg2 : 球の半径
        // @ Arg3 : 当たり判定位置(デフォルト : 全て0.0f)
        CollisionSphere(const CollisionType& type, const float& radius, const Eigen::Vector3f& offset = Eigen::Vector3f::Zero());


        // 球の半径ゲッター
        const float GetRadius(void) const { return m_radius; }
        // 球の半径セッター
        void SetRadius(const float in) { m_radius = in; }
        // 球の半径アクセサー
        float& AccessRadius(void) { return m_radius; }

    private:
        float m_radius; // 球の半径
    };
}


#endif // !I_COLLISIONSPHERE_H
