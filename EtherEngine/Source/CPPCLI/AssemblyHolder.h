#ifndef I_ASSEMBLYHOLDER_H
#define I_ASSEMBLYHOLDER_H
#include <CPPCLI/ManageSingleton.h>
#include <CPPCLI/CPPCLIUtility.h>


//----- AssemblyHolder 定義
namespace EtherEngine {
    // ゲームのアセンブリを保持したクラス
    class AssemblyHolder {
    public:
        // アセンブリを取得する
        // @ Ret  : 取得したアセンブリ、または現在のアセンブリ
        static System::Reflection::Assembly^ GetAssembly(void);


        // アセンブリを読み込む
        // @ Ret  : アセンブリが読み込めたか
        // @ Arg1 : 読み込むアセンブリ名
        static bool LoadAssembly(const PathClass& assemblyPath);
        // 現在読み込みアセンブリを削除する
        static void DeleteAssembly(void);


        // 現在読み込みアセンブリが存在するか
        // @ Ret  : アセンブリを取得しているか
        static bool IsLoadAssemblyEnable(void);

    private:
        /// @brief コンストラクタ
        AssemblyHolder(void) {}


        static msclr::gcroot<System::Reflection::Assembly^> ms_assembly;   // 現在保持しているアセンブリ
        static bool ms_isBuild;     // buildが成功しているか
        static bool ms_isUpdate;    // ソリューションが更新されているか
    };
}


#endif // !I_ASSEMBLYHOLDER_H
