#ifndef I_GAMEOBJECTUPDATER_H
#define I_GAMEOBJECTUPDATER_H
#include <Base/NativeGameObjectStorage.h>
#include <Base/CameraBase.h>


//----- GameObjectUpdater�錾
namespace EtherEngine {
    class NativeGameObjectUpdater : public Singleton<NativeGameObjectUpdater> {
    public:
        // �Q�[���I�u�W�F�N�g�ɍX�V�������s��
        void Update(void);
        // �Q�[���I�u�W�F�N�g�ɕ����X�V�������s��
        void FixedUpdate(void);

        // �Q�[���I�u�W�F�N�g�̕`�揈�����s��
        // @ Arg1 : �J�������
        void Draw(const CameraData& camera);

    private:
        // �R���X�g���N�^
        NativeGameObjectUpdater(void) {}

        friend class CentrallySingleton;
    };
}


#endif // !I_GAMEOBJECTUPDATER_H
