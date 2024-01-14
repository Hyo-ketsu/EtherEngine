#include <EtherEngine/EditorObjectStorage.h>


//----- EditorObjectStorage��`
namespace EtherEngine {
    // ��̃G�f�B�^�[�I�u�W�F�N�g���쐬����
    Handle<EditorObject> EditorObjectStorage::CreateEditorObject(const Transform& transform) {
        Handle<EditorObject> handle = Handle<EditorObject>(EditorObject(transform));
        handle.GetAtomicData().m_handle = handle.GetHandle();
        m_editorObjects.push_back(std::move(handle));
        return m_editorObjects.back();
    }
    // �G�f�B�^�[�I�u�W�F�N�g���폜����
    bool EditorObjectStorage::DeleteEditorObject(const Handle<EditorObject>& editorObject) {
        //----- �폜����n���h�����Ȃ߂�
        for (auto it = m_editorObjects.begin(); it != m_editorObjects.end(); it++) {
            if (*it == editorObject) {
                //----- ���n���h���B�폜����
                it->GetAtomicData().Delete();
                it->GetAtomicData().DeleteObject();
                return true;
            }
        }

        //----- �����n���h�������݂��Ȃ�
        return false;
    }


    // �S�ẴG�f�B�^�[�I�u�W�F�N�g���擾����
    std::vector<Handle<EditorObject>> EditorObjectStorage::GetEditorObjectAll(void) {
        return m_editorObjects;
    }


    // �폜�ς݂̃G�f�B�^�[�I�u�W�F�N�g���폜����
    void EditorObjectStorage::DeleteEditorObjectsDelete(void) {
        for (auto it = m_editorObjects.begin(); it != m_editorObjects.end();) {
            if (it->GetAtomicData().GetDelete()) {
                //----- �폜
                it = m_editorObjects.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
