#ifndef I_GAMEOBJECTUPDATER_H
#define I_GAMEOBJECTUPDATER_H
#include <Base/GameObjectStorage.h>

// @ MEMO : 現状Updateのみ



//----- GameObjectUpdater宣言
namespace EtherEngine {
    class GameObjectUpdater : public Singleton<GameObjectUpdater> {
    public:
        // ゲームオブジェクトに更新処理を行う
        void Update(void);
    };
}


#endif // !I_GAMEOBJECTUPDATER_H
