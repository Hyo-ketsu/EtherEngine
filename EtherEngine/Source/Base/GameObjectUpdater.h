#ifndef I_GAMEOBJECTUPDATER_H
#define I_GAMEOBJECTUPDATER_H
#include <Base/GameObjectStorage.h>


//----- GameObjectUpdater�錾
namespace EtherEngine {
    class GameObjectUpdater : public Singleton<GameObjectUpdater> {
    public:
        // �Q�[���I�u�W�F�N�g�ɍX�V�������s��
        void Update(void);
        // �Q�[���I�u�W�F�N�g�ɕ����X�V�������s��
        void FixedUpdate(void);

        // �Q�[���I�u�W�F�N�g�̕`�揈�����s��
        // @ Arg1 : View�s��
        // @ Arg2 : Projection�s��
        void Draw(const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection);

    private:
        // �R���X�g���N�^
        GameObjectUpdater(void) {}

        friend class Singleton<GameObjectUpdater>;
    };
}


#endif // !I_GAMEOBJECTUPDATER_H
