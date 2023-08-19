#include <EtherEngine/EditorBuildMenuWindow.h>
#include <EtherEngine/EditorObjectStorage.h>


//----- BuildMenu 定義
namespace EtherEngine {
    // 更新
    void BuildMenu::Update(void) {

    }
    // 描画
    void BuildMenu::Draw(void) {
        //----- ウィンドウ描画
        ImGui::OpenPopup("Build Menu");
        DrawWindow();

        //----- 消されたのであれば削除する
        if (m_isOpen == false) EditorObjectStorage::Get()->DeleteEditorObject(EditorComponentHelper::GetEditorObject(this)->GetHandle());
    }
    // ウィンドウ描画
    void BuildMenu::DrawWindow(void) {
        if (ImGui::BeginPopupModal("Build Menu", &m_isOpen, ImGuiWindowFlags_MenuBar)) {


            ImGui::EndPopup();
        }
    }
}
