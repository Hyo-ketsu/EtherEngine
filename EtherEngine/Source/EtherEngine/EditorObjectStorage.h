#ifndef I_EDITOROBJECTSTORAGE_H
#define I_EDITOROBJECTSTORAGE_H
#include <Base/Singleton.h>
#include <Base/Handle.h>
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorComponentHelper.h>


// @ MEMO : Sceneあたりは後回し
//----- GameObejctStorage宣言
namespace EtherEngine {
    // エディターオブジェクトを管理するクラス
    class EditorObjectStorage : public Singleton<EditorObjectStorage> {
    public:
        // 空のエディターオブジェクトを作成する
        // @ Ret  : 作成したエディターオブジェクトのハンドル
        // @ Arg1 : 座標(デフォルト : 座標・回転は0, 拡縮は1)
        BaseHandle<EditorObject> CreateGameObject(const Transform& transform = Transform());
        // 全てのエディターオブジェクトを取得する
        std::vector<BaseHandle<EditorObject>> GetGameObjectAll(void);

    private:
        friend class Singleton<EditorObjectStorage>;


        std::vector<BaseHandle<EditorObject>> m_editorObjects;   // エディターオブジェクトのハンドル
    };
}


#endif // !I_EDITOROBJECTSTORAGE_H
