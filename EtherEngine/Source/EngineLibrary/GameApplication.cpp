#include <EngineLibrary/GameApplication.h>
#include <Base/Timer.h>
#include <Base/BaseInput.h>
#include <Base/BaseDefines.h>
#include <Base/NativeGameObjectUpdater.h>
#include <Base/NativeGameObjectStorage.h>
#include <Base/CameraStorage.h>


//----- GameApplication 定義
#pragma managed
namespace EtherEngine {
    // コンストラクタ
    GameApplication::GameApplication(void)
        : m_isGameUpdate(true)
        , m_isGameDraw(true)
        , m_isLoop(true)
        , m_dxRender(new Handle<DirectXRender>(DirectXRender())) {
    }
    // デストラクタ
    GameApplication::~GameApplication(void) {
        this->!GameApplication();
    }
    // ファイナライザ
    GameApplication::!GameApplication(void) {
        Uninit();
    }


    // メイン関数
    void GameApplication::MainFunction(void) {
        //----- 初期化イベント発火
        InitEvent(this, System::EventArgs::Empty);

        //----- メインループ
        Timer fpsTimer;
        milliSecond frameSecond = 0;
        while (m_isLoop) {
            //----- ゲームループ初期イベント発火
            LoopFirstEvent(this, System::EventArgs::Empty);

            //----- ゲーム処理
            frameSecond += fpsTimer.GetDeltaTime();

            //----- FPS制御
            if (frameSecond < ONE_FRAME * 1000) continue;
            frameSecond = 0;

            //----- イベント用変数宣言
            bool isUpdate = false;  // 何らかのゲーム処理が行われたか

            //----- 入力やタイマー自体の更新
            InputSystem::Update();
            GlobalTimer::Get()->Update();

            //----- ゲームループのイベント発火
            if (m_isGameUpdate && m_isGameDraw) {
                //----- どちらも更新。
                GameLoopUpdateEvent(this, System::EventArgs::Empty);
            }
            if (!(m_isGameUpdate && m_isGameDraw)) {
                //----- どちらも更新しない。
                GameLoopStopEvent(this, System::EventArgs::Empty);
            }

            //----- 更新を行うかの判定
            if (m_isGameUpdate) {
                //----- 更新イベント発火
                GameUpdateEvent(this, System::EventArgs::Empty);

                //----- 更新処理
                NativeGameObjectUpdater::Get()->FixedUpdate();
                NativeGameObjectUpdater::Get()->Update();
            }

            //----- エディター更新処理
            EditorUpdateEvent(this, System::EventArgs::Empty);

            //----- 描画処理
            if (m_isGameDraw) {
                //----- 全ウィンドウに対して描画処理
                auto camera = CameraSystem::Get()->GetMainData();
                if (camera.has_value()) {
                    //----- 全ウィンドウ取得
                    auto&& window = m_dxRender->GetData().AccessWindowRenders();
                    for (auto&& it : window) {
                        //----- 描画前処理
                        it.BeginDraw();

                        {
                            //----- エディター描画処理
                            EditorDrawEvent(this, &*camera);

                            //----- エディター後描画処理
                            EditorLateDrawEvent(this, &*camera);

                            //----- ゲームオブジェクト描画処理
                            NativeGameObjectUpdater::Get()->Draw(*camera);
                        }

                        //----- 描画処理
                        it.Draw(*camera);
                        //----- 描画後処理
                        it.EndDraw();
                    }
                }
            }
        }
    }


    // 終了処理
    void GameApplication::Uninit(void) {
        DELETE_NULL(m_dxRender);
        UninitEvent(this, System::EventArgs::Empty);
    }
}
