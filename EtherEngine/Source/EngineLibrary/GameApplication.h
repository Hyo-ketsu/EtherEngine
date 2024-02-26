#ifndef I_GAMEAPPLICATION_H
#define I_GAMEAPPLICATION_H
#include <Base/Handle.h>
#include <DirectX/DirectX.h>
#include <EngineLibrary/ManageSingleton.h>


//----- GameApplication 宣言
#pragma managed
namespace EtherEngine {
    // 描画用イベント定義
    delegate void EditorDrawEventHandler(System::Object^ s, CameraData* e);


    // ゲームを表現するクラス(Singleton)
    public ref class GameApplication {
        ETHER_ENGINE_MANAGE_SINGLETON(GameApplication);
    public:
        // デストラクタ
        ~GameApplication(void);
        // ファイナライザ
        !GameApplication(void);


        // DirectXゲッター
        void GetDirectX(void** pointer) { *pointer = m_dxRender; }
        // DirectXゲッター
        Handle<DirectXRender>* GetDirectX(void) { return m_dxRender; }


        // ゲームオブジェクト更新プロパティ
        property bool IsGameUpdate {
            bool get(void) { return m_isGameUpdate; }
            void set(bool value) { m_isGameUpdate = value; }
        }
        // ゲームオブジェクト描画プロパティ
        property bool IsGameDraw {
            bool get(void) { return m_isGameDraw; }
            void set(bool value) { m_isGameDraw = value; }
        }
        // ゲームオブジェクト処理プロパティ
        property bool IsGame {
            void set(bool value) { m_isGameUpdate = m_isGameDraw = value; }
        }


        // ゲーム終了関数
        void GameEnd(void) { m_isLoop = false; }


        // メイン関数
        void MainFunction(void);

        event System::EventHandler^ InitEvent;      // 初期化処理
        event System::EventHandler^ UninitEvent;    // 終了時処理

        event System::EventHandler^ GameUpdateEvent;        // ゲームオブジェクトの更新処理が行われた時に発火するイベント
        event System::EventHandler^ GameLoopUpdateEvent;    // ゲームループの更新時に発火するイベント
        event System::EventHandler^ GameLoopStopEvent;      // ゲームループの停止時に発火するイベント

        event System::EventHandler^ EditorUpdateEvent;      // エディターの更新処理
        event EditorDrawEventHandler^ EditorDrawEvent;      // エディターの描画処理
        event EditorDrawEventHandler^ EditorLateDrawEvent;  // エディターの描画後処理

        event System::EventHandler^ LoopFirstEvent;         // ループの先(FPS計測より先に)発火するイベント

    private:
        // 終了処理
        void Uninit(void);


        bool m_isGameUpdate;  // ゲームオブジェクトの更新処理(Delete以外のUpdate)を行うか
        bool m_isGameDraw;    // ゲームオブジェクトの描画処理を行うか
        bool m_isLoop;        // メインループを行うか
        Handle<DirectXRender>* m_dxRender;  // 保持しているDirectX
    };
}


#endif // !I_GAMEAPPLICATION_H
