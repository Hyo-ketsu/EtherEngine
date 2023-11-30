#ifndef I_EDITORMAIN_H
#define I_EDITORMAIN_H
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/ProcedureEditorWindow.h>


//----- EtherEngineMainFunction 宣言
namespace EtherEngine {
    public ref class EtherEngineMainFunction {
    public:
        // メイン関数
        // @ Arg1 : ウィンドウ横サイズ
        // @ Arg2 : ウィンドウ縦サイズ
        // @ Arg3 : コマンドライン(Default : "")
        // @ Arg4 : 
        static void MainFunction(int windowSizeX, int windowSizeY, System::String^ cmdLine, int nShowCmd);
    };
}


#endif // !I_EDITORMAIN_H
