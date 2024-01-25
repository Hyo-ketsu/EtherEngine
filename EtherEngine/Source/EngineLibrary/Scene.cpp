#include <EngineLibrary/Scene.h>


//----- Scene 定義
namespace EtherEngine {
    // コンストラクタ
    Scene::Scene(void) {
    }


    // シーン番号を取得する
    SceneIDType Scene::GetSceneID(void) {
        return this->GetType()->GetHashCode();
    }
}
