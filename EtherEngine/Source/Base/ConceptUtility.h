#ifndef I_CONCEPTUTILITY_H
#define I_CONCEPTUTILITY_H


namespace EtherEngine {
    // 特定の型と同じ型か判定するコンセプト
    template <typename T, typename U>
    concept SameConcept = std::is_same_v<T, U>;
    // 特定の型と違い方か判定するコンセプト
    template <typename T, typename U>
    concept NotSameConcept = !(std::is_same_v<T, U>);
}


#endif // !I_CONCEPTUTILITY_H
