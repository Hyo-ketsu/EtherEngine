#ifndef I_GAMEOBJECTSTORAGE_H
#define I_GAMEOBJECTSTORAGE_H
#include <Base/Singleton.h>
#include <Base/Handle.h>
#include <Base/GameObject.h>


// @ MEMO : Sceneあたりは後回し
//----- GameObejctStorage宣言
namespace EtherEngine {
    // ゲームオブジェクトを管理するクラス
    class GameObjectStorage : public Singleton<GameObjectStorage> {
    public:
        // 空のゲームオブジェクトを作成する
        // @ Ret  : 作成したゲームオブジェクトのハンドル
        // @ Arg1 : 座標(デフォルト : 座標・回転は0, 拡縮は1)
        // @ Arg2 : 名前(Default : GameObject)
        Handle<GameObject> CreateGameObject(const Transform& transform = Transform(), const std::string& name = "GameObject");
        // ゲームオブジェクトを削除する
        // @ Ret  : 削除されたか
        // @ Arg1 : 削除するゲームオブジェクトのハンドル
        bool DeleteGameObject(const Handle<GameObject>& gameObject);


        // 全てのゲームオブジェクトを取得する
        std::vector<Handle<GameObject>> GetGameObjectAll(void) const;


        // 削除済みのゲームオブジェクトを削除する
        void DeleteGameObjectsDelete(void);

    private:
        friend class Singleton<GameObjectStorage>;

        std::vector<Handle<GameObject>> m_gameObjects;   // ゲームオブジェクトのハンドル
    };
}


#endif // !I_GAMEOBJECTSTORAGE_H
