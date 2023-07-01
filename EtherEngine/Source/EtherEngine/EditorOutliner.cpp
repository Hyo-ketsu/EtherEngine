#include <EtherEngine/EditorOutliner.h>
#include <Base/GameObjectStorage.h>
#ifdef _DEBUG
#include <Base/BaseInput.h>
#include <EtherEngine/Test/imgui_demo.h>
#endif // _DEBUG


namespace EtherEngine {
    // �X�V����
    void EditorOutliner::Update(void) {

    }
    // �`�揈��
    void EditorOutliner::DrawWindow(void) {
        //----- �S�Q�[���I�u�W�F�N�g�擾
        auto gameObjects = GameObjectStorage::Get()->GetEditorObjectAll();

        ImGui::ShowDemoWindow();
        ImGui::Begin("hoge");
        if (InputSystem::GetMousePostion().has_value()) {
            ImGui::Text("%d %d", InputSystem::GetMousePostion().value().x(), InputSystem::GetMousePostion().value().y());
        }
        ImGui::End();

        //----- �\��
        // @ MEMO : ���݂͐e�q�֌W����؍l�����Ă��܂���
        for (auto&& it : gameObjects) {
            auto gameObject = it.GetNoAtomicItem();
            ImGui::Text(gameObject.GetData().GetName().c_str());
        }
    }
}
