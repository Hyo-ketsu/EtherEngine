#include <EtherEngine/EditorObjectStorage.h>
#include <Base/HandleHelper.h>


//----- EditorObjectStorage定義
namespace EtherEngine {
    // 空のエディターオブジェクトを作成する
    BaseHandle<EditorObject> EditorObjectStorage::CreateEditorObject(const Transform& transform) {
        BaseHandle<EditorObject> handle = Handle<EditorObject>(EditorObject(transform));
        handle.GetAtomicData().m_handle = handle;
        m_editorObjects.push_back(handle);
        return handle;
    }
    // エディターオブジェクトを削除する
    bool EditorObjectStorage::DeleteEditorObject(const BaseHandle<EditorObject>& editorObject) {
        //----- 削除するハンドルをなめる
        for (auto it = m_editorObjects.begin(); it != m_editorObjects.end(); it++) {
            if (*it == editorObject) {
                //----- 同ハンドル。削除する
                it->GetAtomicData().Delete();
                it->GetAtomicData().DeleteObject();
                return true;
            }
        }

        //----- 同じハンドルが存在しない
        return false;
    }


    // 全てのエディターオブジェクトを取得する
    std::vector<BaseHandle<EditorObject>> EditorObjectStorage::GetEditorObjectAll(void) {
        return m_editorObjects;
    }


    // 削除済みのエディターオブジェクトを削除する
    void EditorObjectStorage::DeleteEditorObjectsDelete(void) {
        for (auto it = m_editorObjects.begin(); it != m_editorObjects.end();) {
            if (it->GetAtomicData().GetDelete()) {
                //----- 削除
                it->Delete();
                it = m_editorObjects.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
