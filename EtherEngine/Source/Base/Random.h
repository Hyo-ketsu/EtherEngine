#ifndef I_RANDOM_H
#define I_RANDOM_H


namespace EtherEngine {
    namespace Random {
        // 数値型若しくは浮動小数、かつ指定したByte数か
        template <class T, int Byte>
        concept RandomBitConcept = (std::is_integral_v<T> || std::is_floating_point_v<T>) && (int)sizeof(T) == Byte;


        // 32bit(4Byte)乱数を生成する
        // @ Temp: 使用する型
        // @ Ret : 乱数
        template <RandomBitConcept<4> Type>
        Type GetRandom(void);
        // 64bit(8Byte)乱数を生成する
        // @ Temp: 使用する型
        // @ Ret : 乱数
        template <RandomBitConcept<8> Type>
        Type GetRandom(void);
    }
}




//----- Random実装
namespace EtherEngine {
    namespace Random {
        // 32bit(4Byte)乱数を生成する
        // @ Temp: 使用する型(デフォルト : float)
        // @ Ret : 乱数
        template <RandomBitConcept<4> Type>
        Type GetRandom(void) {
            //----- 変数宣言
            static std::random_device randomDevice; // 非決定的な乱数生成器
            static std::mt19937 mt(randomDevice()); // 乱数

            //----- 返却
            return (Type)mt();
        }
        // 64bit(8Byte)乱数を生成する
        // @ Temp: 使用する型(デフォルト : long long)
        // @ Ret : 乱数
        template <RandomBitConcept<8> Type>
        Type GetRandom(void) {
            //----- 変数宣言
            static std::random_device randomDevice;    // 非決定的な乱数生成器
            static std::mt19937_64 mt(randomDevice()); // 乱数

            //----- 返却
            return (Type)mt();
        }
    }
}


#endif // !I_RANDOM_H
