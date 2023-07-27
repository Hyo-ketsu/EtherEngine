#ifndef I_SCENELOADER_H
#define I_SCENELOADER_H
#include <Base/Singleton.h>
#include <Base/ConceptUtility.h>
#include <Base/Scene.h>


//----- SceneLoader 宣言
namespace EtherEngine {
    // シーンを総括するクラス
    class SceneLoader : public Singleton<SceneLoader> {
    public:
        // デストラクタ
        ~SceneLoader(void) override;


        // 現在シーン情報ゲッター
        const std::optional<SceneData>& GetCurrentSceneData(void) const { return m_currentSceneData; }


        // シーン情報登録
        
        // シーン追加
        // @ MEMO : 未実装
        // @ Arg1 : 追加するシーン
        void AddScene(const SceneData data);
        // シーン削除
        // @ MEMO : 未実装
        // @ Arg1 : 削除するシーン
        void DeleteScene(const SceneData data);
        // シーン削除
        // @ MEMO : 未実装
        // @ Memo : 全てのシーンの削除を行います
        void DeleteScene(void);
        // シーン移動
        // @ MEMO : 未実装
        // @ Arg1 : 移動するシーン
        void MoveScene(const SceneData data);


    private:
        // コンストラクタ
        SceneLoader(void);

        
        friend class Singleton<SceneLoader>;

        std::vector<SceneData>   m_sceneData;  // 現在保持しているシーンの情報
        std::optional<SceneData> m_currentSceneData;    // 現在初期化しているシーンの情報
    };
}


#endif // !I_SCENELOADER_H
