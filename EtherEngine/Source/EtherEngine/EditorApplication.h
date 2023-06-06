#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H
#include <DirectX/BaseMainWindow.h>
#include <EtherEngine/ImGuiClass.h>


namespace EtherEngine {
    // エディター(ゲームエンジン)を表現するクラス(Singleton)
    class EditorApplication : public BaseMainWindow<EditorApplication> {
    public:
        // コンストラクタ
        EditorApplication(void);
        // デストラクタ
        ~EditorApplication(void);


        // メイン関数
        void MainFunction(void) override;

    private:
        std::unique_ptr<IMGUI> m_imGui; // 保持しているIMGUI
    };
}


#endif // !I_EDITORAPPLICATION_H
