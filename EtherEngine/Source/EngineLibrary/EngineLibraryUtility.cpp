#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/AssemblyHolder.h>
// @ MEMO : w_cahrからcharにしているのでエラー起こすかも
     

//----- 文字列変換関数
namespace EtherEngine {
}


//----- 完全修飾名取得関数 宣言
namespace EtherEngine {
    // 完全修飾名を取得する
    std::string GetFullName(const std::string& className, const uint index, const bool isSystem) {
        //----- 変数宣言
        System::String^ manageClassName = gcnew System::String(className.c_str());
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
                    return ManageToUnmanage::String(type->FullName);
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
