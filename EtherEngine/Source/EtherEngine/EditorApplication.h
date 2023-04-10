#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H

#include <Base/Singleton.h>
#include <DirectX/GameApplication.h>


namespace EtherEngine {
    // エディター(ゲームエンジン)を表現するクラス(Singleton)
    class EditorApplication : public GameApplication, public Singleton<EditorApplication> {
    public:
        using GameApplication::GameApplication;


    private:
        // コンストラクタ
        EditorApplication(void) {}
        // デストラクタ
        ~EditorApplication(void) override {}


        friend Singleton<EditorApplication>;
    };
}


#endif // !I_EDITORAPPLICATION_H
