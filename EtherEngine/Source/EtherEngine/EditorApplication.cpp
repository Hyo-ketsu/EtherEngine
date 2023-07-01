#include <EtherEngine/EditorApplication.h>
#include <Base/Timer.h>
#include <Base/HandleHelper.h>
#include <Base/WindowsDefine.h>
#include <Base/BaseInput.h>
#include <EtherEngine/ProcedureEditorWindow.h>
#include <EtherEngine/EditorObjectUpdater.h>
#ifdef _DEBUG
#include <EtherEngine/EditorCamera.h>

#include <DirectX/ModelComponent.h>
#include <DirectX/ShaderClass.h>
#include <Base/GameObjectStorage.h>
#include <Base/CameraComponent.h>
#include <EtherEngine/Test/TestDefine.h>
#include <EtherEngine/EditorOutliner.h>
#endif // _DEBUG


namespace EtherEngine {
    // コンストラクタ
    EditorApplication::EditorApplication(void) 
        : BaseMainWindow<EditorApplication>(WindowDefine::Name::EDITOR_APPLICATION) {
    }
    // デストラクタ
    EditorApplication::~EditorApplication(void) {
    }


    // メイン関数
    void EditorApplication::MainFunction(void) {
        using namespace std::chrono;

        //----- メモリリークチェック
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        //----- メインウィンドウ情報作成
        WNDCLASSEX wcex;
        ZeroMemory(&wcex, sizeof(wcex));
        wcex.hInstance     = m_hInstance.value();
        wcex.lpszClassName = m_name.c_str();
        wcex.lpszMenuName  = NULL;
        wcex.lpfnWndProc   = WindowEditorProcedure;
        wcex.style         = CS_CLASSDC;
        wcex.cbSize        = sizeof(WNDCLASSEX);
        wcex.hIcon         = LoadIcon(wcex.hInstance, NULL);
        wcex.hIconSm       = LoadIcon(wcex.hInstance, NULL);
        wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
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
            WindowDefine::Name::EDITOR_APPLICATION.c_str(),
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
        m_initUninitPerformer.AddInitUninit(
            [=]() { m_imGui = std::make_unique<IMGUI>(
                m_dxRender.GetAtomicData().GetDevice(),
                m_dxRender.GetAtomicData().GetContext(),
                m_hwnd.value()); },
            [=]() { m_imGui.reset(); });

        //----- 初期化
        m_initUninitPerformer.Init();

#ifdef _DEBUG
        auto cameraGameObejct = EditorObjectStorage::Get()->CreateEditorObject();
        cameraGameObejct.GetAtomicData().AccessTransform().AccessPostion().z() = -5;
        auto camera = cameraGameObejct.GetAtomicData().AddComponent<EditorCamera>();

        //----- テスト用シェーダー追加
        auto vs = VertexShader(this->GetDirectX());
        vs.LoadFile((TestDefine::TEST_ASSET_SHADER_PASS + "VS_Test.cso").c_str());
        auto ps = PixelShader(this->GetDirectX());
        ps.LoadFile((TestDefine::TEST_ASSET_SHADER_PASS + "PS_Test.cso").c_str());

        //----- テスト用ゲームオブジェクト追加
        auto testGameObject = GameObjectStorage::Get()->CreateEditorObject();
        testGameObject.GetAtomicData().AddConponent<ModelComponent>(TestDefine::TEST_ASSET_MODEL_PASS + "spot/spot.fbx", EditorApplication::Get()->GetDirectX(),vs ,ps , 1.0f, false);
        testGameObject.GetAtomicData().AccessName() = "Usi";
        m_dxRender.GetAtomicData().SetCameraID(*camera.lock()->GetID().lock());

        //----- エディター用オブジェクト追加
        auto outlinerGameObject = EditorObjectStorage::Get()->CreateEditorObject();
        outlinerGameObject.GetAtomicData().AddComponent<EditorOutliner>(std::string("OutLiner"));
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
                //frameSecond -= fpsTimer.GetDeltaTime();

                ////----- FPS制御
                //if (frameSecond < milliseconds(int(ONE_FRAME * 1'000))) continue;
                //frameSecond = 0ms;

                //----- 入力更新
                InputSystem::Update();

                //----- エディター更新処理
                EditorUpdater::Get()->Update();

                //----- 描画前処理
                m_dxRender.GetAtomicData().BeginDraw();

                //----- エディター描画処理
                EditorUpdater::Get()->Draw();

                //----- 描画処理
                m_dxRender.GetAtomicData().Draw();

                //----- IMGUI描画後処理
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

                //----- 描画後処理
                m_dxRender.GetAtomicData().EndDraw();
            }
        }

        //----- 終了処理
        m_initUninitPerformer.UnInit();
    }

}
