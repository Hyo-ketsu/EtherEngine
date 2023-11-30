#include <EtherEngine/EditorAssemblyRefresh.h>
#include <EtherEngine/ProjectMediation.h>
#include <EtherEngine/CommandPrompt.h>
#include <EtherEngine/EditorDefine.h>


//----- アセンブリのリフレッシュ関数
namespace EtherEngine {
    // リフレッシュを行う
    // @ MEMO : 暫定的処理。プログレスバーなどの表示を行わない
    Refresh::RefreshStateType Refresh::AssemblyRefresh(void) {
        //----- 既にリフレッシュを行っているか
        if (ms_cmd != nullptr) {
            return RefreshStateType::CurrentlyRefresh;
        }

        //----- まずプロジェクトが既に読み込みできるか(ガード節
        if (ProjectMediation::Get()->GetVcxproj().Get() == "") return RefreshStateType::NoneLoadProject;
        
        //----- ビルドを行う
        try {
            ms_cmd = std::make_unique<CommandPrompt>();
            ms_cmd->CD(ProjectMediation::Get()->GetVcxproj());
            ms_cmd->Write(std::string("MSBuild.exe ") + ProjectMediation::Get()->GetSln().Get() + " && " +
                +"if %ERRORLEVEL%==0 (echo " + EditorDefine::EDITOR_BUILD_OK + ")" + " ELSE " + "echo " + EditorDefine::EDITOR_BUILD_ERROR + ")");
        }
        catch (...) {
            return RefreshStateType::InputCommandFailed;
        }

        //----- プログレスバー出力

        //----- ビルド開始
        ms_isBuildEnd = false;
        ms_isBuildSuccess = false;
        return RefreshStateType::StartRefresh;
    }


    // 現在のリフレッシュ状況を取得する
    Refresh::RefreshStateType Refresh::GetRefreshState(void) {
        //----- ログを取得する
        Refresh::GetRefreshLog();

        //----- リフレッシュ中か
        if (ms_isBuildEnd == false) return RefreshStateType::CurrentlyRefresh;

        //----- リフレッシュが成功したか
        if (ms_isBuildSuccess) {
            return RefreshStateType::Ok;
        }
        else {
            return RefreshStateType::CompileError;
        }
    }
    // ビルドログを読み取る
    std::string Refresh::GetRefreshLog(void) {
        //----- ログ取得
        auto logText = ms_cmd->Read();

        //----- 特定のメッセージが出力されているか
        if (logText.find(EditorDefine::EDITOR_BUILD_OK) != std::string::npos) {
            ms_isBuildEnd = true;
            ms_isBuildSuccess = true;
        }
        if (logText.find(EditorDefine::EDITOR_BUILD_ERROR) != std::string::npos) {
            ms_isBuildEnd = true;
            ms_isBuildSuccess = false;
        }

        //----- ログを追加
        ms_buildLog += logText;

        //----- コマンドプロンプトを削除
        if (ms_isBuildEnd) {
            ms_cmd.reset();
        }

        //----- ログの返却
        return ms_buildLog;
    }


    std::unique_ptr<CommandPrompt> Refresh::ms_cmd;   // 保持しているコマンドプロンプト
    std::string Refresh::ms_buildLog;        // ビルドログ
    bool Refresh::ms_isBuildEnd = true;      // ビルドが終了したか
    bool Refresh::ms_isBuildSuccess = false; // ビルドが成功したか
}
