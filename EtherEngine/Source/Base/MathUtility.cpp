#include <Base/MathUtility.h>


//----- MathUtilityÀ‘•
namespace EtherEngine {
    float MathUtility::ms_floatEpsilon = FLT_EPSILON;


    // •‚“®¬”Œë·İ’è
    void MathUtility::SetFloatEpsilon(const float epsilon) {
        ms_floatEpsilon = epsilon;
    }


    // •‚“®¬”’l‚Ì = ˆ—
    bool MathUtility::FloatEqual(const float float1, const float float2) {
        return fabsf(float1 - float2) <= ms_floatEpsilon ? true : false;
    }
}
