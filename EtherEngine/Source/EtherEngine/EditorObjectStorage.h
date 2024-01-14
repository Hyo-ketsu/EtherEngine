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
        Handle<EditorObject> CreateEditorObject(const Transform& transform = Transform());
        // エディターオブジェクトを削除する
        // @ Ret  : 削除が成功したか
        // @ Arg1 : 削除するオブジェクトのハンドル
        bool DeleteEditorObject(const Handle<EditorObject>& editorObject);


        // 全てのエディターオブジェクトを取得する
        std::vector<Handle<EditorObject>> GetEditorObjectAll(void);


        // 削除済みのエディターオブジェクトを削除する
        void DeleteEditorObjectsDelete(void);

    private:
        friend class CentrallySingleton;

        std::vector<Handle<EditorObject>> m_editorObjects;   // エディターオブジェクトのハンドル
    };
}


#endif // !I_EDITOROBJECTSTORAGE_H
