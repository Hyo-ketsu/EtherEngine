#ifndef I_MATHUTILITY_H
#define I_MATHUTILITY_H


//----- MathUtility�錾
namespace EtherEngine {
    class MathUtility {
    public:
        // ���������덷�ݒ�
        // @ Arg1 : �ݒ肷�镂�������덷
        static void SetFloatEpsilon(const float epsilon);


        // ���������l�� = ����
        // @ Ret  : ���l��
        // @ Arg1 : ��r���������l
        // @ Arg2 : ��r���������l(Default : 0.0f)
        static bool FloatEqual(const float float1, const float float2 = 0.0f);

    private:
        static float ms_floatEpsilon;   // ��r�Ɏg�p���镂�������덷
    };
}


#endif // !I_MATHUTILITY_H
