#include <DirectX/GameApplication.h>
#include <DirectX/ProcedureGameWindow.h>


//----- DirectXメイン関数
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
    EtherEngine::GameApplication::Get()->SetApplicationData(hInstance, lpCmdLine, nShowCmd);
    EtherEngine::GameApplication::Get()->SetWindSize({ 1024,768 });   // 仮
    EtherEngine::GameApplication::Get()->SetProc(WindowGameProcedure);   // 仮
    EtherEngine::GameApplication::Get()->MainFunction();
}
