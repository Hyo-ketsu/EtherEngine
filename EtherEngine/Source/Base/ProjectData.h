#ifndef I_PROJECTDATA_H
#define I_PROJECTDATA_H
#include <Base/PathClass.h>


//----- ProjectData 宣言
namespace EtherEngine {
    // プロジェクトに関するデータを保持したクラス
    class ProjectData {
    public:
        // @ MEMO : 現状ファイルから読込する機能は作成していません。後で作ってください
        // コンストラクタ
        // @ Arg1 : 読み込みファイルパス(Default : パス指定なし)
        ProjectData(const PathClass& path = PathClass(""));


        // コマンドプロンプトパスゲッター
        const PathClass& GetCmdPath(void) const { return m_cmdPath; }
        // コマンドプロンプトパスセッター
        void SetCmdPath(const PathClass& in) { m_cmdPath = in; }

        // MSVCパスゲッター
        const PathClass& GetMsvcPath(void) const { return m_msvcPath; }
        // MSVCパスセッター
        void SetMsvcPath(const PathClass& in) { m_msvcPath = in; }

    private:
        PathClass m_cmdPath;    // コマンドプロンプトが存在するパス
        PathClass m_msvcPath;   // MSVCがあるパス
    };
}


#endif // !I_PROJECTDATA_H
