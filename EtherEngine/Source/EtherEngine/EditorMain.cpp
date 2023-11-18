#include <EtherEngine/EditorMain.h>


//----- EtherEngineMainFunction 定義
namespace EtherEngine {
    // メイン関数
    void EtherEngineMainFunction::MainFunction(System::IntPtr hInstance, int windowSizeX, int windowSizeY, System::String^ cmdLine, int nShowCmd) {
        EtherEngine::EditorApplication::Get()->SetApplicationData(static_cast<HINSTANCE>(hInstance.ToPointer()), nullptr, nShowCmd);    // @ MEMO : ipCmdLineが必要だったら直して
        EtherEngine::EditorApplication::Get()->SetWindSize({ windowSizeX,windowSizeY });
        EtherEngine::EditorApplication::Get()->BaseMainFunction();
    }
}
