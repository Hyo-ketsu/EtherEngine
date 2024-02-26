#ifndef I_NATIVEGAMEOBJECTUPDATER_H
#define I_NATIVEGAMEOBJECTUPDATER_H
#include <Base/Singleton.h>
#include <Base/NativeGameObjectStorage.h>
#include <Base/CameraBase.h>


//----- GameObjectUpdater�錾
namespace EtherEngine {
    class NativeGameObjectUpdater : public Singleton<NativeGameObjectUpdater> {
    public:
        // �f�X�g���N�^
        ~NativeGameObjectUpdater(void) {}


        // �Q�[���I�u�W�F�N�g�ɕ����X�V�������s��
        void FixedUpdate(void);


        // �Q�[���I�u�W�F�N�g�̕`�揈�����s��
        // @ Arg1 : �J�������
        void Draw(const CameraData& camera);


        // ���݃V�[���Q�b�^�[
        SceneIDType GetCurrentSceneID(void) const { return m_currentScene; }
        // ���݃V�[���Z�b�^�[
        void SetCurrentSceneID(SceneIDType in) { m_currentScene = in; }

    private:
        // �R���X�g���N�^
        NativeGameObjectUpdater(void) : m_currentScene(0) {}

        friend class CentrallySingleton;

        SceneIDType m_currentScene; // ���݃V�[�����
    };
}


#endif // !I_NATIVEGAMEOBJECTUPDATER_H
