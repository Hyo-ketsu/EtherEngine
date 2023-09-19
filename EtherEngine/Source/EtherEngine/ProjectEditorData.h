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
        // コンストラクタ
        // @ Arg1 : 開くパス
        ProjectEditorData(const PathClass& path);
        // 作成のみ行うコンストラクタ
        ProjectEditorData(void) {}
        // デストラクタ
        ~ProjectEditorData(void) {}


        // 現在シーンゲッター
        const SceneData& GetCurrentScene(void) const { return m_currentScene; }
        // 現在シーンセッター
        void SetCurrentScene(const SceneData& in) { m_currentScene = in; }


        // 外部出力
        Json Output(void) override;
        // 外部入力
        void Input(const Json& input) override;

    private:
        SceneData m_currentScene;    // 現在シーン
    };
}


#endif // !I_PROJECTEDITORDATA_H
