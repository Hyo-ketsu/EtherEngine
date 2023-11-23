#include <EtherEngine/EditorMain.h>
#include <EngineLibrary/EngineLibraryUtility.h>


//----- EtherEngineMainFunction 定義
namespace EtherEngine {
    // メイン関数
    void EtherEngineMainFunction::MainFunction(System::IntPtr hInstance, int windowSizeX, int windowSizeY, System::String^ cmdLine, int nShowCmd) {
#ifdef _DEBUG
        try {
            EtherEngine::EditorApplication::Get()->SetApplicationData(static_cast<HINSTANCE>(hInstance.ToPointer()), nullptr, nShowCmd);    // @ MEMO : ipCmdLineが必要だったら直して
            EtherEngine::EditorApplication::Get()->SetWindSize({ windowSizeX,windowSizeY });
            EtherEngine::EditorApplication::Get()->BaseMainFunction();
        }
        catch (const std::exception& exception) {
            auto manageException = gcnew System::ApplicationException(gcnew System::String(exception.what()));
            throw gcnew System::Runtime::InteropServices::SEHException("EtherEngine Exception!", manageException);
        }
#else
        EtherEngine::EditorApplication::Get()->SetApplicationData(static_cast<HINSTANCE>(hInstance.ToPointer()), nullptr, nShowCmd);    // @ MEMO : ipCmdLineが必要だったら直して
        EtherEngine::EditorApplication::Get()->SetWindSize({ windowSizeX,windowSizeY });
        EtherEngine::EditorApplication::Get()->BaseMainFunction();
#endif
    }
}
