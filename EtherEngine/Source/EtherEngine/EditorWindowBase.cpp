#include <EtherEngine/EditorWindowBase.h>


namespace EtherEngine {
    // コンストラクタ
    EditorWindowBase::EditorWindowBase(EditorObject* editorObject, const std::string& name, const ImGuiBackendFlags& flag)
        : EditorComponentBase(editorObject)
        , m_name(name) 
        , m_isOpen(true) 
        , m_flags(flag) {
    }

    void EditorWindowBase::Draw(void) {
        ImGui::Begin(m_name.c_str(), &m_isOpen, m_flags);
        DrawWindow();
        ImGui::End();
    }
}
