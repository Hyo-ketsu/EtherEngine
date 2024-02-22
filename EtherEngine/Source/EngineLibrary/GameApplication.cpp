#include <EngineLibrary/GameApplication.h>
#include <Base/Timer.h>
#include <Base/BaseInput.h>
#include <Base/BaseDefines.h>
#include <Base/CameraStorage.h>
#include <EngineLibrary/GameObjectUpdater.h>


//----- GameApplication ��`
#pragma managed
namespace EtherEngine {
    // �R���X�g���N�^
    GameApplication::GameApplication(void)
        : m_isGameUpdate(true)
        , m_isGameDraw(true)
        , m_isLoop(true)
        , m_dxRender(new Handle<DirectXRender>(DirectXRender())) {
    }
    // �f�X�g���N�^
    GameApplication::~GameApplication(void) {
        this->!GameApplication();
    }
    // �t�@�C�i���C�U
    GameApplication::!GameApplication(void) {
        Uninit();
    }


    // ���C���֐�
    void GameApplication::MainFunction(void) {
        //----- �������C�x���g����
        InitEvent(this, System::EventArgs::Empty);

        //----- ���C�����[�v
        System::Diagnostics::Stopwatch^ fpsWatch = System::Diagnostics::Stopwatch::StartNew();
        while (m_isLoop) {
            //----- �Q�[�����[�v�����C�x���g����
            LoopFirstEvent(this, System::EventArgs::Empty);

            //----- FPS����
            if (fpsWatch->Elapsed.Milliseconds < ONE_FRAME * 1000) continue;
            fpsWatch->Reset();
            fpsWatch->Start();

            //----- �C�x���g�p�ϐ��錾
            bool isUpdate = false;  // ���炩�̃Q�[���������s��ꂽ��

            //----- ���͂�^�C�}�[���̂̍X�V
            InputSystem::Update();
            GlobalTimer::Get()->Update();

            //----- �Q�[�����[�v�̃C�x���g����
            if (m_isGameUpdate && m_isGameDraw) {
                //----- �ǂ�����X�V�B
                GameLoopUpdateEvent(this, System::EventArgs::Empty);
            }
            if (!(m_isGameUpdate && m_isGameDraw)) {
                //----- �ǂ�����X�V���Ȃ��B
                GameLoopStopEvent(this, System::EventArgs::Empty);
            }

            //----- �X�V���s�����̔���
            if (m_isGameUpdate) {
                //----- �X�V�C�x���g����
                GameUpdateEvent(this, System::EventArgs::Empty);

                //----- �X�V����

            }

            //----- �G�f�B�^�[�X�V����
            EditorUpdateEvent(this, System::EventArgs::Empty);

            //----- �`�揈��
            if (m_isGameDraw) {
                //----- �S�E�B���h�E�ɑ΂��ĕ`�揈��
                auto camera = CameraSystem::Get()->GetMainData();
                if (camera.has_value()) {
                    //----- �S�E�B���h�E�擾
                    auto&& window = m_dxRender->GetData().AccessWindowRenders();
                    for (auto&& it : window) {
                        //----- �`��O����
                        it.BeginDraw();

                        //----- �`�揈��
                        {
                            //----- �Q�[���I�u�W�F�N�g�`�揈��
                            NativeGameObjectUpdater::Get()->Draw(*camera);

                            //----- �G�f�B�^�[�`�揈��
                            EditorDrawEvent(this, &*camera);

                            //----- �G�f�B�^�[��`�揈��
                            EditorLateDrawEvent(this, &*camera);
                        }

                        //----- �`��㏈��
                        it.EndDraw();
                    }
                }
            }
        }
    }


    // �I������
    void GameApplication::Uninit(void) {
        DELETE_NULL(m_dxRender);
        UninitEvent(this, System::EventArgs::Empty);
    }
}
