#include <EtherEngine/EditorOutliner.h>
#include <Base/GameObjectStorage.h>
#include <EtherEngine/EditorInspectorWindow.h>


namespace EtherEngine {
    // ����������
    void EditorOutliner::Start(void) {
        AccessFlags() |= ImGuiWindowFlags_NoCollapse;
    }
    // �X�V����
    void EditorOutliner::Update(void) {

    }
    // �`�揈��
    void EditorOutliner::DrawWindow(void) {
        //----- �S�Q�[���I�u�W�F�N�g�擾
        auto gameObjects = GameObjectStorage::Get()->GetGameObjectAll();

        //----- �E�N���b�N���j���[����
        if (ImGui::IsMouseReleased(1)) {
            ImGui::OpenPopup("Outliner Popup");
        }

        //----- �\��
        // @ MEMO : ���݂͐e�q�֌W����؍l�����Ă��܂���
        if (ImGui::BeginListBox("GameObjectList")) {
            int i = 0;
            for (auto&& it : gameObjects) {
                auto gameObject = it.GetNoAtomicItem();
                auto name = gameObject.GetData().GetName() + std::to_string(i);
                bool isSelect = (ms_selectNumber == i);  // �I������Ă��邩
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

        //----- �E�N���b�N���j���[�\��
        if (ImGui::BeginPopup("Outliner Popup")) {
            //----- �I�u�W�F�N�g����
            if (ImGui::MenuItem("CreateGameObejct")) {
                GameObjectStorage::Get()->CreateGameObject();
            }
            //----- �I�u�W�F�N�g�폜
            if (ImGui::MenuItem("DeleteGameObject")) {
                if (ms_selectNumber > -1 && gameObjects.size() >= ms_selectNumber) {
                    GameObjectStorage::Get()->DeleteGameObject(gameObjects[ms_selectNumber]);
                }
            }

            //----- ���j���[�\���I��
            ImGui::EndPopup();
        }
    }


    // ���ݑI������Ă���Q�[���I�u�W�F�N�g��n��
    BaseHandle<GameObject> EditorOutliner::GetSelectGameObject(void) {
        return GameObjectStorage::Get()->GetGameObjectAll()[ms_selectNumber];
    }


    int EditorOutliner::ms_selectNumber = -1; // �I������Ă���ԍ�
}
