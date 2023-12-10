#include <Base/MathUtility.h>


//----- MathUtility����
namespace EtherEngine {
    namespace MathUtility {
        // ���������l�� = ����
        bool FloatEqual(const float float1, const float float2, const float epsilon) {
            return fabsf(float1 - float2) <= epsilon ? true : false;
        }
    }
}
