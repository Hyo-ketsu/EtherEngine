#ifndef I_RANDOMMANAGE_H
#define I_RANDOMMANAGE_H
#include <Base/Singleton.h>
#include <Base/Random.h>


//----- RandomManage 宣言
namespace EtherEngine {
    // 32bit,若しくは64bitか
    template <typename T>
    concept Number32_64ByteConcept = Random::RandomBitConcept<T, 4> || Random::RandomBitConcept<T, 8>;


    // 乱数の生成を行い、かつ同じ番号を生成しないクラス
    template <Number32_64ByteConcept Type>
    class RandomManage : public Singleton<RandomManage<Type>> {
    public:
        // 乱数を生成する
        // @ Temp: 使用する型
        // @ Ret : 乱数
        Type GetRandom(void);

    private:
        // コンストラクタ
        RandomManage(void) {}

        friend class Singleton<RandomManage>;

        static std::vector<Type> m_usedNumber; // 保持している生成した番号
    };
}




//----- RandomManage 定義
namespace EtherEngine {
    // 乱数を生成する
    template <Number32_64ByteConcept Type>
    Type RandomManage<Type>::GetRandom(void) {
        //----- 変数宣言
        Type number;

        //----- リストが空なら無条件に追加
        if (m_usedNumber.size() == 0) {
            number = Random::GetRandom<Type>();
            m_usedNumber.push_back(number);
            return number;
        }

        while (true) {
            //----- 乱数を生成する
            number = Random::GetRandom<Type>();

            //----- リストにないか確認、なければ追加、あれば再生成
            for (auto it = m_usedNumber.begin(); it != m_usedNumber.end(); it++) {
                if (*it >= number) {
                    //----- 生成された番号以上の番号。再生成
                    break;
                }
                if (*it < number) {
                    //----- 生成された番号の方が小さい。追加
                    m_usedNumber.insert(it, number);
                    return number;
                }
            }
        }
    }


    template <Number32_64ByteConcept Type>
    std::vector<Type> RandomManage<Type>::m_usedNumber; // 保持している生成した番号
}


#endif // !I_RANDOMMANAGE_H
