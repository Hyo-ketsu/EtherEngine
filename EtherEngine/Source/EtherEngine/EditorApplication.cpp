#include <EtherEngine/EditorApplication.h>
#include <Base/Timer.h>
#include <Base/HandleHelper.h>
#include <Base/WindowsDefine.h>
#include <Base/BaseInput.h>
#include <Base/BaseDefines.h>
#include <Base/GameObjectUpdater.h>
#include <EngineLibrary/EngineLibraryInit.h>
#include <EngineLibrary/AssemblyHolder.h>
#include <EtherEngine/EditorObjectUpdater.h>
#include <EtherEngine/CommandPrompt.h>
#include <EtherEngine/ProjectMediation.h>
#include <EtherEngine/EditorAssemblyRefresh.h>
#include <EtherEngine/EditorCamera.h>
#include <DirectX/ModelComponent.h>
#include <DirectX/ShaderClass.h>
#include <Base/CollisionSphere.h>
#include <Base/GameObjectStorage.h>
#include <Base/CameraComponent.h>
#include <EtherEngine/Test/TestDefine.h>
#include <EtherEngine/Test/TestComponent.h>
#include <EtherEngine/Test/EditorDebugWindow.h>
#include <EtherEngine/EditorDefine.h>


//----- EditorApplication 定義
namespace EtherEngine {
    // コンストラクタ
    EditorApplication::EditorApplication(void)
        : BaseMainWindow(WindowDefine::Name::EDITOR_APPLICATION)
        , m_isGameMode(false) 
        , m_isWindowFunctionEnable(true) {
    }
    // デストラクタ
    EditorApplication::~EditorApplication(void) {
    }


