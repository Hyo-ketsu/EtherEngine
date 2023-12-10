#include <Base/MathUtility.h>


//----- MathUtilityÀ‘•
namespace EtherEngine {
    namespace MathUtility {
        // •‚“®¬”’l‚Ì = ˆ—
        bool FloatEqual(const float float1, const float float2, const float epsilon) {
            return fabsf(float1 - float2) <= epsilon ? true : false;
        }
    }
}
