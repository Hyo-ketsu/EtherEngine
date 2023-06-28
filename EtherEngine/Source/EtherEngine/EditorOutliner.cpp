#include <EtherEngine/EditorOutliner.h>
#include <EtherEngine/Test/imgui_demo.h>


namespace EtherEngine {
    // コンストラクタ
    EditorOutliner::EditorOutliner(EditorObject* editorObject, const BaseHandle<DirectXRender>& directX) 
        : EditorComponentBase(editorObject) {
    }


    // 更新処理
    void EditorOutliner::Update(void) {

    }
    // 描画処理
    void EditorOutliner::Draw(void) {
        bool hoge = true;
        ImGui::ShowDemoWindow(&hoge);

        ImGui::Begin("Hoge");
        ImGui::Text("Fuga");
        ImGui::End();
    }
}
