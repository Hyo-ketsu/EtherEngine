#ifndef I_SCENELOADER_H
#define I_SCENELOADER_H
#include <Base/BaseDefines.h>
#include <EngineLibrary/ManageSingleton.h>
#include <EngineLibrary/Scene.h>


// @ MEMO : 想定するJsonの作り
// {
//     "ID" : 123456789
//     "Name" : "なんちゃら"
//     "Component" :  {
//         "PlayerComponent" : {
//              // 以下コンポーネントのデータ
//          }
//     }
// }
// {
//     "ID" : 123456789
//     "Name" : "なんちゃら"
//     "Component" :  {
//         "PlayerComponent" : {
//              // 以下コンポーネントのデータ
//          }
//     }
// }


//----- SceneLoader 定義
namespace EtherEngine {
    public ref class SceneLoader {
        ETHER_ENGINE_MANAGE_SINGLETON(SceneLoader);
    public:
        // シーンを追加する
        // @ Arg1 : 追加するシーン
        void AddScene(Scene^ addScene);
        // シーンを削除する
        // @ Genr : 削除するシーン
        generic <typename SceneType> where SceneType : Scene
        void DeleteScene(void);
        // シーンを全て削除する
        void DeleteAllScene(void);
        // シーンを移動する
        // @ Memo : 全て削除後、シーンを追加する形です
        // @ arg1 : 追加するシーン
        void MoveScene(Scene^ moveScene);


        // 指定シーンを取得する
        // @ Genr : 取得するシーン
        generic <typename SceneType> where SceneType : Scene
        Scene^ GetScene(void);
        // 全てのシーンを取得する
        // @ Ret  : 取得したすべてのシーン
        System::Collections::Generic::List<Scene^>^ GetAllScene(void);

    private:
        System::Collections::Generic::List<Scene^>^ m_thisScenes;
    };
}


#endif // !I_SCENELOADER_H
