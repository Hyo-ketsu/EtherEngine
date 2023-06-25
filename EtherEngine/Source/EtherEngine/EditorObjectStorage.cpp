#include <EtherEngine/EditorObjectStorage.h>
#include <Base/HandleHelper.h>


//----- EditorObjectStorage定義
namespace EtherEngine {
    // 空のエディターオブジェクトを作成する
    BaseHandle<EditorObject> EditorObjectStorage::CreateGameObject(const Transform& transform) {
        BaseHandle<EditorObject> handle = Handle<EditorObject>(EditorObject(transform));
        handle.GetAtomicData().m_handle = handle;
        m_editorObjects.push_back(handle);
        return handle;
    }
    // 全てのエディターオブジェクトを取得する
    std::vector<BaseHandle<EditorObject>> EditorObjectStorage::GetGameObjectAll(void) {
        return m_editorObjects;
    }
}
