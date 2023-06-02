#ifndef I_CONCEPTUTILITY_H
#define I_CONCEPTUTILITY_H


namespace EtherEngine {
    // ����̌^�Ɠ����^�����肷��R���Z�v�g
    template <typename T, typename U>
    concept SameConcept = std::is_same_v<T, U>;
    // ����̌^�ƈႢ�������肷��R���Z�v�g
    template <typename T, typename U>
    concept NotSameConcept = !(std::is_same_v<T, U>);
}


#endif // !I_CONCEPTUTILITY_H
