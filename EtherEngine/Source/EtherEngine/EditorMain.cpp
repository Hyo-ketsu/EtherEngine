#include <EtherEngine/EditorMain.h>
#include <Base/EditorException.h>
#include <EngineLibrary/EngineLibraryUtility.h>


//----- EtherEngineMainFunction 定義
namespace EtherEngine {
    // メイン関数
    void EtherEngineMainFunction::MainFunction(System::IntPtr hInstance, int windowSizeX, int windowSizeY, System::String^ cmdLine, int nShowCmd) {
#ifdef _DEBUG
        try {
            EtherEngine::EditorApplication::Get()->SetApplicationData(static_cast<HINSTANCE>(hInstance.ToPointer()), nullptr, nShowCmd);    // @ MEMO : ipCmdLineが必要だったら直して
            EtherEngine::EditorApplication::Get()->SetWindSize({ windowSizeX,windowSizeY });
            EtherEngine::EditorApplication::Get()->BaseMainFunction();
        }
        catch (const std::exception& exception) {
            auto manageException = gcnew System::ApplicationException(gcnew System::String(exception.what()));
            throw gcnew System::Runtime::InteropServices::SEHException("EtherEngine Exception!", manageException);
        }
        catch (const EditorException& exception) {
            //----- 全例外メッセージ取得
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

            //----- 例外の送出
            auto manageException = gcnew System::ApplicationException(UNMANAGE_TO_MANAGE_STRING(message));
            throw gcnew System::Runtime::InteropServices::SEHException("EtherEngine Exception!", manageException);
        }
#else
        EtherEngine::EditorApplication::Get()->SetApplicationData(static_cast<HINSTANCE>(hInstance.ToPointer()), nullptr, nShowCmd);    // @ MEMO : ipCmdLineが必要だったら直して
        EtherEngine::EditorApplication::Get()->SetWindSize({ windowSizeX,windowSizeY });
        EtherEngine::EditorApplication::Get()->BaseMainFunction();
#endif
    }
}
