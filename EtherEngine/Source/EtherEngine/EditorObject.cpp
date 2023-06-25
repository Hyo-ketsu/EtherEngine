#include <EtherEngine/EditorObject.h>


//----- EditorObject��`
namespace EtherEngine {
    // �R���X�g���N�^
    EditorObject::EditorObject(const Transform& transform)
        : m_transform(transform) {
    }


    // �X�V�������s��
    void EditorObject::Update(void) {
        for (auto&& it : m_component) {
            it->UpdateFunction();
        }
    }
    // �`�揈�����s��
    void EditorObject::Draw(void) {
        for (auto&& it : m_component) {
            it->DrawFunction();
        }
    }
}
