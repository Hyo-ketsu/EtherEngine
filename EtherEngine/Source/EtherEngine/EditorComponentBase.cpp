#include <EtherEngine/EditorComponentBase.h>


//----- EditorComponent����
namespace EtherEngine {
    // �R���X�g���N�^
    EditorComponentBase::EditorComponentBase(void* editorObject)
        : NativeBaseObject("EditorComponent")
        , m_eidtorObject(editorObject) 
        , m_isStart(false) {
    }


    // �e�G�f�B�^�[�I�u�W�F�N�g�擾
    void EditorComponentBase::GetEditorObject(void** editerObject) const {
        *editerObject = m_eidtorObject;
    }


    // �X�V����
    void EditorComponentBase::UpdateFunction(void) {
        //----- �A�N�e�B�u�`�F�b�J�[
        if (GetActive() == false) return;

        //----- �X�V�����E�Ⴕ���͏���������
        if (m_isStart) {
            //----- �X�V����
            Update();
        }
        else {
            //----- ����������
            Start();
            m_isStart = true;
        }
    }
    // �`�揈��
    void EditorComponentBase::DrawFunction(void) {
        //----- �A�N�e�B�u�`�F�b�J�[
        if (GetActive() == false) return;

        //----- �`�揈��
        Draw();
    }
    // �폜������
    void EditorComponentBase::DeleteFunction(void) {
        //----- �A�N�e�B�u�`�F�b�J�[
        if (GetActive() == false) return;

        //----- �폜������
        Delete();
    }
}
