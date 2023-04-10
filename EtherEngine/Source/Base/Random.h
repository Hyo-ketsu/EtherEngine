#ifndef I_RANDOM_H
#define I_RANDOM_H


namespace EtherEngine {
    namespace Random {
        // 数値型若しくは浮動小数、かつ32bit(4B)か
        template <class T>
        concept Random32BitConcept = (std::is_integral_v<T> || std::is_floating_point_v<T>) && (int)sizeof(T) == 4;
        // 数値型若しくは浮動小数、かつ64bit(8B)か
        template <class T>
        concept Random64BitConcept = (std::is_integral_v<T> || std::is_floating_point_v<T>) && (int)sizeof(T) == 8;


        // 32bit乱数を生成する
        // @ Temp: 使用する型
        // @ Ret : 乱数
        template <Random32BitConcept Type>
        Type GetRandom(void);
        // 64bit乱数を生成する
        // @ Temp: 使用する型
        // @ Ret : 乱数
        template <Random64BitConcept Type>
        Type GetRandom(void);
    }
}




//----- Random実装
namespace EtherEngine {
    namespace Random {
        // 32bit乱数を生成する
        // @ Temp: 使用する型(デフォルト : float)
        // @ Ret : 乱数
        template <Random32BitConcept Type>
        Type GetRandom(void) {
            //----- 変数宣言
            static std::random_device randomDevice; // 非決定的な乱数生成器
            static std::mt19937 mt(rnd());          // 乱数

            //----- 返却
            return (Type)mt();
        }
        // 64bit乱数を生成する
        // @ Temp: 使用する型(デフォルト : long long)
        // @ Ret : 乱数
        template <Random64BitConcept Type>
        Type GetRandom(void) {
            //----- 変数宣言
            static std::random_device randomDevice; // 非決定的な乱数生成器
            static std::mt19937_64 mt(rnd());       // 乱数

            //----- 返却
            return (Type)mt();
        }
    }
}


#endif // !I_RANDOM_H
