#include <EtherEngine/EditorMain.h>
#include <Base/EditorException.h>
#include <EngineLibrary/EngineLibraryUtility.h>


//----- EtherEngineMainFunction ��`
namespace EtherEngine {
    // ���C���֐�
    void EtherEngineMainFunction::MainFunction(int windowSizeX, int windowSizeY, System::String^ cmdLine, int nShowCmd) {
        try {
            EtherEngine::EditorApplication::Get()->SetApplicationData(nullptr, nullptr, nShowCmd);    // @ MEMO : ipCmdLine���K�v�������璼����
            EtherEngine::EditorApplication::Get()->SetWindSize({ windowSizeX,windowSizeY });
            EtherEngine::EditorApplication::Get()->BaseMainFunction();
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
