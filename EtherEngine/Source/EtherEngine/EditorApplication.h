#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H
#include <Base/ProjectData.h>
#include <Base/InitUninitPerformer.h>
#include <DirectX/DirectX.h>
#include <EngineLibrary/ManageSingleton.h>
#include <EtherEngine/ImGuiClass.h>
#include <EtherEngine/ProjectEditorData.h>


#pragma managed
//----- EditorApplication 宣言
namespace EtherEngine {
    // エディター(ゲームエンジン)を表現するクラス(Singleton)
    public ref class EditorApplication {
        ETHER_ENGINE_MANAGE_SINGLETON(EditorApplication);
    public:

        // デストラクタ
        ~EditorApplication(void);
        // ファイナライザ
        !EditorApplication(void);


        // DirectXゲッター
        const Handle<DirectXRender>& GetDirectX(void) { return *m_dxRender; }


        // ゲームループプロパティ
        property bool IsGameLoop {
            bool get(void) { return m_isMainLoop; }
            void set(bool value) { m_isMainLoop = value; }
        }


        // メイン関数
        void MainFunction(void);
        // ゲームモードを開始する
        // @ Memo : 既に開始している際はゲームモードの再起動を行います
        void StartGameMode(void);
        // ゲームモードを一時中断する
        // @ Memo : 開始していない場合は特に何も起こりません
        void StopGameMode(void);
        // ゲームモードを終了する
        // @ Memo : 開始していない場合は特に何も起こりません
        void EndGameMode(void);

    private:
        bool m_isMainLoop;  // メインループを行うか
        bool m_isGameMode;  // ゲームを起動しているか
        IMGUI* m_imGui;     // 保持しているIMGUI
        ProjectData* m_projectData; // 現在保持しているプロジェクトデータ
        EditorData* m_editorData;   // 現在保持しているエディターデータ
        Handle<DirectXRender>* m_dxRender;  // 保持しているDirectX
        System::Collections::Generic::List<EditorUI::SceneViewVM^>^ m_sceneView;    // 保持しているSceneView
    };
}


#endif // !I_EDITORAPPLICATION_H
