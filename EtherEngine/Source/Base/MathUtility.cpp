#include <Base/MathUtility.h>


//----- MathUtility実装
namespace EtherEngine {
    namespace MathUtility {
        // 浮動小数値の = 処理
        bool FloatEqual(const float float1, const float float2, const float epsilon) {
            return fabsf(float1 - float2) <= epsilon ? true : false;
        }
    }
}
