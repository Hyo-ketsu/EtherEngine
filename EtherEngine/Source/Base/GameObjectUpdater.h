#ifndef I_GAMEOBJECTUPDATER_H
#define I_GAMEOBJECTUPDATER_H
#include <Base/GameObjectStorage.h>

// @ MEMO : ����Update�̂�



//----- GameObjectUpdater�錾
namespace EtherEngine {
    class GameObjectUpdater : public Singleton<GameObjectUpdater> {
    public:
        // �Q�[���I�u�W�F�N�g�ɍX�V�������s��
        void Update(void);
    };
}


#endif // !I_GAMEOBJECTUPDATER_H
