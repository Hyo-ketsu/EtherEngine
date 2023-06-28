#include <EtherEngine/EditorOutliner.h>
#include <EtherEngine/Test/imgui_demo.h>


namespace EtherEngine {
    // �R���X�g���N�^
    EditorOutliner::EditorOutliner(EditorObject* editorObject, const BaseHandle<DirectXRender>& directX) 
        : EditorComponentBase(editorObject) {
    }


    // �X�V����
    void EditorOutliner::Update(void) {

    }
    // �`�揈��
    void EditorOutliner::Draw(void) {
        bool hoge = true;
        ImGui::ShowDemoWindow(&hoge);

        ImGui::Begin("Hoge");
        ImGui::Text("Fuga");
        ImGui::End();
    }
}
