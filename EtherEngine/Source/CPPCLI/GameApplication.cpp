#include <CPPCLI/GameApplication.h>
#include <Base/Timer.h>
#include <Base/HandleHelper.h>
#include <Base/WindowsDefine.h>
#include <Base/GameObjectUpdater.h>
#include <Base/BaseInput.h>
#include <CPPCLI/CPPCLIInit.h>


#ifdef _DEBUG
#ifdef _GAME_TEST
#include <DirectX/ModelComponent.h>
#include <DirectX/ShaderClass.h>
#include <Base/CameraComponent.h>
#include <EtherEngine/Test/TestDefine.h>
#endif // _GAME_TEST
#endif // _DEBUG


namespace EtherEngine {
    // �R���X�g���N�^
    GameApplication::GameApplication(void)
        : BaseMainWindow(WindowDefine::Name::GAME_APPLICATION) {
    }
    // �f�X�g���N�^
    GameApplication::~GameApplication(void) {
        HandleSystem<DirectXRender>::Get()->DeleteItem(m_dxRender);
    }


    // ���C���֐�
    void GameApplication::MainFunction(void) {
#ifdef _DEBUG
#ifdef _GAME_TEST
        //----- �e�X�g�p�V�F�[�_�[�ǉ�
        auto vs = VertexShader(this->GetDirectX());
        vs.LoadFile((TestDefine::TEST_ASSET_SHADER_PASS + "VS_Test.cso").c_str());
        auto ps = PixelShader(this->GetDirectX());
        ps.LoadCompile((TestDefine::TEST_ASSET_SHADER_PASS + "PS_Test.cso").c_str());

        //----- �e�X�g�p�Q�[���I�u�W�F�N�g�ǉ�
        //auto testGameObject = GameObjectStorage::Get()->CreateGameObject(Transform());
        //testGameObject.GetAtomicData().AddConponent<ModelComponent>(TestDefine::TEST_ASSET_MODEL_PASS + "TestAsset.obj", GameApplication::Get()->GetDirectX(),vs ,ps , 1.0f, false);
        auto cameraGameObject = GameObjectStorage::Get()->CreateGameObject(Transform());
        cameraGameObject.GetAtomicData().AccessTransform().AccessPostion().z() = -1;
        auto camera = cameraGameObject.GetAtomicData().AddConponent<CameraComponent>(Eigen::Vector3f(0.0, 0.0, -3.0f));
        m_dxRender.GetAtomicData().SetCameraID(camera.lock()->GetID());
#endif // _GAME_TESTB
#endif // _DEBUG

        //----- ���b�Z�[�W���[�v
        MSG message;
        Timer fpsTimer;
        milliSecond frameSecond = 0;
        while (true) {
            //----- ���b�Z�[�W�m�F
            if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE)) {
                // ���b�Z�[�W���擾
                // WM_QUIT�̂݁A�擾�ł��Ȃ��Ɣ��肳���
                if (!GetMessage(&message, NULL, 0, 0)) {
                    // WM_QUIT���͂����������I��
                    break;
                }
                else {
                    TranslateMessage(&message); // �͂������b�Z�[�W��Windows�ɓ]��
                    DispatchMessage(&message);  // 
                }
            }
            else {   //----- �Q�[������
                //----- ����X�V����
                frameSecond += fpsTimer.GetDeltaTime();

                //----- FPS����
                if (frameSecond < (ONE_FRAME * 1'000)) continue;
                frameSecond = 0;

                //----- Update����
                GameObjectUpdater::Get()->Update();

                //----- �`��O����
                m_dxRender.GetAtomicData().BeginDraw();

                //----- �`�揈��
                m_dxRender.GetAtomicData().Draw();

                //----- �`��㏈��
                m_dxRender.GetAtomicData().EndDraw();
            }
        }

        //----- �I������
        m_initUninitPerformer.UnInit();
    }
}