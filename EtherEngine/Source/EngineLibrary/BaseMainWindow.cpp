#include <EngineLibrary/BaseMainWindow.h>
#include <Base/WindowsDefine.h>
#include <Base/WindowsDefine.h>
#include <Base/BaseInput.h>
#include <Base/GameObjectUpdater.h>
#include <Base/Timer.h>
#include <EngineLibrary/ManageFunctionInit.h>
#include <EngineLibrary/AssemblyHolder.h>


namespace EtherEngine {
    // コンストラクタ
    BaseMainWindow::BaseMainWindow(const std::string& name) 
        : Window(name) {
        m_dxRender = Handle<DirectXRender>(DirectXRender());
    }


    // Applicationデータセッター
    void BaseMainWindow::SetApplicationData(const HINSTANCE hInstance, const LPSTR ipCmdLine, const int& cmdShow) {
        m_hInstance = hInstance;
        m_ipCmdLine = ipCmdLine;
        m_cmdShow = cmdShow;
    }


    // ウィンドウ関連の初期化
    void BaseMainWindow::WindowFunction(void) {
        //----- メモリリークチェック
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        //----- メインウィンドウ情報作成
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

        //----- ウィンドウクラス情報の登録
        if (!RegisterClassEx(&wcex)) {
            MessageBox(NULL, "ウィンドウクラスの登録に失敗しました", "Error", MB_OK);
            return;
        }

        //----- ウィンドウの作成
        m_hwnd = CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW,
            wcex.lpszClassName,
            (LPCSTR)WindowDefine::Name::EDITOR_APPLICATION.c_str(),
            WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME,
            //WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
            CW_USEDEFAULT, CW_USEDEFAULT,   // ウィンドウの表示位置
            m_windowSize.x(), m_windowSize.y(), // ウィンドウのサイズ
            HWND_DESKTOP,                   // オーナーウィンドウの設定
            NULL, m_hInstance.value(), NULL);

        //----- ウィンドウが作成できたか
        if (m_hwnd.value() == NULL) {
            MessageBox(NULL, "ウィンドウの作成に失敗しました", "Error", MB_OK);
            return;
        }

        //----- ウィンドウリサイズ
        do {
            //----- 変数宣言
            RECT windowSize;
            RECT clientSize;
            Eigen::Vector2i frameSize;
            Eigen::Vector2i resize;

            //----- ウィンドウサイズを取得
            if (GetWindowRect(m_hwnd.value(), &windowSize) == false) break;

            //----- クライアント領域を取得
            if (GetClientRect(m_hwnd.value(), &clientSize) == false) break;

            //----- フレームサイズ算出
            frameSize.x() = (windowSize.right - windowSize.left) - (clientSize.right - clientSize.left);
            frameSize.y() = (windowSize.bottom - windowSize.top) - (clientSize.bottom - clientSize.top);

            //----- リサイズ用サイズの算出
            resize.x() = frameSize.x() + m_windowSize.x();
            resize.y() = frameSize.y() + m_windowSize.y();

            //----- リサイズ
            SetWindowPos(m_hwnd.value(), NULL, CW_USEDEFAULT, CW_USEDEFAULT, resize.x(), resize.y(), SWP_NOMOVE);
        } while (false);

        //----- ウィンドウの表示
        ShowWindow(m_hwnd.value(), m_cmdShow.value());
        UpdateWindow(m_hwnd.value());
        
        //----- DirectXを初期化
        bool isFullScreen = false;  // フルスクリーン設定

        m_dxRender.GetAtomicData().Init(m_windowSize, m_hwnd.value(), isFullScreen);
    }


    // 初期化前関数
    void BaseMainWindow::InitFirstFunction(void) {
        WindowFunction();
    }
    // 初期化関数
    void BaseMainWindow::BaseInitFunction(void) {
        //----- 初期化呼び出し
        InitFirstFunction();

        //----- 初期化・終了処理登録
        m_initUninitPerformer.AddInitUninit<ManageFunctionInit>();
        m_initUninitPerformer.AddInitUninit(GlobalTimer::Get());
        m_initUninitPerformer.AddInitUninit<InputSystem>();

        InitLateFunction();
        
        //----- 初期化
        m_initUninitPerformer.Init();
    }
    // 終了関数
    void BaseMainWindow::BaseUninitFunction(void) {
        UninitFirstFunction();
        UninitLateFunction();

        //----- 終了処理
        m_initUninitPerformer.UnInit();

        EndUninitLateFunction();
    }
    // メイン関数
    void BaseMainWindow::BaseMainFunction(void) {
        this->BaseInitFunction();
        this->MainFunction();
        this->BaseUninitFunction();
    }
}
