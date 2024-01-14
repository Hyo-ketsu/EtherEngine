#include <EtherEngine/EditorObjectStorage.h>


//----- EditorObjectStorage定義
namespace EtherEngine {
    // 空のエディターオブジェクトを作成する
    Handle<EditorObject> EditorObjectStorage::CreateEditorObject(const Transform& transform) {
        Handle<EditorObject> handle = Handle<EditorObject>(EditorObject(transform));
        handle.GetAtomicData().m_handle = handle.GetHandle();
        m_editorObjects.push_back(std::move(handle));
        return m_editorObjects.back();
    }
    // エディターオブジェクトを削除する
    bool EditorObjectStorage::DeleteEditorObject(const Handle<EditorObject>& editorObject) {
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
    std::vector<Handle<EditorObject>> EditorObjectStorage::GetEditorObjectAll(void) {
        return m_editorObjects;
    }


    // 削除済みのエディターオブジェクトを削除する
    void EditorObjectStorage::DeleteEditorObjectsDelete(void) {
        for (auto it = m_editorObjects.begin(); it != m_editorObjects.end();) {
            if (it->GetAtomicData().GetDelete()) {
                //----- 削除
                it = m_editorObjects.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
