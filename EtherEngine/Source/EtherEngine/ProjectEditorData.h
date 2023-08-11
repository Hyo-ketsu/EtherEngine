#ifndef I_PROJECTEDITORDATA_H
#define I_PROJECTEDITORDATA_H
#include <Base/EtherEngineUtility.h>
#include <Base/PathClass.h>
#include <Base/Scene.h>


//----- ProjectEditorData 宣言
namespace EtherEngine {
    // エディター上でのデータを保持しておくクラス
    class ProjectEditorData : public IInOuter {
    public:
        // @ MEMO : 後で書くのでデフォルト引数あり
        // コンストラクタ
        // @ Arg1 : 開くパス
        ProjectEditorData(const PathClass& path = "");
        // デストラクタ
        ~ProjectEditorData(void) {}


        // 外部出力
        Json Output(void) override;
        // 外部入力
        void Input(const Json& input) override;

    private:
        std::optional<SceneData> m_currentScene;    // 現在開いているシーン
    };
}


#endif // !I_PROJECTEDITORDATA_H
