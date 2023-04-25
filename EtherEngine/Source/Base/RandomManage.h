#ifndef I_RANDOMMANAGE_H
#define I_RANDOMMANAGE_H
#include <Base/Singleton.h>
#include <Base/Random.h>


//----- RandomManage定義
namespace EtherEngine {
    namespace RandomManage {
        // 32bit,若しくは64bitの数値（整数、浮動小数）か
        template <typename T>
        concept Number32_64Concept = Random::Random32BitConcept<T> || Random::Random64BitConcept<T>;


        // 乱数を生成する
        // @ Temp: 使用する型
        // @ Ret : 乱数
        template <Number32_64Concept Type>
        Type GetRandom(void);
    };
}




//----- RandomManage宣言
namespace EtherEngine {
    // 乱数を生成する
    // @ Temp: 使用する型
    // @ Ret : 乱数
    template <RandomManage::Number32_64Concept Type>
    Type RandomManage::GetRandom(void) {
        //----- 静的変数宣言
        std::unordered_map<Type, nullptr> random32map;

        //----- 乱数生成
        auto ret = Random:::GetRandom<Type>();
        
        //----- 生成を繰り返す
        while (random32map.find(ret) == random32map.end()) {
            ret = Random::Random32BitConcept<Type>();
        }

        //----- 返却
        return ret;
    }
}


#endif // !I_RANDOMMANAGE_H
