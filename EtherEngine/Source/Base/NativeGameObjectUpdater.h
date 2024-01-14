#ifndef I_GAMEOBJECTUPDATER_H
#define I_GAMEOBJECTUPDATER_H
#include <Base/NativeGameObjectStorage.h>
#include <Base/CameraBase.h>


//----- GameObjectUpdater宣言
namespace EtherEngine {
    class NativeGameObjectUpdater : public Singleton<NativeGameObjectUpdater> {
    public:
        // ゲームオブジェクトに更新処理を行う
        void Update(void);
        // ゲームオブジェクトに物理更新処理を行う
        void FixedUpdate(void);

        // ゲームオブジェクトの描画処理を行う
        // @ Arg1 : カメラ情報
        void Draw(const CameraData& camera);

    private:
        // コンストラクタ
        NativeGameObjectUpdater(void) {}

        friend class CentrallySingleton;
    };
}


#endif // !I_GAMEOBJECTUPDATER_H
