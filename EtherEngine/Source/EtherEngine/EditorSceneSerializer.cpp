#include <EtherEngine/EditorSceneSerializer.h>
#include <Base/GameObjectStorage.h>


//----- EditorSceneSerialize ��`
namespace EtherEngine {
    // ���݂̃V�[����Ԃ��o�͂���֐�
    void EditorSceneSerialize(const PathClass& path, const SceneData& sceneData) {
        //----- �ϐ��錾
        nlohmann::json json;
        std::ofstream scene;

        //----- ��ɐV�K�쐬����
        scene.open(path, std::ios::out);

        //----- �V�[�����o��
        json["SceneName"] = sceneData;

        //----- �Q�[���I�u�W�F�N�g�擾�E�V�[���ʐU�蕪��
        auto gameObjects = GameObjectStorage::Get()->GetGameObjectAll();
        decltype(gameObjects) sceneObject;
        for (auto& it : gameObjects) {
            if (it.GetNoAtomicData().GetScene() == sceneData) {
                sceneObject.push_back(it);
            }
        }

        //----- �Q�[���I�u�W�F�N�g�o��
        for (auto& it : sceneObject) {
            json["GameObjects"] = it.GetAtomicData().Output();
        }
    }
}
