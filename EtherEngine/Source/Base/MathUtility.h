#ifndef I_MATHUTILITY_H
#define I_MATHUTILITY_H


//----- MathUtility้พ
namespace EtherEngine {
    namespace MathUtility {
        // ฎฌlฬ = 
        // @ Ret  : ฏlฉ
        // @ Arg1 : ไrฎฌl
        // @ Arg2 : ไrฎฌl(Default : 0.0f)
        // @ Arg3 : ไrษgpท้ฎฌ๋ท(Default : FLT_EPSILON)
        bool FloatEqual(const float float1, const float float2 = 0.0f, const float epsilon = FLT_EPSILON);
    }
}


#endif // !I_MATHUTILITY_H
