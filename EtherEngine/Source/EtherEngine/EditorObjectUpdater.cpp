#include <EtherEngine/EditorObjectUpdater.h>
#include <EtherEngine/EditorObjectStorage.h>


namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g�ɍX�V�������s��
    void EditorUpdater::Update(void) {
        auto update = EditorObjectStorage::Get()->GetGameObjectAll();
        for (auto&& it : update) {
            it.GetAtomicData().Update();
        }
    }

    // �Q�[���I�u�W�F�N�g�̕`�揈�����s��
    void EditorUpdater::Draw(void) {
        //----- IMGUI�`�揈��
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        //----- EditorObject�`��
        auto draw = EditorObjectStorage::Get()->GetGameObjectAll();
        for (auto&& it : draw) {
            it.GetAtomicData().Draw();
        }

        ImGui::Render();
    }
}
