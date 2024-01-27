#include <EtherEngine/EditorMain.h>
#include <Base/EditorException.h>
#include <EtherEngine/ConvertManage.h>


//----- EtherEngineMainFunction ��`
namespace EtherEngine {
    // ���C���֐�
    void EtherEngineMainFunction::MainFunction(System::String^ cmdLine, int nShowCmd) {
        try {
            EtherEngine::EditorApplication::Get->MainFunction();
        }
        catch (const EditorException& exception) {
            //----- �S��O���b�Z�[�W�擾
            std::string message;
            for (int i = 0;; i++) {
                auto text = exception.GetErrorMessage(i);
                if (text.has_value()) {
                    message += text.value();
                }
                else {
                    break;
                }
            }

            //----- ��O�̑��o
            auto manageException = gcnew System::ApplicationException(UNMANAGE_TO_MANAGE_STRING(message));
            throw gcnew System::Runtime::InteropServices::SEHException("EtherEngine Exception!", manageException);
        }
    }
}
