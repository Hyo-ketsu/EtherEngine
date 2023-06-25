#include <EtherEngine/EditorObjectStorage.h>
#include <Base/HandleHelper.h>


//----- EditorObjectStorage��`
namespace EtherEngine {
    // ��̃G�f�B�^�[�I�u�W�F�N�g���쐬����
    BaseHandle<EditorObject> EditorObjectStorage::CreateGameObject(const Transform& transform) {
        BaseHandle<EditorObject> handle = Handle<EditorObject>(EditorObject(transform));
        handle.GetAtomicData().m_handle = handle;
        m_editorObjects.push_back(handle);
        return handle;
    }
    // �S�ẴG�f�B�^�[�I�u�W�F�N�g���擾����
    std::vector<BaseHandle<EditorObject>> EditorObjectStorage::GetGameObjectAll(void) {
        return m_editorObjects;
    }
}
