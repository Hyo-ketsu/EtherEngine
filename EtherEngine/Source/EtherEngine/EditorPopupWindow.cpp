#include <EtherEngine/EditorPopupWindow.h>
#include <EtherEngine/EditorApplication.h>


//----- EditorPopupWindow 定義
namespace EtherEngine {
    // コンストラクタ
    EditorPopupWindow::EditorPopupWindow(EditorObject* editorObject, const std::string& name, const bool isCloseButton, const ImGuiWindowFlags& flag)
        : EditorWindowBase(editorObject, name, true, flag | ImGuiWindowFlags_NoCollapse, EditorWindowSizeType::AutoSizeFixed) 
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

            DrawLateWindow();

            //----- キャッシング
            auto gameObject = EditorComponentHelper::GetEditorObject(this);
            auto& transform = gameObject->AccessTransform();
            auto& position = transform.AccessPostion();

            //----- 変数宣言・座標取得
            RECT windowRect{};
            GetWindowRect(EditorApplication::Get()->GetHWND(), &windowRect);

            //----- 中央座標計算
            position.x() = windowRect.left + ((windowRect.right - windowRect.left) / 2);
            position.y() = windowRect.top + ((windowRect.bottom - windowRect.top) / 2);
            ImGui::SetWindowPos(ImVec2(position.x(), position.y()));
            ImGui::SetWindowFocus();

            ImGui::EndPopup();
        }
    }
}
