#ifndef I_GAMEOBJECTUPDATER_H
#define I_GAMEOBJECTUPDATER_H
#include <Base/GameObjectStorage.h>


//----- GameObjectUpdater宣言
namespace EtherEngine {
    class GameObjectUpdater : public Singleton<GameObjectUpdater> {
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
        GameObjectUpdater(void) {}

        friend class Singleton<GameObjectUpdater>;
    };
}


#endif // !I_GAMEOBJECTUPDATER_H
