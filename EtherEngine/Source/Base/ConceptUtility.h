#ifndef I_CONCEPTUTILITY_H
#define I_CONCEPTUTILITY_H


namespace EtherEngine {
    namespace Concept {
        // 特定の型と同じ型か判定するコンセプト
        template <typename T, typename U>
        concept SameConcept = std::is_same_v<T, U>;
        // 特定の型と違う型か判定するコンセプト
        template <typename T, typename U>
        concept NotSameConcept = !(SameConcept<T, U>);

        // 指定した型を継承しているか判定するコンセプト
        template <typename T, typename U>
        concept BaseOfConcept = std::is_base_of_v<U, T>;
        // 指定した型を継承していないか判定するコンセプト
        template <typename T, typename U>
        concept NotBaseOfConcept = !(BaseOfConcept<T, U>);

        // 数値型か判定するコンセプト
        template <typename T>
        concept ArithmeticConcept = std::is_arithmetic_v<T>;
        // 数値型でないか判定するコンセプト
        template <typename T>
        concept NotArithmeticConcept = !(ArithmeticConcept<T>);

        // クラスか判定するコンセプト
        template <typename T>
        concept ClassConcept = std::is_class_v<T>;
        // クラスではないか判定するコンセプト
        template <typename T>
        concept NotClassConcept = !(ClassConcept<T>);

        // ポインタか判定するコンセプト
        template <typename T>
        concept PointerConcept = std::is_pointer_v<T>;
        // ポインタではないか判定するコンセプト
        template <typename T>
        concept NotPointerConcept = !(PointerConcept<T>);
    }
}


#endif // !I_CONCEPTUTILITY_H
