#ifndef I_ETHERENGINEUTILITY_H
#define I_ETHERENGINEUTILITY_H
#include <Base/BaseDefines.h>


// DLL呼び出し用
#define DLL_CALL(ReturnType) extern "C" __declspec(dllexport) ReturnType  


//----- インターフェース定義
namespace EtherEngine {
    // Serialize・Deserialize用インターフェース(Json想定)
    class IInOuter {
    public:
        // 出力する
        // @ Ret  : 出力Json
        virtual Json Output(void) = 0;
        // 入力する
        // @ Arg1 : 入力文字列
        virtual void Input(const Json& input) = 0;
        // 入力する
        // @ Arg1 : 入力文字列
        void Input(const std::string& input);
    };
}


//----- 便利関数 定義
namespace EtherEngine {
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


//----- 重複オブジェクト名命名定義
namespace EtherEngine {
    namespace Utilty {
        // 重複オブジェクト名命名方法
        enum class DuplicationNameObjectName {
            ParenthesesNumber = 0,  // Hoge (1)
            Number,                 // Hoge 1
            UnderscoreNumber        // Hoge_1
        };


        // 重複したオブジェクトに名前を付ける
        // @ Ret  : 変換後の名前
        // @ Arg1 : 対象名
        // @ Arg2 : 何個目の同名オブジェクトか（1 ~ ）
        // @ Arg3 : 命名方法
        std::string DuplicationName(const std::string& name, const uint number, const DuplicationNameObjectName& type);
        // 重複したオブジェクトに名前を付ける
        // @ Arg1 : 対象名
        // @ Arg2 : 何個目の同名オブジェクトか（1 ~ ）
        // @ Arg3 : 命名方法
        void DuplicationName(std::string* name, const uint number, const DuplicationNameObjectName& type);
        // 重複したオブジェクト名か判定する
        // @ Ret  : 重複していれば true
        // @ Arg1 : 重複判定対象
        // @ Arg2 : 元の名前
        // @ Arg3 : 何個目の同名オブジェクトか（1 ~ ）
        // @ Arg4 : 命名方法
        bool IsDuplicationName(const std::string& name, const std::string& base, const uint number, const DuplicationNameObjectName& type);
    }
}


#endif // !I_ETHERENGINEUTILITY_H
