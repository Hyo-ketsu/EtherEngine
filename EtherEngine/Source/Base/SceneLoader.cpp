#include <Base/SceneLoader.h>
#include <Base/DirectoryNameDefine.h>


namespace EtherEngine {
    // コンストラクタ
    SceneLoader::SceneLoader(void) {
    }
    // デストラクタ
    SceneLoader::~SceneLoader(void) {
    }


    // シーン追加
    void SceneLoader::AddScene(const SceneData data) {
        //----- 読み込みディレクトリ修飾
        // @ Memo : Hoge -> Scene/Hoge.dll
        std::string loadSceneName;
        if (data.rfind(".dll") == std::string::npos) {
            loadSceneName = DirectoryDefine::SCENE_DATA + data + ",dll";
        }
        else {
            loadSceneName = DirectoryDefine::SCENE_DATA + data;
        }

        //----- DLL読み込み
        HMODULE dll = LoadLibrary(loadSceneName.c_str());
        if (dll == nullptr) { throw std::exception("Error!"); }

        //----- シーン読み込み
        using InitSceneFunction = void*(__stdcall*)();
        auto InitScene = (InitSceneFunction)GetProcAddress(dll, ETHERENGINE_INIT_SCENE_FUNCTION_LITERAL);
        // @ MEMO : 思い出したら関数がなかった場合の例外処理

        //----- 読み込んだシーンを用いて初期化を行う
        m_currentSceneData = data;
        InitScene();
    }
    // シーン削除
    void SceneLoader::DeleteScene(const SceneData data) {

    }
    // シーン削除
    void SceneLoader::DeleteScene(void) {

    }
    // シーン移動
    void SceneLoader::MoveScene(const SceneData data) {

    }
}
