#include <EngineLibrary/AssemblyHolder.h>
#include <EngineLibrary/EngineLibraryUtility.h>


//----- AssemblyHolder 定義
namespace EtherEngine {
    // アセンブリを取得する
    System::Reflection::Assembly^ AssemblyHolder::GetAssembly(void) {
        if (ms_assembly == nullptr) {
            //----- 何も読み込んでいない。現在のアセンブリを取得
            return System::Reflection::Assembly::GetCallingAssembly();
        }
        else {
            //----- アセンブリ返却
            return ms_assembly;
        }
    }


    // アセンブリを読み込む
    bool AssemblyHolder::LoadAssembly(PathString^ assemblyPath) {
        //----- dllかファイルチェック
        if (System::IO::Path::Exists(assemblyPath->ToString()) == false) return false;
        if (System::IO::Path::HasExtension(assemblyPath->ToString()) && System::IO::Path::GetExtension(assemblyPath->ToString()) != ".dll") return false;

        //----- 読み込む
        ms_assembly = System::Reflection::Assembly::LoadFrom(assemblyPath->ToString());
        return true;
    }
    // 現在読み込みアセンブリを削除する
    void AssemblyHolder::DeleteAssembly(void) {
        ms_assembly = nullptr;
    }


    // 現在読み込みアセンブリが存在するか
    bool AssemblyHolder::IsLoadAssemblyEnable(void) {
        return ms_assembly == nullptr ? false : true;
    }
}
