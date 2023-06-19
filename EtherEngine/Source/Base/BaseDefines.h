#ifndef I_BASEDEFINES_H
#define I_BASEDEFINES_H
#include <Base/ConceptUtility.h>

//// コピーコンストラクタ定義
//#define DEFAULT_COPY_CONSTRUCTOR(type) type(const type& copy) = default
//// ムーブコンストラクタ定義
//#define DEFAULT_MOVE_CONSTRUCTOR(type) type(type&& move) = default

//----- 定数定義
namespace EtherEngine {
    // 画面比率
    namespace AspectDefine {
        // HD比率
        template <Concept::ArithmeticConcept T = float>
        const float HD = 16.0f / 9.0f;
    }
    // カメラ用の定数
    namespace CameraDefine {
        const Eigen::Vector3f UP = { 0.0f,1.0f,0.0f };      // カメラの上方向
        const float FOVY = DirectX::XMConvertToRadians(60); // 視野角
        const float ASPECT = AspectDefine::HD<>;    // 画面アスペクト比
        const float NEAR = 0.2f;                    // 最短クリップ距離
        const float FAR = 1000.0f;                  // 最長クリップ距離
    }
}


#endif // !I_BASEDEFINES_H
