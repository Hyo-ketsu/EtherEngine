#include <EtherEngine/EditorBuildMenuWindow.h>
#include <EtherEngine/EditorObjectStorage.h>


//----- BuildMenu ��`
namespace EtherEngine {
    // �X�V
    void BuildMenu::Update(void) {

    }
    // �`��
    void BuildMenu::Draw(void) {
        //----- �E�B���h�E�`��
        ImGui::OpenPopup("Build Menu");
        DrawWindow();

        //----- �����ꂽ�̂ł���΍폜����
        if (m_isOpen == false) EditorObjectStorage::Get()->DeleteEditorObject(EditorComponentHelper::GetEditorObject(this)->GetHandle());
    }
    // �E�B���h�E�`��
    void BuildMenu::DrawWindow(void) {
        if (ImGui::BeginPopupModal("Build Menu", &m_isOpen, ImGuiWindowFlags_MenuBar)) {


            ImGui::EndPopup();
        }
    }
}
