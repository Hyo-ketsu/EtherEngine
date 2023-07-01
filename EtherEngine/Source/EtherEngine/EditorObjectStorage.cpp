#include <EtherEngine/EditorObjectStorage.h>
#include <Base/HandleHelper.h>


//----- EditorObjectStorage��`
namespace EtherEngine {
    // ��̃G�f�B�^�[�I�u�W�F�N�g���쐬����
    BaseHandle<EditorObject> EditorObjectStorage::CreateEditorObject(const Transform& transform) {
        BaseHandle<EditorObject> handle = Handle<EditorObject>(EditorObject(transform));
        handle.GetAtomicData().m_handle = handle;
        m_editorObjects.push_back(handle);
        return handle;
    }
    // �G�f�B�^�[�I�u�W�F�N�g���폜����
    bool EditorObjectStorage::DeleteEditorObject(const BaseHandle<EditorObject>& editorObject) {
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
    std::vector<BaseHandle<EditorObject>> EditorObjectStorage::GetEditorObjectAll(void) {
        return m_editorObjects;
    }


    // �폜�ς݂̃G�f�B�^�[�I�u�W�F�N�g���폜����
    void EditorObjectStorage::DeleteEditorObjectsDelete(void) {
        for (auto it = m_editorObjects.begin(); it != m_editorObjects.end();) {
            if (it->GetAtomicData().GetDelete()) {
                //----- �폜
                it->Delete();
                it = m_editorObjects.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
