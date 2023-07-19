#include <EtherEngine/EditorOutliner.h>
#include <Base/GameObjectStorage.h>
#ifdef _DEBUG
#include <Base/BaseInput.h>
#include <EtherEngine/Test/imgui_demo.h>
#endif // _DEBUG


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

        //----- �\��
        // @ MEMO : ���݂͐e�q�֌W����؍l�����Ă��܂���
        if (ImGui::BeginListBox("GameObjectList")) {
            int i = 0;
            for (auto&& it : gameObjects) {
                auto gameObject = it.GetNoAtomicItem();
                bool isSelect = ms_selectNumber == i;  // �I������Ă��邩
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


    // ���ݑI������Ă���Q�[���I�u�W�F�N�g��n��
    BaseHandle<GameObject> EditorOutliner::GetSelectGameObject(void) {
        return GameObjectStorage::Get()->GetGameObjectAll()[ms_selectNumber];
    }


    int EditorOutliner::ms_selectNumber = -1; // �I������Ă���ԍ�
}
