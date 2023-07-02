#include <EtherEngine/EditorWindowBase.h>
#include <EtherEngine/EditorObjectStorage.h>


namespace EtherEngine {
    // コンストラクタ
    EditorWindowBase::EditorWindowBase(EditorObject* editorObject, const std::string& name, const ImGuiBackendFlags& flag)
        : EditorComponentBase(editorObject)
        , m_name(name) 
        , m_isOpen(true) 
        , m_flags(flag) {
    }

    void EditorWindowBase::Draw(void) {
        //----- ウィンドウ描画
        ImGui::Begin(m_name.c_str(), &m_isOpen, m_flags);
        DrawWindow();
        ImGui::End();

        //----- 消されたのであれば削除する
        if (m_isOpen == false) EditorObjectStorage::Get()->DeleteEditorObject(EditorComponentHelper::GetEditorObject(this)->GetHandle());
    }
}
