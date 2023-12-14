#include <EngineLibrary/GameApplication.h>
#include <Base/Timer.h>
#include <Base/WindowsDefine.h>
#include <Base/GameObjectUpdater.h>
#include <Base/BaseInput.h>
#include <Base/CameraStorage.h>
#include <EngineLibrary/ManageFunctionInit.h>


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
        : BaseMainWindow(WindowDefine::Name::GAME_APPLICATION) {
    }
    // デストラクタ
    GameApplication::~GameApplication(void) {
        HandleSystem<DirectXRender>::Get()->DeleteItem(m_dxRender);
    }


    // メイン関数
    void GameApplication::MainFunction(void) {
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
            else {   //----- ゲーム処理
                //----- 定期更新処理
                frameSecond += fpsTimer.GetDeltaTime();

                //----- FPS制御
                if (frameSecond < (ONE_FRAME * 1'000)) continue;
                frameSecond = 0;

                //----- Update処理
                GameObjectUpdater::Get()->Update();

                //----- 描画前処理
                m_dxRender.GetAtomicData().AccessWindowRenders()[0].BeginDraw();

                //----- 描画処理
                auto camera = CameraSystem::Get()->GetMainData();
                if (camera.has_value()) {
                    m_dxRender.GetAtomicData().AccessWindowRenders()[0].Draw(*camera);
                }

                //----- 描画後処理
                m_dxRender.GetAtomicData().AccessWindowRenders()[0].EndDraw();
            }
        }

        //----- 終了処理
        m_initUninitPerformer.UnInit();
    }
}
