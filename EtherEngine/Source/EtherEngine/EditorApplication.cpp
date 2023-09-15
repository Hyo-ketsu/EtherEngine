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


    // 初期化関数
    void EditorApplication::InitFirstFunction(void) {
        //----- データ読み取り
        // @ MEMO : ひとまず仮で（現状ProjectData側でデータを生成しているので）
        m_projectData = std::make_unique<ProjectData>();
        m_projectEditorData = std::make_unique<ProjectEditorData>();
    }
    // 初期化関数
    void EditorApplication::InitLateFunction(void) {
        m_initUninitPerformer.AddInitUninit(
            [&]() { MSVCMediation::Get()->Init(m_projectData->GetCmdPath(), m_projectData->GetMsvcPath()); },
            []() { MSVCMediation::Get()->Uninit(); }
        );
        m_initUninitPerformer.AddInitUninit(
            [&]() { ProjectMediation::Get()->Init(PathClass::GetCurDirectory() / FileDefine::PROJECTNAME + FileDefine::SOLUTION, PathClass::GetCurDirectory() / FileDefine::PROJECTNAME + FileDefine::PROJECT); },
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
    // メイン関数
    void EditorApplication::MainFunction(void) {
#ifdef _DEBUG
        //----- テストウィンドウ
        auto testWindow = EditorObjectStorage::Get()->CreateEditorObject();
        testWindow.GetAtomicData().AddComponent<EditorDebugWindow>(ImGuiDefine::Name::WINDOW_DEBUG);

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
}