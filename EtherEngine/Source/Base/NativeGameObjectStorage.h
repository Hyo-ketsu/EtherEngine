#ifndef I_NATIVEGAMEOBJECTSTORAGE_H
#define I_NATIVEGAMEOBJECTSTORAGE_H
#include <Base/Singleton.h>
#include <Base/Handle.h>
#include <Base/NativeGameObject.h>


// @ MEMO : Sceneあたりは後回し
//----- GameObejctStorage宣言
namespace EtherEngine {
    // ゲームオブジェクトを管理するクラス
    class NativeGameObjectStorage : public Singleton<NativeGameObjectStorage> {
    public:
        // 空のゲームオブジェクトを作成する
        // @ Ret  : 作成したゲームオブジェクトのハンドル
        // @ Arg1 : 座標(デフォルト : 座標・回転は0, 拡縮は1)
        // @ Arg2 : 名前(Default : NativeGameObject)
        Handle<NativeGameObject> CreateGameObject(const Transform& transform = Transform(), const std::string& name = "GameObject");
        // ゲームオブジェクトを削除する
        // @ Ret  : 削除されたか
        // @ Arg1 : 削除するゲームオブジェクトのハンドル
        bool DeleteGameObject(const Handle<NativeGameObject>& gameObject);
        // ゲームオブジェクトを削除する
        // @ Arg1 : 削除するシーン
        void DeleteGameObject(const SceneIDType& deleteScene);


        // 全てのゲームオブジェクトを取得する
        std::vector<Handle<NativeGameObject>> GetGameObjectAll(void) const;


        // 削除済みのゲームオブジェクトを削除する
        void DeleteGameObjectsDelete(void);

    private:
        friend class CentrallySingleton;

        std::vector<Handle<NativeGameObject>> m_gameObjects;   // ゲームオブジェクトのハンドル
    };
}


#endif // !I_NATIVEGAMEOBJECTSTORAGE_H
