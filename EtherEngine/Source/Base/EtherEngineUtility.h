#ifndef I_ETHERENGINEUTILITY_H
#define I_ETHERENGINEUTILITY_H


//----- 重複オブジェクト名命名定義
namespace EtherEngine {
    namespace Utilty {
        // 重複オブジェクト名命名方法
        enum class DuplicationNameObjectName {
            PARENTHESES_NUMBER = 0, // Hoge (1)
            NUMBER,                 // Hoge 1
            UNDERSCORE_NUMBER       // Hoge_1
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
