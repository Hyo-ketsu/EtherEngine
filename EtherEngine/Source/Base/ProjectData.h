#ifndef I_PROJECTDATA_H
#define I_PROJECTDATA_H
#include <Base/PathClass.h>
#include <Base/EtherEngineUtility.h>


//----- ProjectData 宣言
namespace EtherEngine {
    // プロジェクトに関するデータを保持したクラス
    class ProjectData : public IInOuter {
    public:
        // コンストラクタ
        // @ Arg1 : 読み込みファイルパス(Default : パス指定なし)
        ProjectData(const PathClass& path);
        // 作成のみ行うコンストラクタ
        ProjectData(void) {}


        // コマンドプロンプトパスゲッター
        const PathClass& GetCmdPath(void) const { return m_cmdPath; }
        // コマンドプロンプトパスセッター
        void SetCmdPath(const PathClass& in) { m_cmdPath = in; }
        // MSVCパスゲッター
        const PathClass& GetMsvcPath(void) const { return m_msvcPath; }
        // MSVCパスセッター
        void SetMsvcPath(const PathClass& in) { m_msvcPath = in; }
        // VisualStudioパスセッター
        const PathClass& GetVisualStudioPath(void) const { return m_visualStudioPath; }
        // VisualStudioパスゲッター
        void SetVisualStudioPath(const PathClass& in) { m_visualStudioPath = in; }


        // 出力する
        Json Output(void) override;
        // 入力する
        void Input(const Json& input) override;

    private:
        PathClass m_cmdPath;    // コマンドプロンプトが存在するパス
        PathClass m_msvcPath;   // MSVCがあるパス
        PathClass m_visualStudioPath;   // VisualStudioのあるパス
    };
}


#endif // !I_PROJECTDATA_H
