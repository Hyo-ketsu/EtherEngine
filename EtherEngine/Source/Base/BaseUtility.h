#ifndef I_BASEUTILITY_H
#define I_BASEUTILITY_H


namespace {
    template <typename T, typename U>
    concept equalConcept = requires(T t, U u) { t == u; };
}


//----- •Ö—˜ŠÖ” éŒ¾
namespace EtherEngine {
    // ‘S‚Ä‚Ì“ü—Í‚Æ”äŠr‚·‚é
    // @ Ret  : ”äŠrŒ‹‰Ê
    // @ Temp : ”äŠrŒ³
    // @ Temps: ”äŠr‘ÎÛ
    // @ Arg1 : ”äŠrŒ³
    // @ Arg2 : ‘S‚Äor‚È‚ç true ‘S‚Äand‚È‚ç false
    // @ Args : ”äŠr‘ÎÛ
    template <typename TargetType, equalConcept<TargetType> ArgType, equalConcept<TargetType> ...ArgsType>
    bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg, const ArgsType& ...args);
    // ‘S‚Ä‚Ì“ü—Í‚Æ”äŠr‚·‚é
    // @ Ret  : ”äŠrŒ‹‰Ê
    // @ Temp : ”äŠrŒ³
    // @ Arg1 : ”äŠrŒ³
    // @ Arg2 : ‘S‚Äor‚È‚ç true ‘S‚Äand‚È‚ç false
    template <typename TargetType, equalConcept<TargetType> ArgType>
    bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg);
}




//----- •Ö—˜ŠÖ” ’è‹`
namespace EtherEngine {
    // ‘S‚Ä‚Ì“ü—Í‚Æ”äŠr‚·‚é
    // @ Ret  : ”äŠrŒ‹‰Ê
    // @ Temp : ”äŠrŒ³
    // @ Temps: ”äŠr‘ÎÛ
    // @ Arg1 : ”äŠrŒ³
    // @ Arg2 : ‘S‚Äor‚È‚ç true ‘S‚Äand‚È‚ç false
    // @ Args : ”äŠr‘ÎÛ
    template <typename TargetType, equalConcept<TargetType> ArgType, equalConcept<TargetType> ...ArgsType>
    bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg, const ArgsType& ...args) {
        //----- Ä‹A‚µ‚Ä”»’è
        if (isOr) {
            return target == arg || IsInputComparison(target, isOr, args...);
        }
        else {
            return target == arg && IsInputComparison(target, isOr, args...);
        }
    }
    // ‘S‚Ä‚Ì“ü—Í‚Æ”äŠr‚·‚é
    // @ Ret  : ”äŠrŒ‹‰Ê
    // @ Temp : ”äŠrŒ³
    // @ Arg1 : ”äŠrŒ³
    // @ Arg2 : ‘S‚Äor‚È‚ç true ‘S‚Äand‚È‚ç false
    template <typename TargetType, equalConcept<TargetType> ArgType>
    bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg) {
        return target == arg;
    }
}


#endif // !I_BASEUTILITY_H