    // 初期化前関数
    void EditorApplication::InitFirstFunction(void) {
        //----- パス等のデータ読み取り
//#ifdef _DEBUG
        try {
            m_projectData = std::make_unique<ProjectData>(PathClass::GetCurDirectory() / EditorFileDefine::Directory::EDITOR_SETTING / EditorFileDefine::PROJECT_DATA);
        }
        catch (...) {
            m_projectData = std::make_unique<ProjectData>();
            m_projectData->SetMSBuildPath(R"(C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe)");
            m_projectData.reset();  // 保存させるため。
        }
//#endif // _DEBUG
    }
    // 初期化後関数
    void EditorApplication::InitLateFunction(void) {
        m_initUninitPerformer.AddInitUninit(
            [&]() { m_imGui = std::make_unique<IMGUI>(
            m_dxRender.GetAtomicData().GetDevice(),
            m_dxRender.GetAtomicData().GetContext(),
            m_hwnd.value()); },
            [&]() { m_imGui.reset(); }
        );

        //----- プロジェクト設定の読み込み
        try {
            m_projectData = std::make_unique<ProjectData>(PathClass::GetCurDirectory() / EditorFileDefine::Directory::EDITOR_SETTING / EditorFileDefine::PROJECT_DATA);
        }
        catch (const EditorException& e) {
            using namespace EditorUI;

            //----- ない。スタートアップウィンドウ起動
            auto VM = CreateEditorWindow::AddCreateWindow<StartupWindow^, StartupVM^>(true);

            //----- スタートアップウィンドウ終了待ち
            StartupMessage^ message = nullptr;
            while (message == nullptr) { 
                message = MessageQue<StartupMessage^>::GetEngineMessage();
                Utility::ThisThreadSleep();
            }

            //----- 取得したパスを設定
            m_projectData = std::make_unique<ProjectData>();
            m_projectData->SetMSBuildPath(ManageToUnmanage::String(message->Path));
        }

        //----- エディター設定の読み込み
        try {
            m_editorData = std::make_unique<EditorData>(PathClass::GetCurDirectory() / EditorFileDefine::Directory::EDITOR_SETTING / EditorFileDefine::EDITOR_SETTING);
        }
        catch (...) {
            //----- ない。1から生成
            m_editorData = std::make_unique<EditorData>();
        }

        m_initUninitPerformer.AddInitUninit(
            []() { ProjectMediation::Get()->Init(PathClass::GetCurDirectory() / FileDefine::PROJECT_NAME + FileDefine::Extended::SOLUTION, PathClass::GetCurDirectory() / FileDefine::PROJECT_NAME + FileDefine::Extended::PROJECT); },
            []() { ProjectMediation::Get()->Uninit(); }
        );
    }
    // 初期化終了後関数
    void EditorApplication::EndInitLateFunction(void) {

    }
    // 終了前関数
    void EditorApplication::UninitFirstFunction(void) {
#ifndef _DEBUG
        //----- 出力
        // @ MEMO : 面倒なんで後回し
#endif // !_DEBUG
    }
    // メイン関数
    void EditorApplication::MainFunction(void) {
#ifdef _DEBUG
        //----- テストウィンドウ
        //auto testWindow = EditorObjectStorage::Get()->CreateEditorObject();
        //testWindow.GetAtomicData().AddComponent<EditorDebugWindow>();

        ////----- テストコンポーネント
        //auto testGameObject = GameObjectStorage::Get()->CreateGameObject();
        ////testGameObject.GetAtomicData().AddComponent("TestComponent");

        ////----- エディター用カメラ作成
        //auto cameraGameObejct = EditorObjectStorage::Get()->CreateEditorObject();
        //cameraGameObejct.GetAtomicData().AccessTransform().AccessPostion().z() = -5;
        //auto camera = cameraGameObejct.GetAtomicData().AddComponent<EditorCamera>();

        ////----- テスト用シェーダー追加
        //auto vs = VertexShader(this->GetDirectX());
        //vs.LoadFile((TestDefine::TEST_ASSET_SHADER_PASS + "VS_Test.cso").c_str());
        //auto ps = PixelShader(this->GetDirectX());
        //ps.LoadFile((TestDefine::TEST_ASSET_SHADER_PASS + "PS_Test.cso").c_str());

        ////----- カメラ設定
        //m_dxRender.GetAtomicData().SetCameraID(camera.lock()->GetID().GetId());
#endif // _DEBUG

        //----- VS等の設定
        // @ MEMO : 後で実装する

        // @ MEMO : テスト
        Refresh::AssemblyRefresh();

        //----- メッセージループ
        MSG message;
        Timer fpsTimer;
        milliSecond frameSecond = 0;
        while (GetIsGameLoop()) {
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
            else {   
                //----- ゲーム処理
                frameSecond += fpsTimer.GetDeltaTime();

                //----- ウィンドウ処理
                // シーンウィンドウの追加
                while (true) {
                    //----- ウィンドウの取得(取得できなかったら終了)
                    auto window = EditorUI::GetEditorWindow::GetCreateWindow<EditorUI::SceneViewVM^>();
                    if (window == nullptr) break;

                    //----- 前準備
                    auto engineLock = window->GetEngineLock();  // ロック取得
                    auto size = engineLock.Item2->NewWindowSize;    // このウィンドウのサイズ
                    if (size.HasValue == false) throw std::exception("Error! Is SceneView size?");

                    //----- ラムダ用意
                    // @ MEMO : 結果的に参照をラムダでキャプチャしている。windowRenderが死んだら解放されるだろうけど要注意？
                    DrawFunctionLambda drawFunction = [&](Eigen::Matrix4f view, Eigen::Matrix4f projection) {    // ウィンドウで行う描画
                        GameObjectUpdater::Get()->Draw(view, projection);
                    };
                    msclr::gcroot<decltype(window)> enableWindow = window;  // ウィンドウ生存確認lambdaでキャプチャするため
                    WindowEnableLambda enableFunction = [=]() -> bool {
                        return enableWindow->GetEngineLock().Item2 != nullptr && enableWindow->GetEngineLock().Item2 != nullptr;
                    };
                    WindowFunctionLambda windowFunction = [=](DXWindowRender* const window) {   // ウィンドウでの追加処理。リサイズ検出
                        auto size = enableWindow->GetEngineLock().Item2->NewWindowSize;
                        if (size.HasValue) {
                            //----- リサイズを行う
                            // @ MEMO : 現状行っておりません。
                        }
                    };

                    //----- 新規に作成
                    m_dxRender.GetAtomicData().CreateDrawWindow(Eigen::Vector2i(size.Value.X, size.Value.Y),static_cast<HWND>(engineLock.Item2->SceneViewTarget.ToPointer()),
                        false, drawFunction, enableFunction, windowFunction);
                }

                //----- アセンブリ存在チェック
                if (AssemblyHolder::IsLoadAssemblyEnable() == false && Refresh::GetRefreshState() != Refresh::RefreshStateType::CurrentlyRefresh) {
                    //----- Refreshを行う
                    if (false) {
                        ProjectMediation::Get()->RefreshAssembly();
                    }
                }

                //----- シーンウィンドウ更新処理
                auto& windowData = m_dxRender.GetAtomicData();
                for (auto it = windowData.AccessWindowRenders().begin(); it != windowData.AccessWindowRenders().end();) {
                    //----- 生存チェック
                    if (it->GetWindowEnableFunction()()) {
                        //----- 生存している。更新
                        it->GetWindowFunction()(&*it);
                        it++;
                    }
                    else {
                        //----- 生存していない。削除
                        windowData.AccessWindowRenders().erase(it);
                    }
                }

                //----- FPS制御
                if (frameSecond < ONE_FRAME * 1000) continue;
                frameSecond = 0;

                //----- 更新
                InputSystem::Update();
                GlobalTimer::Get()->Update();

                //----- エディター更新処理
                //EditorUpdater::Get()->Update();

                //----- 更新処理
                GameObjectUpdater::Get()->FixedUpdate();
                GameObjectUpdater::Get()->Update();

                //----- 描画前処理
                for (auto&& it : m_dxRender.GetAtomicData().AccessWindowRenders()) {
                    it.BeginDraw();
                }

                //----- 描画処理
                for (auto&& it : m_dxRender.GetAtomicData().AccessWindowRenders()) {
                    it.Draw();
                }

                ////----- エディター描画処理
                //EditorUpdater::Get()->Draw();

                ////----- エディター描画後処理
                //EditorUpdater::Get()->LateDraw();

                //----- 描画後処理
                for (auto&& it : m_dxRender.GetAtomicData().AccessWindowRenders()) {
                    it.EndDraw();
                }
            }
        }
    }


    // ゲームモードを開始する
    void EditorApplication::StartGameMode(void) {

    }
    // ゲームモードを一時中断する
    void EditorApplication::StopGameMode(void) {

    }
    // ゲームモードを終了する
    void EditorApplication::EndGameMode(void) {

    }


    // ウィンドウの移動などの有効無効を切り替える
    void EditorApplication::SetWindowFunctionEnable(const bool isEnable, const bool isClose) {
        //----- 変数宣言
        uint enable = isEnable ? MF_ENABLED : MF_BYCOMMAND | MF_GRAYED;

        //----- 以下メニュー設定
        if (isClose) EnableMenuItem(GetSystemMenu(GetHWND(), FALSE), SC_CLOSE, enable);

        m_isWindowFunctionEnable = isEnable;
    }
}
