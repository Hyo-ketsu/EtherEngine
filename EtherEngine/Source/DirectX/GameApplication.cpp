#include <DirectX/GameApplication.h>
#include <Base/Timer.h>
#include <Base/WindowName.h>
#include <Base/HandleHelper.h>


namespace EtherEngine {
    // �R���X�g���N�^
    GameApplication::GameApplication(void)
        : Window(WindowName::GAME_APPLICATION_NAME) {
    }
    // �f�X�g���N�^
    GameApplication::~GameApplication(void) {
        HandleSystem<DirectXRender>::Get()->DeleteItem(m_dxRender);
    }


    // Application�f�[�^�Z�b�^�[
    void GameApplication::SetApplicationData(const HINSTANCE hInstance, const LPSTR ipCmdLine, const int& cmdShow) {
        m_hInstance = hInstance;
        m_ipCmdLine = ipCmdLine;
        m_cmdShow = cmdShow;
    }


    LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


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
        wcex.lpszClassName = WINDOW_CLASS_NAME.c_str();           // �E�B���h�E�N���X�ɐݒ肷�閼��
        wcex.lpfnWndProc = MainWndProc;                           // 
        wcex.style = CS_CLASSDC;                                  //   
        wcex.cbSize = sizeof(WNDCLASSEX);                         // 
        wcex.hIcon = LoadIcon(wcex.hInstance, NULL);               // �^�X�N�o�[�̃A�C�R���ݒ�
        wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);             // �X���[���A�C�R���ݒ�
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);               // �}�E�X�J�[�\�������ڐݒ�
        wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // �E�B���h�E�w�i�F

        //----- �E�B���h�E�N���X���̓o�^
        if (!RegisterClassEx(&wcex)) {
            MessageBox(NULL, "�E�B���h�E�N���X�̓o�^�Ɏ��s���܂���", "Error", MB_OK);
            return;
        }

        //----- �E�B���h�E�̍쐬
        m_hwnd = CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW,         // �E�B���h�E�̊O�ρE����̎w��i�g���Łj
            wcex.lpszClassName,             // �R�Â���E�B���h�E�N���X���
            "Test",                         // �E�B���h�E�̃^�C�g��
            WS_CAPTION | WS_SYSMENU,        // �E�B���h�E�̊O�ρE����̎w��
            CW_USEDEFAULT, CW_USEDEFAULT,   // �E�B���h�E�̕\���ʒu
            m_windowSize.x(), m_windowSize.y(), // �E�B���h�E�̃T�C�Y
            HWND_DESKTOP,                   // �I�[�i�[�E�B���h�E�̐ݒ�
            NULL, m_hInstance.value(), NULL);

        //----- �E�B���h�E���쐬�ł�����
        if (m_hwnd.value() == NULL) {
            MessageBox(NULL, "�E�B���h�E�̍쐬�Ɏ��s���܂���", "Error", MB_OK);
            return;
        }

        //----- �E�B���h�E�̕\��
        ShowWindow(m_hwnd.value(), m_cmdShow.value());
        UpdateWindow(m_hwnd.value());

        //�r�f�I�J�[�h�̌���
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
#ifdef _RELEASE
#ifdef _DEVELOP
        isFullScreen = true;    // Develop_Release�̂݃t���X�N���[��
#endif // _DEVELOP
#endif // _RELEASE

        m_dxRender = HandleHelper::AddItem<DirectXRender>(DirectXRender());
        HRESULT hr = m_dxRender.GetAtomicData().Init(m_windowSize.x(), m_windowSize.y(), m_hwnd.value(), isFullScreen, adapterMax, factory);
        if (FAILED(hr)) {
            return;
        }

        if (adapter) adapter->Release();
        if (adapterMax) adapterMax->Release();
        if (factory) factory->Release();

        //----- �������E�I�������o�^
        InitFirst();
        m_initUninitPerformer.AddInitUninit(GlobalTimer::Get());
        InitLast();

        //----- ������
        m_initUninitPerformer.Init();
        InitLateFuntion();

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

                //----- �`��O����
                m_dxRender.GetAtomicData().BeginDraw();
                this->DrawFirst();

                //----- �`�揈��
                m_dxRender.GetAtomicData().Draw();

                //----- �`��㏈��
                this->DrawLast();
                m_dxRender.GetAtomicData().EndDraw();
            }
        }

        //----- �I������
        m_initUninitPerformer.UnInit();
    }


    LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
        case WM_SIZE:
            break;

        case WM_CLOSE:  // �E�B���h�E���폜���悤�Ƃ��Ă���
            break;

        case WM_DESTROY:    // �E�B���h�E���폜
            PostQuitMessage(0); // WM_QUIT ���b�Z�[�W�𑗐M
            break;
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
