#include <EtherEngine/EditorApplication.h>
#include <Base/Timer.h>
#include <Base/HandleHelper.h>
#include <Base/WindowsDefine.h>
#include <Base/BaseInput.h>
#include <Base/GameObjectUpdater.h>
#include <C++CLI/C++CLIInit.h>
#include <EtherEngine/ProcedureEditorWindow.h>
#include <EtherEngine/EditorObjectUpdater.h>
#include <EtherEngine/MSVCMediation.h>
#include <EtherEngine/ProjectMediation.h> 
#ifdef _DEBUG
#include <EtherEngine/EditorCamera.h>
#include <DirectX/ModelComponent.h>
#include <DirectX/ShaderClass.h>
#include <Base/CollisionSphere.h>
#include <Base/GameObjectStorage.h>
#include <Base/CameraComponent.h>
#include <EtherEngine/Test/TestDefine.h>
#include <EtherEngine/Test/TestComponent.h>
#include <EtherEngine/EditorOutliner.h>
#include <EtherEngine/Test/EditorDebugWindow.h>
#include <EtherEngine/EditorExplorerWindow.h>
#endif // _DEBUG


namespace EtherEngine {
    // �R���X�g���N�^
    EditorApplication::EditorApplication(void)
        : BaseMainWindow<EditorApplication>(WindowDefine::Name::EDITOR_APPLICATION)
        , m_isGameMode(false) {
    }
    // �f�X�g���N�^
    EditorApplication::~EditorApplication(void) {
    }


    // �������֐�
    void EditorApplication::InitFunction(void) {
        //----- �f�[�^�ǂݎ��
        // @ MEMO : �ЂƂ܂����Łi����ProjectData���Ńf�[�^�𐶐����Ă���̂Łj
        m_projectData = std::make_unique<ProjectData>();
        m_projectEditorData = std::make_unique<ProjectEditorData>();
    }
    // ���C���֐�
    void EditorApplication::MainFunction(void) {

        //----- ���������[�N�`�F�b�N
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        //----- ���C���E�B���h�E���쐬
        WNDCLASSEX wcex;
        ZeroMemory(&wcex, sizeof(wcex));
        wcex.hInstance = m_hInstance.value();
        wcex.lpszClassName = m_name.c_str();
        wcex.lpszMenuName = NULL;
        wcex.lpfnWndProc = WindowEditorProcedure;
        wcex.style = CS_CLASSDC;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.hIcon = LoadIcon(wcex.hInstance, NULL);
        wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

        //----- �E�B���h�E�N���X���̓o�^
        if (!RegisterClassEx(&wcex)) {
            MessageBox(NULL, "�E�B���h�E�N���X�̓o�^�Ɏ��s���܂���", "Error", MB_OK);
            return;
        }

        //----- �E�B���h�E�̍쐬
        m_hwnd = CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW,
            wcex.lpszClassName,
            WindowDefine::Name::EDITOR_APPLICATION.c_str(),
            WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME,
            //WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
            CW_USEDEFAULT, CW_USEDEFAULT,   // �E�B���h�E�̕\���ʒu
            m_windowSize.x(), m_windowSize.y(), // �E�B���h�E�̃T�C�Y
            HWND_DESKTOP,                   // �I�[�i�[�E�B���h�E�̐ݒ�
            NULL, m_hInstance.value(), NULL);

        //----- �E�B���h�E���쐬�ł�����
        if (m_hwnd.value() == NULL) {
            MessageBox(NULL, "�E�B���h�E�̍쐬�Ɏ��s���܂���", "Error", MB_OK);
            return;
        }

