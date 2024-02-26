#ifndef I_GAMEAPPLICATION_H
#define I_GAMEAPPLICATION_H
#include <Base/Handle.h>
#include <DirectX/DirectX.h>
#include <EngineLibrary/ManageSingleton.h>


//----- GameApplication �錾
#pragma managed
namespace EtherEngine {
    // �`��p�C�x���g��`
    delegate void EditorDrawEventHandler(System::Object^ s, CameraData* e);


    // �Q�[����\������N���X(Singleton)
    public ref class GameApplication {
        ETHER_ENGINE_MANAGE_SINGLETON(GameApplication);
    public:
        // �f�X�g���N�^
        ~GameApplication(void);
        // �t�@�C�i���C�U
        !GameApplication(void);


        // DirectX�Q�b�^�[
        void GetDirectX(void** pointer) { *pointer = m_dxRender; }
        // DirectX�Q�b�^�[
        Handle<DirectXRender>* GetDirectX(void) { return m_dxRender; }


        // �Q�[���I�u�W�F�N�g�X�V�v���p�e�B
        property bool IsGameUpdate {
            bool get(void) { return m_isGameUpdate; }
            void set(bool value) { m_isGameUpdate = value; }
        }
        // �Q�[���I�u�W�F�N�g�`��v���p�e�B
        property bool IsGameDraw {
            bool get(void) { return m_isGameDraw; }
            void set(bool value) { m_isGameDraw = value; }
        }
        // �Q�[���I�u�W�F�N�g�����v���p�e�B
        property bool IsGame {
            void set(bool value) { m_isGameUpdate = m_isGameDraw = value; }
        }


        // �Q�[���I���֐�
        void GameEnd(void) { m_isLoop = false; }


        // ���C���֐�
        void MainFunction(void);

        event System::EventHandler^ InitEvent;      // ����������
        event System::EventHandler^ UninitEvent;    // �I��������

        event System::EventHandler^ GameUpdateEvent;        // �Q�[���I�u�W�F�N�g�̍X�V�������s��ꂽ���ɔ��΂���C�x���g
        event System::EventHandler^ GameLoopUpdateEvent;    // �Q�[�����[�v�̍X�V���ɔ��΂���C�x���g
        event System::EventHandler^ GameLoopStopEvent;      // �Q�[�����[�v�̒�~���ɔ��΂���C�x���g

        event System::EventHandler^ EditorUpdateEvent;      // �G�f�B�^�[�̍X�V����
        event EditorDrawEventHandler^ EditorDrawEvent;      // �G�f�B�^�[�̕`�揈��
        event EditorDrawEventHandler^ EditorLateDrawEvent;  // �G�f�B�^�[�̕`��㏈��

        event System::EventHandler^ LoopFirstEvent;         // ���[�v�̐�(FPS�v�������)���΂���C�x���g

    private:
        // �I������
        void Uninit(void);


        bool m_isGameUpdate;  // �Q�[���I�u�W�F�N�g�̍X�V����(Delete�ȊO��Update)���s����
        bool m_isGameDraw;    // �Q�[���I�u�W�F�N�g�̕`�揈�����s����
        bool m_isLoop;        // ���C�����[�v���s����
        Handle<DirectXRender>* m_dxRender;  // �ێ����Ă���DirectX
    };
}


#endif // !I_GAMEAPPLICATION_H
