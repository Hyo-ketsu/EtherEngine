#include <EngineLibrary/AssemblyHolder.h>


//----- AssemblyHolder 定義
namespace EtherEngine {
    // アセンブリを取得する
    System::Reflection::Assembly^ AssemblyHolder::GetAssembly(void) {
        if (static_cast<System::Reflection::Assembly^>(ms_assembly) == nullptr) {
            //----- 何も読み込んでいない。現在のアセンブリを取得
            return System::Reflection::Assembly::GetCallingAssembly();
        }
        else {
            //----- アセンブリ返却
            return ms_assembly;
        }
    }


    // アセンブリを読み込む
    bool AssemblyHolder::LoadAssembly(const PathClass& assemblyPath) {
        //----- dllかファイルチェック
        if (assemblyPath.IsExists() == false) return false;
        if (assemblyPath.HasExtension() && assemblyPath.GetExtension() != "dll") return false;

        //----- 読み込む
        ms_assembly = System::Reflection::Assembly::LoadFrom(UnToManage(assemblyPath));
        return true;
    }
    // 現在読み込みアセンブリを削除する
    void AssemblyHolder::DeleteAssembly(void) {
        ms_assembly = nullptr;
    }


    // 現在読み込みアセンブリが存在するか
    bool AssemblyHolder::IsLoadAssemblyEnable(void) {
        return static_cast<System::Reflection::Assembly^>(ms_assembly) == nullptr ? false : true;
    }


    msclr::gcroot<System::Reflection::Assembly^> AssemblyHolder::ms_assembly = nullptr;   // 現在保持しているアセンブリ
    bool AssemblyHolder::ms_isBuild = true;      // buildが成功しているか
    bool AssemblyHolder::ms_isUpdate = false;    // ソリューションが更新されているか
}
