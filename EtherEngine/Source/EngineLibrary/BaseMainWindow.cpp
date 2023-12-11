#include <EngineLibrary/BaseMainWindow.h>
#include <Base/WindowsDefine.h>
#include <Base/WindowsDefine.h>
#include <Base/BaseInput.h>
#include <Base/GameObjectUpdater.h>
#include <Base/Timer.h>
#include <EngineLibrary/ManageFunctionInit.h>
#include <EngineLibrary/AssemblyHolder.h>


namespace EtherEngine {
    // �R���X�g���N�^
    BaseMainWindow::BaseMainWindow(const std::string& name) 
        : Window(name) {
        m_dxRender = Handle<DirectXRender>(DirectXRender());
    }


    // Application�f�[�^�Z�b�^�[
    void BaseMainWindow::SetApplicationData(const HINSTANCE hInstance, const LPSTR ipCmdLine, const int& cmdShow) {
        m_hInstance = hInstance;
        m_ipCmdLine = ipCmdLine;
        m_cmdShow = cmdShow;
    }


    // �E�B���h�E�֘A�̏�����
    void BaseMainWindow::WindowFunction(void) {
        //----- ���������[�N�`�F�b�N
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        //----- ���C���E�B���h�E���쐬
        WNDCLASSEX wcex;
        ZeroMemory(&wcex, sizeof(wcex));
        wcex.hInstance = m_hInstance.value();
        wcex.lpszClassName = m_name.c_str();
        wcex.lpszMenuName = NULL;
        wcex.lpfnWndProc = *m_proc;
        wcex.style = CS_CLASSDC;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.hIcon = NULL;
        wcex.hIconSm = NULL;
        wcex.hCursor = NULL;
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
            (LPCSTR)WindowDefine::Name::EDITOR_APPLICATION.c_str(),
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
        
        //----- DirectX��������
        bool isFullScreen = false;  // �t���X�N���[���ݒ�

        m_dxRender.GetAtomicData().Init(m_windowSize, m_hwnd.value(), isFullScreen);
    }


    // �������O�֐�
    void BaseMainWindow::InitFirstFunction(void) {
        WindowFunction();
    }
    // �������֐�
    void BaseMainWindow::BaseInitFunction(void) {
        //----- �������Ăяo��
        InitFirstFunction();

        //----- �������E�I�������o�^
        m_initUninitPerformer.AddInitUninit<ManageFunctionInit>();
        m_initUninitPerformer.AddInitUninit(GlobalTimer::Get());
        m_initUninitPerformer.AddInitUninit<InputSystem>();

        InitLateFunction();
        
        //----- ������
        m_initUninitPerformer.Init();
    }
    // �I���֐�
    void BaseMainWindow::BaseUninitFunction(void) {
        UninitFirstFunction();
        UninitLateFunction();

        //----- �I������
        m_initUninitPerformer.UnInit();

        EndUninitLateFunction();
    }
    // ���C���֐�
    void BaseMainWindow::BaseMainFunction(void) {
        this->BaseInitFunction();
        this->MainFunction();
        this->BaseUninitFunction();
    }
}
