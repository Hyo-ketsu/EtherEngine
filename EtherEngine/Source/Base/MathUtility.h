#ifndef I_MATHUTILITY_H
#define I_MATHUTILITY_H


//----- MathUtility宣言
namespace EtherEngine {
    namespace MathUtility {
        // 浮動小数値の = 処理
        // @ Ret  : 同値か
        // @ Arg1 : 比較浮動小数値
        // @ Arg2 : 比較浮動小数値(Default : 0.0f)
        // @ Arg3 : 比較に使用する浮動小数誤差(Default : FLT_EPSILON)
        bool FloatEqual(const float float1, const float float2 = 0.0f, const float epsilon = FLT_EPSILON);
    }
}


#endif // !I_MATHUTILITY_H
