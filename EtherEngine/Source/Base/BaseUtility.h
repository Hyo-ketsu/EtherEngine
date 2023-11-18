#ifndef I_BASEUTILITY_H
#define I_BASEUTILITY_H


namespace {
    template <typename T, typename U>
    concept equalConcept = requires(T t, U u) { t == u; };
}


//----- 生存確認クラス 宣言
namespace EtherEngine {
    // 生存確認用インターフェース 宣言
    class EnableCheckClass {
    public:
        // コピーコンストラクタ
        EnableCheckClass(const EnableCheckClass& copy);


        // 生存確認用のキーを取得する
        // @ Ret  : 取得したキー
        std::weak_ptr<void> GetEnableKey(void);

    protected:
        // コンストラクタ
        EnableCheckClass(void); 

    private:
        std::shared_ptr<void> m_sharedPtr;
    };
}


//----- 便利関数 宣言
namespace EtherEngine {
    // 全ての入力と比較する
    // @ Ret  : 比較結果
    // @ Temp : 比較元
    // @ Temps: 比較対象
    // @ Arg1 : 比較元
    // @ Arg2 : 全てorなら true 全てandなら false
    // @ Args : 比較対象
    template <typename TargetType, equalConcept<TargetType> ArgType, equalConcept<TargetType> ...ArgsType>
    bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg, const ArgsType& ...args);
    // 全ての入力と比較する
    // @ Ret  : 比較結果
    // @ Temp : 比較元
    // @ Arg1 : 比較元
    // @ Arg2 : 全てorなら true 全てandなら false
    template <typename TargetType, equalConcept<TargetType> ArgType>
    bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg);
}




//----- 便利関数 定義
namespace EtherEngine {
    // 全ての入力と比較する
    // @ Ret  : 比較結果
    // @ Temp : 比較元
    // @ Temps: 比較対象
    // @ Arg1 : 比較元
    // @ Arg2 : 全てorなら true 全てandなら false
    // @ Args : 比較対象
    template <typename TargetType, equalConcept<TargetType> ArgType, equalConcept<TargetType> ...ArgsType>
    bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg, const ArgsType& ...args) {
        //----- 再帰して判定
        if (isOr) {
            return target == arg || IsInputComparison(target, isOr, args...);
        }
        else {
            return target == arg && IsInputComparison(target, isOr, args...);
        }
    }
    // 全ての入力と比較する
    // @ Ret  : 比較結果
    // @ Temp : 比較元
    // @ Arg1 : 比較元
    // @ Arg2 : 全てorなら true 全てandなら false
    template <typename TargetType, equalConcept<TargetType> ArgType>
    bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg) {
        return target == arg;
    }
}


#endif // !I_BASEUTILITY_H
