#ifndef I_NATIVEGAMEOBJECTUPDATER_H
#define I_NATIVEGAMEOBJECTUPDATER_H
#include <Base/Singleton.h>
#include <Base/NativeGameObjectStorage.h>
#include <Base/CameraBase.h>


//----- GameObjectUpdater宣言
namespace EtherEngine {
    class NativeGameObjectUpdater : public Singleton<NativeGameObjectUpdater> {
    public:
        // デストラクタ
        ~NativeGameObjectUpdater(void) {}


        // ゲームオブジェクトに物理更新処理を行う
        void FixedUpdate(void);


        // ゲームオブジェクトの描画処理を行う
        // @ Arg1 : カメラ情報
        void Draw(const CameraData& camera);


        // 現在シーンゲッター
        SceneIDType GetCurrentSceneID(void) const { return m_currentScene; }
        // 現在シーンセッター
        void SetCurrentSceneID(SceneIDType in) { m_currentScene = in; }

    private:
        // コンストラクタ
        NativeGameObjectUpdater(void) : m_currentScene(0) {}

        friend class CentrallySingleton;

        SceneIDType m_currentScene; // 現在シーン情報
    };
}


#endif // !I_NATIVEGAMEOBJECTUPDATER_H
