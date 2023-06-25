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
        auto draw = EditorObjectStorage::Get()->GetGameObjectAll();
        for (auto&& it : draw) {
            it.GetAtomicData().Draw();
        }
    }
}
