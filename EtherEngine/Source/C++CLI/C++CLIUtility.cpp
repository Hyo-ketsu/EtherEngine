#include <C++CLI/C++CLIUtility.h>
#include <C++CLI/AssemblyHolder.h>
// @ MEMO : w_cahrからcharにしているのでエラー起こすかも
     

//----- 文字列変換関数
namespace EtherEngine {
    // .NET文字列をC++文字列に変換する
    std::string ManageToUn(System::String^ manage) {
        //----- 宣言・取得
        std::string ret;
        auto wchars = manage->ToCharArray();

        //----- 確保
        ret.reserve(wchars->Length);

        //----- 変換
        for (int i = 0; i < wchars->Length; i++) {
            ret.push_back(static_cast<char>(wchars[i]));
        }

        return ret;
    }
    // C++文字列を.NET文字列に変換する
    System::String^ UnToManage(const std::string& un) {
        //----- 宣言
        System::String^ ret;

        //----- 変換
        ret = gcnew System::String(un.c_str());

        //----- 返却
        return ret;
    }
}


//----- 完全修飾名取得関数 宣言
namespace EtherEngine {
    // 完全修飾名を取得する
    std::string GetFullName(const std::string& className, const uint index, const bool isSystem) {
        //----- 変数宣言
        auto manageClassName = UnToManage(className);
        uint currentIndex = 0;

        //----- アセンブリのロード
        auto assembly = AssemblyHolder::GetAssembly();

        //----- 型の取得
        auto types = assembly->GetTypes();

        //----- 全型からの検索
        for each (auto type in types) {
            //----- System名前空間の省略
            if (isSystem == true) {
                if (type->Namespace == "System") {
                    continue;
                }
            }

            //----- 同じ型名か
            if (type->Name == manageClassName) {
                if (index == currentIndex) {
                    //----- インデックスが合う。返却
                    return ManageToUn(type->FullName);
                }
                else {
                    //----- インデックスが合わない。インデックスを進める
                    currentIndex++;
                    continue;
                }
            }

            //----- 完全修飾名が一致するか
            if (type->FullName == manageClassName) {
                return className;
            }
        }

        //----- （恐らく）クラス名が存在しない。例外送出
        throw std::exception("Error! No Class Name!");
    }
    // 完全修飾名を取得する
    System::String^ GetFullName(System::String^ className, const uint index, const bool isSystem) {
        //----- 変数宣言
        uint currentIndex = 0;

        //----- アセンブリのロード
        auto assembly = AssemblyHolder::GetAssembly();

        //----- 型の取得
        auto types = assembly->GetTypes();

        //----- 全型からの検索
        for each (auto type in types) {
            //----- System名前空間の省略
            if (isSystem == true) {
                if (type->Namespace == "System") {
                    continue;
                }
            }

            //----- 同じ型名か
            if (type->Name == className) {
                if (index == currentIndex) {
                    //----- インデックスが合う。返却
                    return type->FullName;
                }
                else {
                    //----- インデックスが合わない。インデックスを進める
                    currentIndex++;
                    continue;
                }
            }

            //----- 完全修飾名が一致するか
            if (type->FullName == className) {
                return className;
            }
        }

        //----- （恐らく）クラス名が存在しない。例外送出
        throw std::exception("Error! No Class Name!");
    }
}
