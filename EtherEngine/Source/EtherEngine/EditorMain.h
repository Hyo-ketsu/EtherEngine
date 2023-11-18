#ifndef I_EDITORMAIN_H
#define I_EDITORMAIN_H
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/ProcedureEditorWindow.h>


//----- EtherEngineMainFunction �錾
namespace EtherEngine {
    public ref class EtherEngineMainFunction {
    public:
        // ���C���֐�
        // @ Arg1 : �A�v���P�[�V�����C���X�^���X
        // @ Arg2 : �E�B���h�E���T�C�Y
        // @ Arg3 : �E�B���h�E�c�T�C�Y
        // @ Arg4 : �R�}���h���C��(Default : "")
        // @ Arg5 : 
        static void MainFunction(System::IntPtr hInstance, int windowSizeX, int windowSizeY, System::String^ cmdLine, int nShowCmd);
    };
}


#endif // !I_EDITORMAIN_H
