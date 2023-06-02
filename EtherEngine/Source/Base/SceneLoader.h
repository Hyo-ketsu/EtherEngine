#ifndef I_SCENELOADER_H
#define I_SCENELOADER_H
#include <Base/Singleton.h>
#include <Base/Scene.h>

// @ MEMO : 現段階では「動く」目標。DLL名渡して、というのも考えられるがひとまず描画させる


//----- SceneLoader宣言
namespace EtherEngine {
    // Sceneのみを表現するコンセプト
    // @ Temp2 : nullptrを許容するか
    template <typename T, bool IsNullptr>
    concept SceneConcept = std::is_base_of_v<Scene, T> && (IsNullptr || std::is_null_pointer_v<T>);


    // シーンを総括するクラス
    class SceneLoader : public Singleton<SceneLoader> {
    public:
        // デストラクタ
        ~SceneLoader(void) override;


        // シーン追加
        // @ Temp : 追加するシーン
        template <SceneConcept<false> SceneType>
        void AddScene(void);
        // シーン削除
        // @ Temp : 削除するシーン(Default : nullptr_t。全シーン削除)
        template <SceneConcept<true> SceneType = nullptr_t>
        void DeleteScene(void);
        // シーン移動
        // @ Temp : 移動するシーン
        template <SceneConcept<false> SceneType>
        [deprecated("未実装")]
        void MoveScene(void);


    private:
        // コンストラクタ
        SceneLoader(void);


        friend class Singleton<SceneLoader>;
    };
}


//----- SceneLoader実装
namespace EtherEngine {
    // シーン追加
    // @ Temp : 追加するシーン
    template <SceneConcept<false> SceneType>
    void SceneLoader::AddScene(void) {

    }
    // シーン削除
    // @ Temp : 削除するシーン(Default : nullptr_t。全シーン削除)
    template <SceneConcept<true> SceneType>
    void SceneLoader::DeleteScene(void) {

    }
    // シーン移動
    // @ Temp : 移動するシーン
    template <SceneConcept<false> SceneType>
    void SceneLoader::MoveScene(void) {
    }
}


#endif // !I_SCENELOADER_H
