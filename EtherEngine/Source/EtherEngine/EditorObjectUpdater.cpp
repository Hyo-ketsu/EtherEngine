#include <EtherEngine/EditorObjectUpdater.h>
#include <EtherEngine/EditorObjectStorage.h>


namespace EtherEngine {
    // ゲームオブジェクトに更新処理を行う
    void EditorUpdater::Update(void) {
        auto update = EditorObjectStorage::Get()->GetGameObjectAll();
        for (auto&& it : update) {
            it.GetAtomicData().Update();
        }
    }

    // ゲームオブジェクトの描画処理を行う
    void EditorUpdater::Draw(void) {
        //----- IMGUI描画処理
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        //----- EditorObject描画
        auto draw = EditorObjectStorage::Get()->GetGameObjectAll();
        for (auto&& it : draw) {
            it.GetAtomicData().Draw();
        }

        ImGui::Render();
    }
}
