#include <DirectX/GameApplication.h>
#include <Base/Timer.h>
#include <Base/HandleHelper.h>
#include <Base/WindowsDefine.h>
#include <Base/GameObjectUpdater.h>
#include <Base/BaseInput.h>
#include <DirectX/ProcedureGameWindow.h>


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
        : BaseMainWindow(WindowDefine::Name::GAME_APPLICATION_NAME) {
    }
    // �f�X�g���N�^
    GameApplication::~GameApplication(void) {
        HandleSystem<DirectXRender>::Get()->DeleteItem(m_dxRender);
    }


    // ���C���֐�
    void GameApplication::MainFunction(void) {
        using namespace std::chrono;

#ifdef _DEBUG
        //----- ���������[�N�`�F�b�N
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

        //----- ���C���E�B���h�E���쐬
        WNDCLASSEX wcex;                                          // �E�B���h�E���̃N���X
        ZeroMemory(&wcex, sizeof(wcex));                          // �T�C�Y���̏�����
        wcex.hInstance = m_hInstance.value();                     // �R�Â��Ă���A�v���P�[�V����
        wcex.lpszClassName = m_name.c_str();                      // �E�B���h�E�N���X�ɐݒ肷�閼��
        wcex.lpfnWndProc = WindowGameProcedure;                   // 
        wcex.style = CS_CLASSDC;                                  //   
        wcex.cbSize = sizeof(WNDCLASSEX);                         // 
        wcex.hIcon = LoadIcon(wcex.hInstance, NULL);              // �^�X�N�o�[�̃A�C�R���ݒ�
        wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);            // �X���[���A�C�R���ݒ�
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);               // �}�E�X�J�[�\�������ڐݒ�
        wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // �E�B���h�E�w�i�F

        //----- �E�B���h�E�N���X���̓o�^
        if (!RegisterClassEx(&wcex)) {
            MessageBox(NULL, "�E�B���h�E�N���X�̓o�^�Ɏ��s���܂���", "Error", MB_OK);
            return;
        }

        //----- �E�B���h�E�̍쐬
        m_hwnd = CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW,
            wcex.lpszClassName,
            WindowDefine::Name::GAME_APPLICATION_NAME.c_str(),
            WS_CAPTION | WS_SYSMENU,
            CW_USEDEFAULT, CW_USEDEFAULT,
            m_windowSize.x(), m_windowSize.y(),
            HWND_DESKTOP,
            NULL, m_hInstance.value(), NULL);

        //----- �E�B���h�E���쐬�ł�����
        if (m_hwnd.value() == NULL) {
            MessageBox(NULL, "�E�B���h�E�̍쐬�Ɏ��s���܂���", "Error", MB_OK);
            return;
        }

        //----- �E�B���h�E�̕\��
        ShowWindow(m_hwnd.value(), m_cmdShow.value());
        UpdateWindow(m_hwnd.value());

        //----- �r�f�I�J�[�h�̌���
        IDXGIFactory1* factory;
        IDXGIAdapter1* adapter;
        IDXGIAdapter1* adapterMax;
        DXGI_ADAPTER_DESC descMax; // ���݂̍ő又�����x�̃r�f�I�J�[�h
        UINT i = 0;
        CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory);
        factory->EnumAdapters1(i, &adapter); i++;
        adapterMax = adapter;
        adapterMax->GetDesc(&descMax);
        for (; factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i) {
            DXGI_ADAPTER_DESC desc;
            adapter->GetDesc(&desc);

            bool isHighPerformanceGPU = (desc.DedicatedVideoMemory > descMax.DedicatedVideoMemory);
            if (isHighPerformanceGPU) {
                adapterMax = adapter;
                adapterMax->GetDesc(&descMax);
            }
        }

        //----- DirectX��������
        bool isFullScreen = false;  // �t���X�N���[���ݒ�

        m_dxRender = Handle<DirectXRender>(DirectXRender());
        HRESULT hr = m_dxRender.GetAtomicData().Init(m_windowSize.x(), m_windowSize.y(), m_hwnd.value(), isFullScreen, adapterMax, factory);
        if (FAILED(hr)) {
            return;
        }

        if (adapter) adapter->Release();
        if (adapterMax) adapterMax->Release();
        if (factory) factory->Release();

        //----- �������E�I�������o�^
        m_initUninitPerformer.AddInitUninit(GlobalTimer::Get());
        m_initUninitPerformer.AddInitUninit<InputSystem>();

        //----- ������
        m_initUninitPerformer.Init();

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
        milliseconds frameSecond = 0ms;
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
                frameSecond -= fpsTimer.GetDeltaTime();

                //----- FPS����
                if (frameSecond < milliseconds(int(ONE_FRAME * 1'000))) continue;
                frameSecond = 0ms;

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
