#ifndef I_MATHUTILITY_H
#define I_MATHUTILITY_H


//----- MathUtility�錾
namespace EtherEngine {
    namespace MathUtility {
        // ���������l�� = ����
        // @ Ret  : ���l��
        // @ Arg1 : ��r���������l
        // @ Arg2 : ��r���������l(Default : 0.0f)
        // @ Arg3 : ��r�Ɏg�p���镂�������덷(Default : FLT_EPSILON)
        bool FloatEqual(const float float1, const float float2 = 0.0f, const float epsilon = FLT_EPSILON);
    }
}


#endif // !I_MATHUTILITY_H
