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
        BaseHandle<GameObject> CreateEditorObject(const Transform& transform = Transform());
        // ゲームオブジェクトを削除する
        // @ Ret  : 削除されたか
        // @ Arg1 : 削除するゲームオブジェクトのハンドル
        bool DeleteGameObject(const BaseHandle<GameObject>& gameObject);


        // 全てのゲームオブジェクトを取得する
        std::vector<BaseHandle<GameObject>> GetEditorObjectAll(void);


        // 削除済みのゲームオブジェクトを削除する
        void DeleteGameObjectsDelete(void);

    private:
        friend class Singleton<GameObjectStorage>;

        std::vector<BaseHandle<GameObject>> m_gameObjects;   // ゲームオブジェクトのハンドル
    };
}


#endif // !I_GAMEOBJECTSTORAGE_H
