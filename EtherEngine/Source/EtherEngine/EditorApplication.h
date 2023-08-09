#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H
#include <Base/ProjectData.h>
#include <DirectX/BaseMainWindow.h>
#include <EtherEngine/ImGuiClass.h>
#include <EtherEngine/ProjectEditorData.h>


namespace EtherEngine {
    // エディター(ゲームエンジン)を表現するクラス(Singleton)
    class EditorApplication : public BaseMainWindow<EditorApplication> {
    public:
        // コンストラクタ
        EditorApplication(void);
        // デストラクタ
        ~EditorApplication(void);


        // 初期化関数
        virtual void InitFunction(void) override;
        // メイン関数
        void MainFunction(void) override;

    private:
        std::unique_ptr<IMGUI> m_imGui; // 保持しているIMGUI
        std::unique_ptr<ProjectData> m_projectData; // 現在保持しているプロジェクトデータ
        std::unique_ptr<ProjectEditorData> m_projectEditorData; // 現在保持しているエディターデータ
    };
}


#endif // !I_EDITORAPPLICATION_H
