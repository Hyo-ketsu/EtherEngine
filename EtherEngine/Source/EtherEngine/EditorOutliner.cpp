#include <EtherEngine/EditorOutliner.h>
#include <Base/GameObjectStorage.h>
#ifdef _DEBUG
#include <Base/BaseInput.h>
#include <EtherEngine/Test/imgui_demo.h>
#endif // _DEBUG


namespace EtherEngine {
    // 初期化処理
    void EditorOutliner::Start(void) {
        AccessFlags() |= ImGuiWindowFlags_NoCollapse;
    }
    // 更新処理
    void EditorOutliner::Update(void) {

    }
    // 描画処理
    void EditorOutliner::DrawWindow(void) {
        //----- 全ゲームオブジェクト取得
        auto gameObjects = GameObjectStorage::Get()->GetGameObjectAll();

        //----- 表示
        // @ MEMO : 現在は親子関係を一切考慮していません
        if (ImGui::BeginListBox("GameObjectList")) {
            int i = 0;
            for (auto&& it : gameObjects) {
                auto gameObject = it.GetNoAtomicItem();
                bool isSelect = ms_selectNumber == i;  // 選択されているか
                if (ImGui::Selectable(gameObject.GetData().GetName().c_str(), &isSelect)) {
                    ms_selectNumber = i;
                }
                if (isSelect) {
                    ImGui::SetItemDefaultFocus();
                }

                i++;
            }

            ImGui::EndListBox();
        }
    }


    // 現在選択されているゲームオブジェクトを渡す
    BaseHandle<GameObject> EditorOutliner::GetSelectGameObject(void) {
        return GameObjectStorage::Get()->GetGameObjectAll()[ms_selectNumber];
    }


    int EditorOutliner::ms_selectNumber = -1; // 選択されている番号
}
