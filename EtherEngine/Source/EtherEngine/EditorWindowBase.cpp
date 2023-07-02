#include <EtherEngine/EditorWindowBase.h>
#include <EtherEngine/EditorObjectStorage.h>


namespace EtherEngine {
    // �R���X�g���N�^
    EditorWindowBase::EditorWindowBase(EditorObject* editorObject, const std::string& name, const ImGuiBackendFlags& flag)
        : EditorComponentBase(editorObject)
        , m_name(name) 
        , m_isOpen(true) 
        , m_flags(flag) {
    }

    void EditorWindowBase::Draw(void) {
        //----- �E�B���h�E�`��
        ImGui::Begin(m_name.c_str(), &m_isOpen, m_flags);
        DrawWindow();
        ImGui::End();

        //----- �����ꂽ�̂ł���΍폜����
        if (m_isOpen == false) EditorObjectStorage::Get()->DeleteEditorObject(EditorComponentHelper::GetEditorObject(this)->GetHandle());
    }
}
