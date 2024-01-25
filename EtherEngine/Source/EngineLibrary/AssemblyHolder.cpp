#include <EngineLibrary/AssemblyHolder.h>
#include <EngineLibrary/EngineLibraryUtility.h>

using namespace System::Reflection;
using namespace System::Runtime::Loader;


//----- AssemblyHolder 定義
namespace EtherEngine {
    // コンストラクタ
    AssemblyHolder::AssemblyHolder(void) 
        : ms_loadAssemblyPath(nullptr) 
        , ms_assembly(nullptr)
        , ms_assemblyLoadContext(gcnew AssemblyLoadContext("EngineContext", true)) {
    }
    // デストラクタ
    AssemblyHolder::~AssemblyHolder(void) {
        this->!AssemblyHolder();
    }
    // ファイナライザ
    AssemblyHolder::!AssemblyHolder(void) {
        DeleteAssembly();
        ms_assemblyLoadContext = nullptr;
    }


    // アセンブリを取得する
    System::Reflection::Assembly^ AssemblyHolder::GetAssembly(void) {
        if (ms_assembly == nullptr) {
            //----- assemblyを読み込む
            LoadAssembly();
        }
        else {
            //----- アセンブリ返却
            return ms_assembly;
        }
    }


    // アセンブリを読み込むh
    bool AssemblyHolder::LoadAssembly(void) {
        //----- dllかファイルチェック
        if (System::IO::Path::Exists(ms_loadAssemblyPath) == false) return false;
        if (System::IO::Path::HasExtension(ms_loadAssemblyPath) && System::IO::Path::GetExtension(ms_loadAssemblyPath) != ".dll") return false;
                

        //----- 読み込む
        ms_assembly = ms_assemblyLoadContext->LoadFromAssemblyPath(ms_loadAssemblyPath);

        return true;
    }
    // 現在読み込みアセンブリを削除する
    void AssemblyHolder::DeleteAssembly(void) {
        ms_assembly = nullptr;
        ms_assemblyLoadContext->Unload();
        System::GC::Collect();
        System::GC::WaitForPendingFinalizers();
    }


    // 現在読み込みアセンブリが存在するか
    bool AssemblyHolder::IsLoadAssemblyEnable(void) {
        return ms_assembly == nullptr ? false : true;
    }
}
