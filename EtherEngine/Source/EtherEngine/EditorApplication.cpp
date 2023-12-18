#include <EtherEngine/EditorApplication.h>
#include <Base/Timer.h>
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
#include <Base/CameraStorage.h>
#include <EtherEngine/EditorUtility.h>


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
        , m_sceneView(gcnew System::Collections::Generic::List<EditorUI::EditorExclusionObject<EditorUI::SceneViewVM^>^>(0)) {
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
        auto cameraGameObejct = EditorObjectStorage::Get()->CreateEditorObject();
        cameraGameObejct.GetAtomicData().AccessTransform().AccessPostion().z() = -5;
        auto camera = cameraGameObejct.GetAtomicData().AddComponent<EditorCamera>();

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
        using namespace System::Collections::Generic;
        using namespace EditorUI;

        //----- 変数宣言
        List<MessageObject<SceneViewMessageType, EditorExclusionObject<SceneViewVM^>^>^>^ sceneViewMessage
            = gcnew List<MessageObject<SceneViewMessageType, EditorExclusionObject<SceneViewVM^>^>^>(0);

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
                auto window = EditorMessageQue<SceneViewMessageType, EditorExclusionObject<SceneViewVM^>^>::GetEngineMessage(SceneViewMessageType::Add);
                if (window == nullptr) break;

                //----- 前準備
                m_sceneView->Add(window->Data);
                auto size = window->Data->NoLock->NewWindowSize;    // このウィンドウのサイズ
                while (size.HasValue == false) {
                    ThreadingUtility::ThisThreadSleep();
                    size = window->Data->NoLock->NewWindowSize;
                }

                //----- 新規に作成
                auto id = m_dxRender->GetAtomicData().CreateDrawWindow(Eigen::Vector2i(size.Value.X, size.Value.Y), static_cast<HWND>(window->Data->NoLock->SceneViewTarget.ToPointer()), false);
                m_dxRender->GetAtomicData().GetWindowRender(id)->AccessWindowId() = window->Data->NoLock->ID->ID;
            }

            ////----- アセンブリ存在チェック
            //if (AssemblyHolder::IsLoadAssemblyEnable() == false && Refresh::GetRefreshState() != Refresh::RefreshStateType::CurrentlyRefresh) {
            //    //----- Refreshを行う
            //    if (false) {
            //        ProjectMediation::Get()->RefreshAssembly();
            //    }
            //}

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

            //----- SceneViewのメッセージの取得
            while (true) {
                auto window = EditorMessageQue<SceneViewMessageType, EditorExclusionObject<SceneViewVM^>^>::GetEngineMessage(SceneViewMessageType::Delete);
                if (window == nullptr) break;
                sceneViewMessage->Add(window);
            }
            //----- 描画処理
            for (int i = 0; i < m_sceneView->Count; i++) {
                //----- 各要素の取得
                auto sceneView = EditorUtility::ListGet<EditorExclusionObject<SceneViewVM^>^>(m_sceneView,i);
                auto& directXs = m_dxRender->GetAtomicData().AccessWindowRenders();

                //----- ロックの取得
                auto lock = sceneView->GetEngineLock();

                //----- 削除確認
                for (int j = 0; j < directXs.size(); j++) {
                    for each (auto it in sceneViewMessage) {
                        //----- こちらで保持しているSceneViewとウィンドウのIDが合致すれば両方を削除する
                        if (it->Data->NoLock->ID == sceneView->NoLock->ID && it->Data->NoLock->ID->ID == directXs[j].AccessWindowId()) {
                            //----- IDが合致する。削除
                            m_sceneView->RemoveAt(i);
                            directXs.erase(directXs.begin() + j);
                            j--;
                            i--;
                            goto LOOP_END;
                        }
                    }

                    //----- 削除はされていない。各描画処理
                    directXs[j].BeginDraw();
                    auto camera = CameraSystem::Get()->GetMainData();
                    if (camera.has_value()) {
                        directXs[j].Draw(*camera);
                    }
                    directXs[j].EndDraw();
                }
                
                LOOP_END: {
                //----- ロックの解除
                delete lock.Item1;
                }
            }
            ////----- エディター描画処理
            //EditorUpdater::Get()->Draw();

            ////----- エディター描画後処理
            //EditorUpdater::Get()->LateDraw();
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
