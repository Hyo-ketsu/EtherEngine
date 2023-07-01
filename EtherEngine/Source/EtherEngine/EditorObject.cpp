#include <EtherEngine/EditorObject.h>


//----- EditorObject��`
namespace EtherEngine {
    // �R���X�g���N�^
    EditorObject::EditorObject(const Transform& transform, const std::string& name)
        : BaseObject(name)
        , m_transform(transform) {
    }


    // �X�V�������s��
    void EditorObject::Update(void) {
        //----- �A�N�e�B�u�`�F�b�J�[
        if (GetActive() == false) return;
        if (GetDelete()) return;

        //----- �X�V����
        for (auto&& component : m_components) {
            component->UpdateFunction();
        }
        DeleteComponentsDelete();
    }
    // �`�揈�����s��
    void EditorObject::Draw(void) {
        //----- �A�N�e�B�u�`�F�b�J�[
        if (GetActive() == false) return;
        if (GetDelete()) return;

        //----- �`�揈��
        for (auto&& component : m_components) {
            component->DrawFunction();
        }
        DeleteComponentsDelete();
    }
    // �폜���������s��
    void EditorObject::Delete(void) {
        //----- �A�N�e�B�u�`�F�b�J�[
        if (GetActive() == false) return;
        if (GetDelete()) return;

        //----- �폜������
        for (auto&& component : m_components) {
            component->DeleteFunction();
        }
        DeleteComponentsDelete();
    }


    // �폜���ꂽ�R���|�[�l���g���폜����
    void EditorObject::DeleteComponentsDelete(void) {
        if (m_components.empty()) return;
        for (auto it = m_components.begin(); it != m_components.end();) {
            //----- �폜���邩
            if ((*it)->GetDelete()) {
                //----- �폜����Ă�B�폜
                it = m_components.erase(it);
            }
            else {
                it++;
            }
        }
    }
}
