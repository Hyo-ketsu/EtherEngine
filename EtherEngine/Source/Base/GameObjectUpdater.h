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

        // �Q�[���I�u�W�F�N�g�̕`�揈�����s��
        void Draw(void);

    private:
        // �R���X�g���N�^
        GameObjectUpdater(void) {}

        friend class Singleton<GameObjectUpdater>;
    };
}


#endif // !I_GAMEOBJECTUPDATER_H
