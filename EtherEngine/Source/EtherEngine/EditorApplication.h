#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H

#include <Base/Singleton.h>
#include <DirectX/GameApplication.h>
#include <EtherEngine/ImGuiClass.h>


namespace EtherEngine {
    // エディター(ゲームエンジン)を表現するクラス(Singleton)
    class EditorApplication : public GameApplication, public Singleton<EditorApplication> {
    public:
        // デストラクタ
        ~EditorApplication(void) override {}


    private:
        // コンストラクタ
        using GameApplication::GameApplication;


        // 追加初期化(後)
        void InitLast(void) override;

        std::unique_ptr<IMGUI> m_imGui; // 保持しているIMGUI


        friend Singleton<EditorApplication>;
    };
}


#endif // !I_EDITORAPPLICATION_H
