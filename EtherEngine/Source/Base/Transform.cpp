#include <Base/Transform.h>

using namespace EtherEngine;


// コンストラクタ
// @ Arg1 : 座標(デフォルト：全て0)
// @ Arg2 : 拡縮(デフォルト：全て0)
// @ Arg3 : 回転(デフォルト：全て1)
Transform::Transform(Eigen::Vector3f pos, Eigen::Vector3f sca, Eigen::Vector3f rot) 
    : m_postion(pos)
    , m_scale(sca)
    , m_rotation(rot) {
}
