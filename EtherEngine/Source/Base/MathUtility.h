#ifndef I_MATHUTILITY_H
#define I_MATHUTILITY_H


//----- MathUtilityé¾
namespace EtherEngine {
    class MathUtility {
    public:
        // ®¬ë·Ýè
        // @ Arg1 : Ýè·é®¬ë·
        static void SetFloatEpsilon(const float epsilon);


        // ®¬lÌ = 
        // @ Ret  : ¯l©
        // @ Arg1 : är®¬l
        // @ Arg2 : är®¬l(Default : 0.0f)
        static bool FloatEqual(const float float1, const float float2 = 0.0f);

    private:
        static float ms_floatEpsilon;   // ärÉgp·é®¬ë·
    };
}


#endif // !I_MATHUTILITY_H
