#include <EtherEngine/EditorApplication.h>
#include <Base/Timer.h>
#include <Base/HandleHelper.h>
#include <Base/WindowsDefine.h>
#include <Base/BaseInput.h>
#include <Base/GameObjectUpdater.h>
#include <C++CLI/C++CLIInit.h>
#include <C++CLI/AssemblyHolder.h>
#include <EtherEngine/EditorObjectUpdater.h>
#include <EtherEngine/MSVCMediation.h>
#include <EtherEngine/ProjectMediation.h> 
#include <EtherEngine/EditorPopupWindow.h>
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
    // コンストラクタ
    EditorApplication::EditorApplication(void)
        : BaseMainWindow(WindowDefine::Name::EDITOR_APPLICATION)
        , m_isGameMode(false) {
    }
    // デストラクタ
    EditorApplication::~EditorApplication(void) {
    }


    // 初期化前関数
    void EditorApplication::InitFirstFunction(void) {
        //----- データ読み取り
#ifdef _DEBUG
        m_projectData = std::make_unique<ProjectData>();
        // @ MEMO : 全て深谷PCのパス等を打ち込んでいます。
        m_projectData->SetCmdPath("C:\\Windows\\System32\\cmd.exe");
        m_projectData->SetMsvcPath("/k \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat\"");
        m_projectData->SetVisualStudioPath("C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\devenv.com");

        m_projectEditorData = std::make_unique<ProjectEditorData>();
#endif // _DEBUG
    }
    // 初期化後関数
    void EditorApplication::InitLateFunction(void) {
        m_initUninitPerformer.AddInitUninit(
            [&]() { MSVCMediation::Get()->Init(m_projectData->GetCmdPath(), m_projectData->GetMsvcPath()); },
            []() { MSVCMediation::Get()->Uninit(); }
        );
        m_initUninitPerformer.AddInitUninit(
            [&]() { ProjectMediation::Get()->Init(PathClass::GetCurDirectory() / FileDefine::PROJECTNAME + FileDefine::Extended::SOLUTION, PathClass::GetCurDirectory() / FileDefine::PROJECTNAME + FileDefine::Extended::PROJECT); },
            []() { ProjectMediation::Get()->Uninit(); }
        );
        m_initUninitPerformer.AddInitUninit(
            [&]() { m_imGui = std::make_unique<IMGUI>(
                m_dxRender.GetAtomicData().GetDevice(),
                m_dxRender.GetAtomicData().GetContext(),
                m_hwnd.value()); },
            [&]() { m_imGui.reset(); }
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
        auto testWindow = EditorObjectStorage::Get()->CreateEditorObject();
        testWindow.GetAtomicData().AddComponent<EditorDebugWindow>();

        EditorMessagePopupResult result{};
        CreatePopWindow<EditorMessagePopup<EditorMessagePopupType::YesNoCancel>>(std::string("Hoge"), std::string("Fuga"), result);

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

        //----- メッセージループ
        MSG message;
        Timer fpsTimer;
        milliSecond frameSecond = 0;
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
            else {   
                //----- ゲーム処理
                frameSecond += fpsTimer.GetDeltaTime();

                //----- アセンブリ存在チェック
                if (AssemblyHolder::IsLoadAssemblyEnable() == false) {
                    //----- 存在しない。読み込みまたはリフレッシュ
                    // @ MEMO : 現時点では即リフレッシュしているがのちに「最新のファイルがある」場合は単なる読み込みにするべき
                    AssemblyHolder::LoadAssembly()
                }

                //----- FPS制御
                if (frameSecond < ONE_FRAME * 1000) continue;
                frameSecond = 0;

                //----- 更新
                InputSystem::Update();
                GlobalTimer::Get()->Update();

                //----- エディター更新処理
                EditorUpdater::Get()->Update();

                //----- 更新処理
                GameObjectUpdater::Get()->FixedUpdate();
                GameObjectUpdater::Get()->Update();

                //----- 描画前処理
                m_dxRender.GetAtomicData().BeginDraw();

                //----- 描画処理
                m_dxRender.GetAtomicData().Draw();

                //----- エディター描画処理
                EditorUpdater::Get()->Draw();

                //----- エディター描画後処理
                EditorUpdater::Get()->LateDraw();

                //----- 描画後処理
                m_dxRender.GetAtomicData().EndDraw();
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
