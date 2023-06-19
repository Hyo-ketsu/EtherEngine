#include <Base/MathUtility.h>


//----- MathUtility����
namespace EtherEngine {
    float MathUtility::ms_floatEpsilon = FLT_EPSILON;


    // ���������덷�ݒ�
    void MathUtility::SetFloatEpsilon(const float epsilon) {
        ms_floatEpsilon = epsilon;
    }


    // ���������l�� = ����
    bool MathUtility::FloatEqual(const float float1, const float float2) {
        return fabsf(float1 - float2) <= ms_floatEpsilon ? true : false;
    }
}
