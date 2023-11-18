#ifndef I_EDITORMAIN_H
#define I_EDITORMAIN_H
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/ProcedureEditorWindow.h>


//----- EtherEngineMainFunction 宣言
namespace EtherEngine {
    public ref class EtherEngineMainFunction {
    public:
        // メイン関数
        // @ Arg1 : アプリケーションインスタンス
        // @ Arg2 : ウィンドウ横サイズ
        // @ Arg3 : ウィンドウ縦サイズ
        // @ Arg4 : コマンドライン(Default : "")
        // @ Arg5 : 
        static void MainFunction(System::IntPtr hInstance, int windowSizeX, int windowSizeY, System::String^ cmdLine, int nShowCmd);
    };
}


#endif // !I_EDITORMAIN_H
