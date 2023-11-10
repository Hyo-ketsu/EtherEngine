#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H
#include <Base/ProjectData.h>
#include <CPPCLI/BaseMainWindow.h>
#include <EtherEngine/ImGuiClass.h>
#include <EtherEngine/ProjectEditorData.h>


namespace EtherEngine {
    // エディター(ゲームエンジン)を表現するクラス(Singleton)
    class EditorApplication : public BaseMainWindow, public Singleton<EditorApplication> {
    public:
        // デストラクタ
        ~EditorApplication(void);


        // ウィンドウ機能使用可否ゲッター
        bool GetIsWindowFunctionEnable(void) const { return m_isWindowFunctionEnable; }


        // ゲームモードを開始する
        // @ Memo : 既に開始している際はゲームモードの再起動を行います
        void StartGameMode(void);
        // ゲームモードを一時中断する
        // @ Memo : 開始していない場合は特に何も起こりません
        void StopGameMode(void);
        // ゲームモードを終了する
        // @ Memo : 開始していない場合は特に何も起こりません
        void EndGameMode(void);


        // ウィンドウの移動などの有効無効を切り替える
        // @ Arg1 : 有効無効の設定
        // @ Arg2 : ウィンドウを閉じることも有効無効を切り替えるか(Default : true)
        void SetWindowFunctionEnable(const bool isEnable, const bool isClose = true);
        
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
        bool m_isWindowFunctionEnable;  // ウィンドウの機能が有効か
        std::unique_ptr<IMGUI> m_imGui; // 保持しているIMGUI
        std::unique_ptr<ProjectData> m_projectData; // 現在保持しているプロジェクトデータ
        std::unique_ptr<EditorData> m_editorData; // 現在保持しているエディターデータ

        friend Singleton<EditorApplication>;
    };
}


#endif // !I_EDITORAPPLICATION_H
