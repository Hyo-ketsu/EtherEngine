#ifndef I_MATHUTILITY_H
#define I_MATHUTILITY_H


//----- MathUtility宣言
namespace EtherEngine {
    class MathUtility {
    public:
        // 浮動小数誤差設定
        // @ Arg1 : 設定する浮動小数誤差
        static void SetFloatEpsilon(const float epsilon);


        // 浮動小数値の = 処理
        // @ Ret  : 同値か
        // @ Arg1 : 比較浮動小数値
        // @ Arg2 : 比較浮動小数値(Default : 0.0f)
        static bool FloatEqual(const float float1, const float float2 = 0.0f);

    private:
        static float ms_floatEpsilon;   // 比較に使用する浮動小数誤差
    };
}


#endif // !I_MATHUTILITY_H
