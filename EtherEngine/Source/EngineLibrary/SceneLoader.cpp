#include <EngineLibrary/SceneLoader.h>
#include <Base/NativeGameObjectStorage.h>
#include <Base/NativeGameObjectUpdater.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/GameObjectStorage.h>
#include <EngineLibrary/ClassLoader.h>


//----- SceneLoader 定義
namespace EtherEngine {
    // コンストラクタ
    SceneLoader::SceneLoader(void) 
        : m_thisScenes(gcnew System::Collections::Generic::List<Scene^>(1)) {
    }


    // シーンを追加する
    void SceneLoader::AddScene(Scene^ addScene) {
        using namespace Newtonsoft::Json;
        using namespace Newtonsoft::Json::Linq;

        //----- まずシーンを追加
        m_thisScenes->Add(addScene);

        //----- 変数宣言
        System::String^ sceneData = addScene->GetScene();

        //----- 生成前にチェック
        if (sceneData == System::String::Empty) return; // 何も生成しない。

        //----- シーンに基づいてゲームオブジェクトを生成する
        auto sceneJson = JObject::Parse(addScene->GetScene());
        for each (auto gameObject in sceneJson) {
            ClassLoader::Input(gameObject.Value->ToString(), gcnew GameObject());   // @ Memo : gameObjectのエラーは無視して下さい……正常にビルドできます
        }
    }
    // シーンを削除する
    generic <typename SceneType>
    void SceneLoader::DeleteScene(void) {
        for (int i = 0; i < m_thisScenes->Count; i++) {
            auto scene = EditorUtility::ListGet(m_thisScenes, i);
            if (scene->GetType() == SceneType::typeid) {
                NativeGameObjectStorage::Get()->DeleteGameObject(scene->GetSceneID());
                m_thisScenes->RemoveAt(i);
            }
        }
    }
    // シーンを全て削除する
    void SceneLoader::DeleteAllScene(void) {
        for each (auto it in m_thisScenes) {
            NativeGameObjectStorage::Get()->DeleteGameObject(it->GetSceneID());
        }
        m_thisScenes->Clear();
    }
    // シーンを移動する
    void SceneLoader::MoveScene(Scene^ moveScene) {
        DeleteAllScene();
        AddScene(moveScene);
    }


    // 指定シーンを取得する
    generic <typename SceneType>
    Scene^ SceneLoader::GetScene(void) {
        for (int i = 0; i < m_thisScenes->Count; i++) {
            auto scene = EditorUtility::ListGet(m_thisScenes, i);
            if (scene->GetType() == SceneType::typeid) {
                return scene;
            }
        }
    }
    // 全てのシーンを取得する
    System::Collections::Generic::List<Scene^>^ SceneLoader::GetAllScene(void) {
        return m_thisScenes;
    }
}
