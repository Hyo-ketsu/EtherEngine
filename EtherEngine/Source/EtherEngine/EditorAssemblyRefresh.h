#ifndef I_EDITORASSEMBLYREFRESH_H
#define I_EDITORASSEMBLYREFRESH_H


//----- アセンブリのリフレッシュ関数
namespace EtherEngine {
    namespace Refresh {
        // エラー内容
        enum class RefreshStateType {
            Ok = 0,   // 問題なし
            CurrentlyRefresh,       // 現在リフレッシュ中
            NoneLoadProject,        // プロジェクトが読み込まれていない
            NoneMSVCMediationInit,  // MSVCMediationが初期化されていない
            InputCommandFailed,     // コマンド入力が失敗した
            CompileError,           // ビルドの際コンパイルエラーが出力された
        };


        // リフレッシュを行う
        // @ Ret  : リフレッシュ状況
        RefreshStateType AssemblyRefresh(void);
    }
}


#endif // !I_EDITORASSEMBLYREFRESH_H
