#ifndef I_PROJECTEDITORDATA_H
#define I_PROJECTEDITORDATA_H
#include <Base/EtherEngineUtility.h>
#include <Base/PathClass.h>


//----- ProjectEditorData 宣言
namespace EtherEngine {
    // エディター上でのデータを保持しておくクラス
    class EditorData : public IInOuter {
    public:
        // コンストラクタ
        // @ Arg1 : 開くパス
        EditorData(const PathClass& path);
        // デフォルトコンストラクタ
        EditorData(void) {}
        // デストラクタ
        ~EditorData(void);


        // 現在シーンゲッター
        const SceneIDType& GetCurrentScene(void) const { return m_currentScene; }
        // 現在シーンセッター
        void SetCurrentScene(const SceneIDType& in) { m_currentScene = in; }


        // 外部出力
        Json Output(void) override;
        // 外部入力
        void Input(const Json& input) override;

    private:
        SceneIDType m_currentScene;   // 現在シーン
        PathClass m_path;           // 保持しているパス
    };
}


#endif // !I_PROJECTEDITORDATA_H
