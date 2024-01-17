#ifndef I_EDITORMAIN_H
#define I_EDITORMAIN_H
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/ProcedureEditorWindow.h>


//----- EtherEngineMainFunction 宣言
namespace EtherEngine {
    public ref class EtherEngineMainFunction {
    public:
        // メイン関数
        // @ Arg1 : コマンドライン(Default : "")
        // @ Arg2 : 
        static void MainFunction(System::String^ cmdLine, int nShowCmd);
    };
}


#endif // !I_EDITORMAIN_H
