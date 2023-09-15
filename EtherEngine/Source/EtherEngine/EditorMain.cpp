#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/ProcedureEditorWindow.h>


//----- DirectXƒƒCƒ“ŠÖ”
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
    EtherEngine::EditorApplication::Get()->SetApplicationData(hInstance, lpCmdLine, nShowCmd);
    EtherEngine::EditorApplication::Get()->SetWindSize({ 1024,768 });   // ‰¼
    EtherEngine::EditorApplication::Get()->SetProc((WNDPROC*)&EtherEngine::WindowEditorProcedure);
    EtherEngine::EditorApplication::Get()->BaseMainFunction();
}
