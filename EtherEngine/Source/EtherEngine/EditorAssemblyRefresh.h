#ifndef I_EDITORASSEMBLYREFRESH_H
#define I_EDITORASSEMBLYREFRESH_H
#include <EtherEngine/EditorProgressBar.h>


//----- アセンブリのリフレッシュ関数
namespace EtherEngine {
    // リフレッシュクラス
    class Refresh {
    public:
        // エラー内容
        enum class RefreshStateType {
            Ok = 0,   // 問題なし
            StartRefresh,           // リフレッシュ開始
            CurrentlyRefresh,       // 現在リフレッシュ中
            NoneLoadProject,        // プロジェクトが読み込まれていない
            NoneMSVCMediationInit,  // MSVCMediationが初期化されていない
            InputCommandFailed,     // コマンド入力が失敗した
            CompileError,           // ビルドの際コンパイルエラーが出力された
        };


        // ビルド状況ゲッター
        static bool GetBuildEnd(void) { return ms_isBuildEnd; }
        // ビルド成功ゲッター
        static bool GetBuildSuccess(void) { return ms_isBuildSuccess; }


        // リフレッシュを行う
        // @ Ret  : リフレッシュ状況
        static RefreshStateType AssemblyRefresh(void);
        // 現在のリフレッシュ状況を取得する
        // @ Ret  : 現在のリフレッシュ状況
        static RefreshStateType GetRefreshState(void);
        // ビルドログを読み取る
        // @ Ret  : ビルドログ
        static std::string GetRefreshLog(void);
        
    private:
        static std::shared_ptr<ProgressClass> ms_progress;   // プログレスバー
        static std::string ms_buildLog; // ビルドログ
        static bool ms_isBuildEnd;      // ビルドが終了したか
        static bool ms_isBuildSuccess;  // ビルドが成功したか
    };
}


#endif // !I_EDITORASSEMBLYREFRESH_H
