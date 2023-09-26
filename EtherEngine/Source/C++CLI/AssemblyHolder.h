#ifndef I_ASSEMBLYHOLDER_H
#define I_ASSEMBLYHOLDER_H
#include <C++CLI/ManageSingleton.h>
#include <C++CLI/C++CLIUtility.h>


//----- AssemblyHolder 定義
namespace EtherEngine {
    // ゲームのアセンブリを保持したクラス
    static public ref class AssemblyHolder {
    public:
        // アセンブリを取得する
        // @ Ret  : 取得したアセンブリ、または現在のアセンブリ
        static System::Reflection::Assembly^ GetAssembly(void) {
            if (ms_assembly == nullptr) {
                //----- 何も読み込んでいない。現在のアセンブリを取得
                return System::Reflection::Assembly::GetCallingAssembly();
            }
            else {
                //----- アセンブリ返却
                return ms_assembly;
            }
        }
        // 現在読み込みアセンブリが存在するか
        // @ Ret  : アセンブリを取得しているか
        static bool IsLoadAssemblyEnable(void) {
            return ms_assembly == nullptr ? false : true;
        }


        // アセンブリを読み込む
        // @ Ret  : アセンブリが読み込めたか
        // @ Arg1 : 読み込むアセンブリ名
        static bool LoadAssembly(const PathClass& assemblyPath) {
            //----- dllかファイルチェック
            if (assemblyPath.IsExists() == false) return false;
            if (assemblyPath.HasExtension() && assemblyPath.GetExtension() != "dll") return false;

            //----- 読み込む
            ms_assembly = System::Reflection::Assembly::LoadFrom(UnToManage(assemblyPath));
        }
        // 現在読み込みアセンブリを削除する
        static void DeleteAssembly(void) {
            ms_assembly = nullptr;
        }

    private:
        static System::Reflection::Assembly^ ms_assembly = nullptr;   // 現在保持しているアセンブリ
    };
}


#endif // !I_ASSEMBLYHOLDER_H
