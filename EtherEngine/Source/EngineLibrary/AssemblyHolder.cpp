#include <EngineLibrary/AssemblyHolder.h>
#include <EngineLibrary/EngineLibraryUtility.h>

using namespace System::Reflection;
using namespace System::Runtime::Loader;


//----- AssemblyHolder 定義
namespace EtherEngine {
    // コンストラクタ
    AssemblyHolder::AssemblyHolder(void) 
        : m_loadAssemblyPath(nullptr) 
        , m_assembly(nullptr)
        , m_assemblyLoadContext(gcnew AssemblyLoadContext("EngineContext", true)) {
    }
    // デストラクタ
    AssemblyHolder::~AssemblyHolder(void) {
        this->!AssemblyHolder();
    }
    // ファイナライザ
    AssemblyHolder::!AssemblyHolder(void) {
        DeleteAssembly();
        m_assemblyLoadContext = nullptr;
    }


    // アセンブリを取得する
    System::Reflection::Assembly^ AssemblyHolder::GetAssembly(void) {
        if (m_assembly == nullptr) {
            //----- assemblyを読み込む
            LoadAssembly();
        }
        else {
            //----- アセンブリ返却
            return m_assembly;
        }
    }


    // アセンブリを読み込む
    bool AssemblyHolder::LoadAssembly(void) {
        //----- dllかファイルチェック
        if (System::IO::Path::Exists(m_loadAssemblyPath) == false) return false;
        if (System::IO::Path::HasExtension(m_loadAssemblyPath) && System::IO::Path::GetExtension(m_loadAssemblyPath) != ".dll") return false;
                
        //----- 読み込む
        m_assembly = m_assemblyLoadContext->LoadFromAssemblyPath(m_loadAssemblyPath);

        return true;
    }
    // 現在読み込みアセンブリを削除する
    void AssemblyHolder::DeleteAssembly(void) {
        m_assembly = nullptr;
        m_assemblyLoadContext->Unload();
        System::GC::Collect();
        System::GC::WaitForPendingFinalizers();
    }


    // 現在読み込みアセンブリが存在するか
    bool AssemblyHolder::IsLoadAssemblyEnable(void) {
        return m_assembly == nullptr ? false : true;
    }
}
