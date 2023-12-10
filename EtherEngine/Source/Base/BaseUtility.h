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
    namespace Utility {
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


        // 入力ファイルの中身を全て読み取る
        // @ Exce : ファイルが開けない
        // @ Ret  : 読み取った結果
        // @ Arg1 : 読み取るファイル
        std::string RoadFileAll(const std::string& file);


        // 文字列から特定の文字列を置換する
        // @ Ret  : 置換後の文字列
        // @ Arg1 : 検索元文字列
        // @ Arg2 : 置換対象文字列
        // @ Arg3 : 置換後文字列
        std::string StringSubstitution(const std::string& target, const std::string& dest, const std::string& replacement);
    }
}




//----- 便利関数 定義
namespace EtherEngine {
    namespace Utility {
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
}


#endif // !I_BASEUTILITY_H
