#ifndef I_GAMEOBJECTUPDATER_H
#define I_GAMEOBJECTUPDATER_H
#include <Base/NativeGameObjectStorage.h>


//----- GameObjectUpdater宣言
namespace EtherEngine {
    class NativeGameObjectUpdater : public Singleton<NativeGameObjectUpdater> {
    public:
        // ゲームオブジェクトに更新処理を行う
        void Update(void);
        // ゲームオブジェクトに物理更新処理を行う
        void FixedUpdate(void);

        // ゲームオブジェクトの描画処理を行う
        // @ Arg1 : View行列
        // @ Arg2 : Projection行列
        void Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection);

    private:
        // コンストラクタ
        NativeGameObjectUpdater(void) {}

        friend class Singleton<NativeGameObjectUpdater>;
    };
}


#endif // !I_GAMEOBJECTUPDATER_H