        //----- �E�B���h�E���T�C�Y
        do {
            //----- �ϐ��錾
            RECT windowSize;
            RECT clientSize;
            Eigen::Vector2i frameSize;
            Eigen::Vector2i resize;

            //----- �E�B���h�E�T�C�Y���擾
            if (GetWindowRect(m_hwnd.value(), &windowSize) == false) break;

            //----- �N���C�A���g�̈���擾
            if (GetClientRect(m_hwnd.value(), &clientSize) == false) break;

            //----- �t���[���T�C�Y�Z�o
            frameSize.x() = (windowSize.right - windowSize.left) - (clientSize.right - clientSize.left);
            frameSize.y() = (windowSize.bottom - windowSize.top) - (clientSize.bottom - clientSize.top);

            //----- ���T�C�Y�p�T�C�Y�̎Z�o
            resize.x() = frameSize.x() + m_windowSize.x();
            resize.y() = frameSize.y() + m_windowSize.y();

            //----- ���T�C�Y
            SetWindowPos(m_hwnd.value(), NULL, CW_USEDEFAULT, CW_USEDEFAULT, resize.x(), resize.y(), SWP_NOMOVE);
        } while (false);

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
        m_initUninitPerformer.AddInitUninit<CPPCLI>();
        m_initUninitPerformer.AddInitUninit(GlobalTimer::Get());
        m_initUninitPerformer.AddInitUninit<InputSystem>();
        m_initUninitPerformer.AddInitUninit(
            [&]() { m_imGui = std::make_unique<IMGUI>(
                m_dxRender.GetAtomicData().GetDevice(),
                m_dxRender.GetAtomicData().GetContext(),
                m_hwnd.value()); },
            [&]() { m_imGui.reset(); }
        );
        m_initUninitPerformer.AddInitUninit(
            [&]() { MSVCMediation::Get()->Init(m_projectData->GetCmdPath(), m_projectData->GetMsvcPath()); },
            []() { MSVCMediation::Get()->Uninit(); }
        );
        m_initUninitPerformer.AddInitUninit(
            [&]() { ProjectMediation::Get()->Init(PathClass::GetCurDirectory() / FileDefine::PROJECTNAME + FileDefine::SOLUTION, PathClass::GetCurDirectory() / FileDefine::PROJECTNAME + FileDefine::PROJECT); },
            []() { ProjectMediation::Get()->Uninit(); }
        );

        //----- ������
        m_initUninitPerformer.Init();

#ifdef _DEBUG
        //----- �e�X�g�E�B���h�E
        auto testWindow = EditorObjectStorage::Get()->CreateEditorObject();
        testWindow.GetAtomicData().AddComponent<EditorDebugWindow>(ImGuiDefine::Name::WINDOW_DEBUG);

        //----- �e�X�g�R���|�[�l���g
        auto testGameObject = GameObjectStorage::Get()->CreateGameObject();
        testGameObject.GetAtomicData().AddComponent("TestComponent");

        //----- �G�f�B�^�[�p�J�����쐬
        auto cameraGameObejct = EditorObjectStorage::Get()->CreateEditorObject();
        cameraGameObejct.GetAtomicData().AccessTransform().AccessPostion().z() = -5;
        auto camera = cameraGameObejct.GetAtomicData().AddComponent<EditorCamera>();

        //----- �e�X�g�p�V�F�[�_�[�ǉ�
        auto vs = VertexShader(this->GetDirectX());
        vs.LoadFile((TestDefine::TEST_ASSET_SHADER_PASS + "VS_Test.cso").c_str());
        auto ps = PixelShader(this->GetDirectX());
        ps.LoadFile((TestDefine::TEST_ASSET_SHADER_PASS + "PS_Test.cso").c_str());

        //----- �J�����ݒ�
        m_dxRender.GetAtomicData().SetCameraID(camera.lock()->GetID().GetId());
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
                frameSecond += fpsTimer.GetDeltaTime();

                //----- FPS����
                if (frameSecond < ONE_FRAME * 1000) continue;
                frameSecond = 0;

                //----- �X�V
                InputSystem::Update();
                GlobalTimer::Get()->Update();

                //----- �G�f�B�^�[�X�V����
                EditorUpdater::Get()->Update();

                //----- �X�V����
                GameObjectUpdater::Get()->FixedUpdate();
                GameObjectUpdater::Get()->Update();

                //----- �`��O����
                m_dxRender.GetAtomicData().BeginDraw();

                //----- �G�f�B�^�[�`�揈��
                EditorUpdater::Get()->Draw();

                //----- �`�揈��
                m_dxRender.GetAtomicData().Draw();

                //----- IMGUI�`��㏈��
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

                //----- �`��㏈��
                m_dxRender.GetAtomicData().EndDraw();
            }
        }

        //----- �I������
        m_initUninitPerformer.UnInit();
    }


    // �Q�[�����[�h���J�n����
    void EditorApplication::StartGameMode(void) {

    }
    // �Q�[�����[�h���ꎞ���f����
    void EditorApplication::StopGameMode(void) {

    }
    // �Q�[�����[�h���I������
    void EditorApplication::EndGameMode(void) {

    }
}