#include <EtherEngine/EditorComponentBase.h>


//----- EditorComponent����
namespace EtherEngine {
    // �R���X�g���N�^
    EditorComponentBase::EditorComponentBase(void* editorObject)
        : m_eidtorObject(editorObject) 
        , m_isStart(false) {
    }


    // �e�G�f�B�^�[�I�u�W�F�N�g�擾
    void EditorComponentBase::GetEditorObject(void** editerObject) const {
        *editerObject = m_eidtorObject;
    }


    // �X�V����
    void EditorComponentBase::UpdateFunction(void) {
        if (m_isStart) {
            Update();
        }
        else {
            Start();
            m_isStart = true;
        }
    }
    // �`�揈��
    void EditorComponentBase::DrawFunction(void) {
        Draw();
    }
}
