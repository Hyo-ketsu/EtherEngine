#include <EtherEngine/EditorOutliner.h>
#include <Base/GameObjectStorage.h>
#include <EtherEngine/EditorInspectorWindow.h>


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

        //----- 右クリックメニュー入力
        if (ImGui::IsMouseReleased(1)) {
            ImGui::OpenPopup("Outliner Popup");
        }

        //----- 表示
        // @ MEMO : 現在は親子関係を一切考慮していません
        if (ImGui::BeginListBox("GameObjectList")) {
            int i = 0;
            for (auto&& it : gameObjects) {
                auto gameObject = it.GetNoAtomicItem();
                auto name = gameObject.GetData().GetName() + std::to_string(i);
                bool isSelect = (ms_selectNumber == i);  // 選択されているか
                if (ImGui::Selectable(name.c_str(), isSelect)) {
                    ms_selectNumber = i;
                    EditorInspectorWindow::SetInspectorShow(EditorInspectorObject(&it.GetNoAtomicData(), [=]() -> bool { return it.IsEnable(); }));
                }
                if (isSelect) {
                    ImGui::SetItemDefaultFocus();
                }

                i++;
            }

            ImGui::EndListBox();
        }

        //----- 右クリックメニュー表示
        if (ImGui::BeginPopup("Outliner Popup")) {
            //----- オブジェクト生成
            if (ImGui::MenuItem("CreateGameObejct")) {
                GameObjectStorage::Get()->CreateGameObject();
            }
            //----- オブジェクト削除
            if (ImGui::MenuItem("DeleteGameObject")) {
                if (ms_selectNumber > -1 && gameObjects.size() >= ms_selectNumber) {
                    GameObjectStorage::Get()->DeleteGameObject(gameObjects[ms_selectNumber]);
                }
            }

            //----- メニュー表示終了
            ImGui::EndPopup();
        }
    }


    // 現在選択されているゲームオブジェクトを渡す
    BaseHandle<GameObject> EditorOutliner::GetSelectGameObject(void) {
        return GameObjectStorage::Get()->GetGameObjectAll()[ms_selectNumber];
    }


    int EditorOutliner::ms_selectNumber = -1; // 選択されている番号
}
