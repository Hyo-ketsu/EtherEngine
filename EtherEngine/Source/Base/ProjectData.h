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
        // @ Arg1 : 読み込みファイルパス
        ProjectData(const PathClass& path);
        // デフォルトコンストラクタ
        ProjectData(void) {}
        // デストラクタ
        ~ProjectData(void);


        // MSBuildパスセッター
        const PathClass& GetMSBuildPath(void) const { return m_msbuildPath; }
        // MSBuildパスゲッター
        void SetMSBuildPath(const PathClass& in) { m_msbuildPath = in; }


        // 出力する
        Json Output(void) override;
        // 入力する
        void Input(const Json& input) override;

    private:
        PathClass m_msbuildPath;    // MSBuildのあるパス
        PathClass m_path;           // 情報自体を保持しているクラス
    };
}


#endif // !I_PROJECTDATA_H
