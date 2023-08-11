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
        // @ Memo : 読込等を行わない、純粋にシーン情報を与えるだけのメンバ関数です
        // @ Arg1 : 追加するシーン
        // @ Arg2 : サブシーンか（現在のシーンとして登録されません。Default : false)
        void RegistryScene(const SceneData data, const bool isSubScene = false);

        
        // シーン追加
        // @ Arg1 : 追加するシーン
        // @ Arg2 : サブシーンか（現在のシーンとして登録されません。Default : false）
        void AddScene(const SceneData data, const bool isSubScene = false);
        // シーン削除
        // @ Arg1 : 削除するシーン
        void DeleteScene(const SceneData data);
        // シーン削除
        // @ Memo : 全てのシーンの削除を行います
        void DeleteScene(void);
        // シーン移動
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
