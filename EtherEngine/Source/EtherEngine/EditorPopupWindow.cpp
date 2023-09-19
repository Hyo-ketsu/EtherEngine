#include <EtherEngine/EditorPopupWindow.h>


//----- EditorPopupWindow ��`
namespace EtherEngine {
    // �R���X�g���N�^
    EditorPopupWindow::EditorPopupWindow(EditorObject* editorObject, const std::string& name, const bool isCloseButton, const ImGuiBackendFlags& flag)
        : EditorWindowBase(editorObject, name, flag) 
        , m_isCloseButton(isCloseButton) {
    }

    void EditorPopupWindow::UpdateWindow(void) {

    }
    void EditorPopupWindow::Draw(void) {
        ImGui::OpenPopup(m_name.c_str());

        //----- x�{�^���\����
        bool* isOpen = m_isCloseButton ? &m_isOpen : nullptr;

        //----- �E�B���h�E�`��
        if (ImGui::BeginPopupModal(m_name.c_str(), isOpen, m_flags)) {
            DrawWindow();
            ImGui::EndPopup();
        }

        //----- �����ꂽ�̂ł���΍폜����
        if (m_isOpen == false) EditorObjectStorage::Get()->DeleteEditorObject(EditorComponentHelper::GetEditorObject(this)->GetHandle());
    }
}
