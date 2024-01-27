#ifndef I_ASSEMBLYHOLDER_H
#define I_ASSEMBLYHOLDER_H
#include <EngineLibrary/EngineLibraryDefine.h>
#include <EngineLibrary/ManageSingleton.h>


#pragma managed
//----- AssemblyHolder 定義
namespace EtherEngine {
    // ゲームのアセンブリを保持したクラス
    public ref class AssemblyHolder {
        ETHER_ENGINE_MANAGE_SINGLETON(AssemblyHolder);
    public:
        // デストラクタ
        ~AssemblyHolder(void);
        // ファイナライザ
        !AssemblyHolder(void);


        // アセンブリを取得する
        // @ Ret  : 取得したアセンブリ、または現在のアセンブリ
        System::Reflection::Assembly^ GetAssembly(void);


        property System::String^ LoadAssemblyPath {
            System::String^ get(void) { return m_loadAssemblyPath; }
            void set(System::String^ value) { m_loadAssemblyPath = value; }
        }


        // アセンブリを読み込む
        // @ Ret  : アセンブリが読み込めたか
        bool LoadAssembly(void);
        // 現在読み込みアセンブリを削除する
        void DeleteAssembly(void);


        // 現在読み込みアセンブリが存在するか
        // @ Ret  : アセンブリを取得しているか
        bool IsLoadAssemblyEnable(void);

    private:
        System::String^ m_loadAssemblyPath;   // assemblyを読み込むパス
        System::Reflection::Assembly^ m_assembly;   // 現在保持しているアセンブリ
        System::Runtime::Loader::AssemblyLoadContext^ m_assemblyLoadContext;   // 現在保持しているアセンブリ
    };
}


#endif // !I_ASSEMBLYHOLDER_H
