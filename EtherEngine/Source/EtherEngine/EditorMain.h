#ifndef I_EDITORMAIN_H
#define I_EDITORMAIN_H
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/ProcedureEditorWindow.h>


//----- EtherEngineMainFunction �錾
namespace EtherEngine {
    public ref class EtherEngineMainFunction {
    public:
        // ���C���֐�
        // @ Arg1 : �R�}���h���C��(Default : "")
        // @ Arg2 : 
        static void MainFunction(System::String^ cmdLine, int nShowCmd);
    };
}


#endif // !I_EDITORMAIN_H
