#ifndef I_BASEUTILITY_H
#define I_BASEUTILITY_H


namespace {
    template <typename T, typename U>
    concept equalConcept = requires(T t, U u) { t == u; };
}


//----- �֗��֐� �錾
namespace EtherEngine {
    // �S�Ă̓��͂Ɣ�r����
    // @ Ret  : ��r����
    // @ Temp : ��r��
    // @ Temps: ��r�Ώ�
    // @ Arg1 : ��r��
    // @ Arg2 : �S��or�Ȃ� true �S��and�Ȃ� false
    // @ Args : ��r�Ώ�
    template <typename TargetType, equalConcept<TargetType> ArgType, equalConcept<TargetType> ...ArgsType>
    bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg, const ArgsType& ...args);
    // �S�Ă̓��͂Ɣ�r����
    // @ Ret  : ��r����
    // @ Temp : ��r��
    // @ Arg1 : ��r��
    // @ Arg2 : �S��or�Ȃ� true �S��and�Ȃ� false
    template <typename TargetType, equalConcept<TargetType> ArgType>
    bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg);
}




//----- �֗��֐� ��`
namespace EtherEngine {
    // �S�Ă̓��͂Ɣ�r����
    // @ Ret  : ��r����
    // @ Temp : ��r��
    // @ Temps: ��r�Ώ�
    // @ Arg1 : ��r��
    // @ Arg2 : �S��or�Ȃ� true �S��and�Ȃ� false
    // @ Args : ��r�Ώ�
    template <typename TargetType, equalConcept<TargetType> ArgType, equalConcept<TargetType> ...ArgsType>
    bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg, const ArgsType& ...args) {
        //----- �ċA���Ĕ���
        if (isOr) {
            return target == arg || IsInputComparison(target, isOr, args...);
        }
        else {
            return target == arg && IsInputComparison(target, isOr, args...);
        }
    }
    // �S�Ă̓��͂Ɣ�r����
    // @ Ret  : ��r����
    // @ Temp : ��r��
    // @ Arg1 : ��r��
    // @ Arg2 : �S��or�Ȃ� true �S��and�Ȃ� false
    template <typename TargetType, equalConcept<TargetType> ArgType>
    bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg) {
        return target == arg;
    }
}


#endif // !I_BASEUTILITY_H
