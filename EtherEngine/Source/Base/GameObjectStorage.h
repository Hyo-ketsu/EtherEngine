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
        // ゲームオブジェクトを追加する
        // @ Ret  : 追加したゲームオブジェクトのハンドル
        // @ Arg1 : 追加するゲームオブジェクト
        BaseHandle<GameObject> AddGameObject(GameObject& gameObject);
        // 全てのゲームオブジェクトを取得する
        std::vector<BaseHandle<GameObject>> GetGameObjectAll(void);

    private:

        friend class Singleton<GameObjectStorage>;

        std::vector<BaseHandle<GameObject>> m_gameObject;   // ゲームオブジェクトのハンドル
    };
}


#endif // !I_GAMEOBJECTSTORAGE_H
