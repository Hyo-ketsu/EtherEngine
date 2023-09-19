#include <EtherEngine/EditorPopupWindow.h>


//----- EditorPopupWindow 定義
namespace EtherEngine {
    // コンストラクタ
    EditorPopupWindow::EditorPopupWindow(EditorObject* editorObject, const std::string& name, const bool isCloseButton, const ImGuiBackendFlags& flag)
        : EditorWindowBase(editorObject, name, flag) 
        , m_isCloseButton(isCloseButton) {
    }

    void EditorPopupWindow::UpdateWindow(void) {

    }
    void EditorPopupWindow::Draw(void) {
        ImGui::OpenPopup(m_name.c_str());

        //----- xボタン表示可否
        bool* isOpen = m_isCloseButton ? &m_isOpen : nullptr;

        //----- ウィンドウ描画
        if (ImGui::BeginPopupModal(m_name.c_str(), isOpen, m_flags)) {
            DrawWindow();
            ImGui::EndPopup();
        }

        //----- 消されたのであれば削除する
        if (m_isOpen == false) EditorObjectStorage::Get()->DeleteEditorObject(EditorComponentHelper::GetEditorObject(this)->GetHandle());
    }
}
