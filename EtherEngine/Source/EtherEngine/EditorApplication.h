#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H
#include <Base/ProjectData.h>
#include <EngineLibrary/BaseMainWindow.h>
#include <EtherEngine/ImGuiClass.h>
#include <EtherEngine/ProjectEditorData.h>


//----- EditorApplication 宣言
namespace EtherEngine {
    // エディター(ゲームエンジン)を表現するクラス(Singleton)
    class EditorApplication : public BaseMainWindow, public Singleton<EditorApplication> {
    public:
        // デストラクタ
        ~EditorApplication(void);


        // ゲームモードを開始する
        // @ Memo : 既に開始している際はゲームモードの再起動を行います
        void StartGameMode(void);
        // ゲームモードを一時中断する
        // @ Memo : 開始していない場合は特に何も起こりません
        void StopGameMode(void);
        // ゲームモードを終了する
        // @ Memo : 開始していない場合は特に何も起こりません
        void EndGameMode(void);

    protected:
        // 初期化前関数
        void InitFirstFunction(void) override;
        // 初期化後関数
        void InitLateFunction(void) override;
        // 初期化終了後関数
        void EndInitLateFunction(void) override;
        // 終了前関数
        void UninitFirstFunction(void) override;
        // メイン関数
        void MainFunction(void) override;

    private:
        // コンストラクタ
        EditorApplication(void);

        bool m_isGameMode;  // ゲームを起動しているか
        std::unique_ptr<IMGUI> m_imGui; // 保持しているIMGUI
        std::unique_ptr<ProjectData> m_projectData; // 現在保持しているプロジェクトデータ
        std::unique_ptr<EditorData> m_editorData;   // 現在保持しているエディターデータ

        friend class Singleton<EditorApplication>;
    };
}


//----- Wrapper
namespace EtherEngine {
    namespace Wrapper {
        //----- エディターのアプリケーション
        public ref class EditorApplication {
        public:
            // エディターを終了させる
            static property bool IsGameLoop {
                void set(bool value){
                    EtherEngine::EditorApplication::Get()->SetIsGameLoop(value);
                }
            }
        };
    }
}


#endif // !I_EDITORAPPLICATION_H
