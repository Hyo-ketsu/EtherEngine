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
    // コンストラクタ
    GameApplication::GameApplication(void)
        : BaseMainWindow(WindowDefine::Name::GAME_APPLICATION_NAME) {
    }
    // デストラクタ
    GameApplication::~GameApplication(void) {
        HandleSystem<DirectXRender>::Get()->DeleteItem(m_dxRender);
    }


    // メイン関数
    void GameApplication::MainFunction(void) {
        using namespace std::chrono;

#ifdef _DEBUG
        //----- メモリリークチェック
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

        //----- メインウィンドウ情報作成
        WNDCLASSEX wcex;                                          // ウィンドウ情報のクラス
        ZeroMemory(&wcex, sizeof(wcex));                          // サイズ分の初期化
        wcex.hInstance = m_hInstance.value();                     // 紐づいているアプリケーション
        wcex.lpszClassName = m_name.c_str();                      // ウィンドウクラスに設定する名称
        wcex.lpfnWndProc = WindowGameProcedure;                   // 
        wcex.style = CS_CLASSDC;                                  //   
        wcex.cbSize = sizeof(WNDCLASSEX);                         // 
        wcex.hIcon = LoadIcon(wcex.hInstance, NULL);              // タスクバーのアイコン設定
        wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);            // スモールアイコン設定
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);               // マウスカーソル見た目設定
        wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ウィンドウ背景色

        //----- ウィンドウクラス情報の登録
        if (!RegisterClassEx(&wcex)) {
            MessageBox(NULL, "ウィンドウクラスの登録に失敗しました", "Error", MB_OK);
            return;
        }

        //----- ウィンドウの作成
        m_hwnd = CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW,
            wcex.lpszClassName,
            WindowDefine::Name::GAME_APPLICATION_NAME.c_str(),
            WS_CAPTION | WS_SYSMENU,
            CW_USEDEFAULT, CW_USEDEFAULT,
            m_windowSize.x(), m_windowSize.y(),
            HWND_DESKTOP,
            NULL, m_hInstance.value(), NULL);

        //----- ウィンドウが作成できたか
        if (m_hwnd.value() == NULL) {
            MessageBox(NULL, "ウィンドウの作成に失敗しました", "Error", MB_OK);
            return;
        }

        //----- ウィンドウの表示
        ShowWindow(m_hwnd.value(), m_cmdShow.value());
        UpdateWindow(m_hwnd.value());

        //----- ビデオカードの検索
        IDXGIFactory1* factory;
        IDXGIAdapter1* adapter;
        IDXGIAdapter1* adapterMax;
        DXGI_ADAPTER_DESC descMax; // 現在の最大処理速度のビデオカード
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

        //----- DirectXを初期化
        bool isFullScreen = false;  // フルスクリーン設定

        m_dxRender = Handle<DirectXRender>(DirectXRender());
        HRESULT hr = m_dxRender.GetAtomicData().Init(m_windowSize.x(), m_windowSize.y(), m_hwnd.value(), isFullScreen, adapterMax, factory);
        if (FAILED(hr)) {
            return;
        }

        if (adapter) adapter->Release();
        if (adapterMax) adapterMax->Release();
        if (factory) factory->Release();

        //----- 初期化・終了処理登録
        m_initUninitPerformer.AddInitUninit(GlobalTimer::Get());
        m_initUninitPerformer.AddInitUninit<InputSystem>();

        //----- 初期化
        m_initUninitPerformer.Init();

#ifdef _DEBUG
#ifdef _GAME_TEST
        //----- テスト用シェーダー追加
        auto vs = VertexShader(this->GetDirectX());
        vs.LoadFile((TestDefine::TEST_ASSET_SHADER_PASS + "VS_Test.cso").c_str());
        auto ps = PixelShader(this->GetDirectX());
        ps.LoadCompile((TestDefine::TEST_ASSET_SHADER_PASS + "PS_Test.cso").c_str());

        //----- テスト用ゲームオブジェクト追加
        //auto testGameObject = GameObjectStorage::Get()->CreateGameObject(Transform());
        //testGameObject.GetAtomicData().AddConponent<ModelComponent>(TestDefine::TEST_ASSET_MODEL_PASS + "TestAsset.obj", GameApplication::Get()->GetDirectX(),vs ,ps , 1.0f, false);
        auto cameraGameObject = GameObjectStorage::Get()->CreateGameObject(Transform());
        cameraGameObject.GetAtomicData().AccessTransform().AccessPostion().z() = -1;
        auto camera = cameraGameObject.GetAtomicData().AddConponent<CameraComponent>(Eigen::Vector3f(0.0, 0.0, -3.0f));
        m_dxRender.GetAtomicData().SetCameraID(camera.lock()->GetID());
#endif // _GAME_TESTB
#endif // _DEBUG

        //----- メッセージループ
        MSG message;
        Timer fpsTimer;
        milliseconds frameSecond = 0ms;
        while (true) {
            //----- メッセージ確認
            if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE)) {
                // メッセージを取得
                // WM_QUITのみ、取得できないと判定される
                if (!GetMessage(&message, NULL, 0, 0)) {
                    // WM_QUITが届いた時だけ終了
                    break;
                }
                else {
                    TranslateMessage(&message); // 届いたメッセージをWindowsに転送
                    DispatchMessage(&message);  // 
                }
            }
            else {   //----- ゲーム処理
                //----- 定期更新処理
                frameSecond -= fpsTimer.GetDeltaTime();

                //----- FPS制御
                if (frameSecond < milliseconds(int(ONE_FRAME * 1'000))) continue;
                frameSecond = 0ms;

                //----- Update処理
                GameObjectUpdater::Get()->Update();

                //----- 描画前処理
                m_dxRender.GetAtomicData().BeginDraw();

                //----- 描画処理
                m_dxRender.GetAtomicData().Draw();

                //----- 描画後処理
                m_dxRender.GetAtomicData().EndDraw();
            }
        }

        //----- 終了処理
        m_initUninitPerformer.UnInit();
    }
}
