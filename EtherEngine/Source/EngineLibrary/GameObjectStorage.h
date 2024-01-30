#ifndef I_GAMEOBJECTSTORAGE_H
#define I_GAMEOBJECTSTORAGE_H
#include <EngineLibrary/ManageSingleton.h>
#include <EngineLibrary/GameObject.h>


//----- GameObjectStorage 宣言
namespace EtherEngine {
    // ゲームオブジェクトを管理するクラス
    public ref class GameObjectStorage {
        ETHER_ENGINE_MANAGE_SINGLETON(GameObjectStorage);
    public:
        // ゲームオブジェクトを追加する
        // @ Arg1 : 追加するゲームオブジェクト
        void AddGameObject(GameObject^ gameObject);
        // ゲームオブジェクトを削除する
        // @ Arg1 : 削除するゲームオブジェクト
        void DeleteGameObject(GameObject^ gameObject);
        // ゲームオブジェクトを削除する
        // @ Arg1 : 削除するゲームオブジェクト
        void DeleteGameObject(IDClass^ id);
        // ゲームオブジェクトを全削除する
        void DeleteAllGameObject(void);


        // ゲームオブジェクトの追加・削除バージョン
        property int UpdateGameObjectVersion {
            int get(void) { return m_updateVersion; }
        }


        // 全てのゲームオブジェクトを取得する
        property System::Collections::Generic::List<GameObject^>^ GameObjects {
            System::Collections::Generic::List<GameObject^>^ get(void) { return m_gameObjects; }
        }


    private:
        System::Collections::Generic::List<GameObject^>^ m_gameObjects; // 保持しているゲームオブジェクトの一覧
        int m_updateVersion;    // ゲームオブジェクトの追加・削除バージョン
    };

}


#endif // !I_GAMEOBJECTSTORAGE_H
