#include <EngineLibrary/SceneLoader.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/GameObjectStorage.h>
#include <Base/NativeGameObjectStorage.h>
#include <Base/NativeGameObjectUpdater.h>


//----- SceneLoader 定義
namespace EtherEngine {
    // シーンを追加する
    void SceneLoader::AddScene(Scene^ addScene) {
        using namespace System::Text::Json;

        //----- まずシーンを追加
        m_thisScenes->Add(addScene);

        //----- シーンに基づいてゲームオブジェクトを生成する
        // @ MEMO : 制作中
        // @ MEMO : 制作中
        // @ MEMO : 制作中
        auto sceneJson = addScene->GetScene();
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
    generic <typename SceneType>
    void SceneLoader::MoveScene(void) {
        DeleteAllScene();
        AddScene<SceneType>();
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
