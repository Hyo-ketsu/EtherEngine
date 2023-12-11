#include <EtherEngine/EditorApplication.h>
#include <Base/Timer.h>
#include <Base/HandleHelper.h>
#include <Base/WindowsDefine.h>
#include <Base/BaseInput.h>
#include <Base/BaseDefines.h>
#include <Base/GameObjectUpdater.h>
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
#include <Base/ThreadingUtility.h>


#pragma managed
//----- EditorApplication 定義
namespace EtherEngine {
    // コンストラクタ
    EditorApplication::EditorApplication(void) 
        : m_isMainLoop(true)
        , m_isGameMode(false)
        , m_imGui(nullptr)
        , m_projectData(nullptr)
        , m_editorData(nullptr) 
        , m_dxRender(new Handle<DirectXRender>(DirectXRender())) 
        , m_sceneView(gcnew System::Collections::Generic::List<EditorUI::SceneViewVM^>(1)) {
    }
    // デストラクタ
    EditorApplication::~EditorApplication(void) {
        this->!EditorApplication();
    }
    // ファイナライザ
    EditorApplication::!EditorApplication(void) {
        DELETE_NULL(m_imGui);
        DELETE_NULL(m_projectData);
        DELETE_NULL(m_dxRender);
        m_sceneView = nullptr;
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
        //m_imGui = new IMGUI(*m_dxRender->GetAtomicData().GetEditableDevice(), *m_dxRender->GetAtomicData().GetEditableContext(),);

        ////----- プロジェクト設定の読み込み
        //try {
        //    m_projectData = new ProjectData(PathClass::GetCurDirectory() / EditorFileDefine::Directory::EDITOR_SETTING / EditorFileDefine::PROJECT_DATA);
        //}
        //catch (const EditorException& e) {
        //    using namespace EditorUI;

        //    //----- ない。スタートアップウィンドウ起動
        //    auto VM = CreateEditorWindow::AddCreateWindow<StartupWindow^, StartupVM^>(true);

        //    //----- スタートアップウィンドウ終了待ち
        //    StartupMessage^ message = nullptr;
        //    while (message == nullptr) {
        //        message = MessageQue<StartupMessage^>::GetEngineMessage();
        //        ThreadingUtility::ThisThreadSleep();
        //    }

        //    //----- 取得したパスを設定
        //    m_projectData = new ProjectData();
        //    m_projectData->SetMSBuildPath(ManageToUnmanage::String(message->Path));
        //}

        //----- メインループ
        Timer fpsTimer;
        milliSecond frameSecond = 0;
        while (m_isMainLoop) {
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
                m_dxRender->GetAtomicData().CreateDrawWindow(Eigen::Vector2i(size.Value.X, size.Value.Y),static_cast<HWND>(engineLock.Item2->SceneViewTarget.ToPointer()),
                    false, drawFunction, enableFunction, windowFunction);
            }

            ////----- アセンブリ存在チェック
            //if (AssemblyHolder::IsLoadAssemblyEnable() == false && Refresh::GetRefreshState() != Refresh::RefreshStateType::CurrentlyRefresh) {
            //    //----- Refreshを行う
            //    if (false) {
            //        ProjectMediation::Get()->RefreshAssembly();
            //    }
            //}

            //----- シーンウィンドウ更新処理
            auto& windowData = m_dxRender->GetAtomicData();
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
            for (auto&& it : m_dxRender->GetAtomicData().AccessWindowRenders()) {
                it.BeginDraw();
            }

            //----- 描画処理
            for (auto&& it : m_dxRender->GetAtomicData().AccessWindowRenders()) {
                it.Draw();
            }

            ////----- エディター描画処理
            //EditorUpdater::Get()->Draw();

            ////----- エディター描画後処理
            //EditorUpdater::Get()->LateDraw();

            //----- 描画後処理
            for (auto&& it : m_dxRender->GetAtomicData().AccessWindowRenders()) {
                it.EndDraw();
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
