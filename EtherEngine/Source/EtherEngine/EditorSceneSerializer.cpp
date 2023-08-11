#include <EtherEngine/EditorSceneSerializer.h>
#include <Base/BaseDefines.h>
#include <Base/GameObjectStorage.h>


//----- EditorSceneSerialize ��`
namespace EtherEngine {
    // ���݂̃V�[����Ԃ��o�͂���֐�
    void EditorSceneSerialize(const PathClass& path, const SceneData& sceneData) {
        //----- �ϐ��錾
        nlohmann::json json;
        std::ofstream scene;

        //----- ��ɐV�K�쐬����
        (path /= sceneData).GetDirectory().CreateDirectories();
        scene.open(path /= std::string(sceneData) += FileDefine::SCENE, std::ios::out);

        //----- �V�[�����o��
        json["SceneName"] = sceneData.c_str();

        //----- �Q�[���I�u�W�F�N�g�擾�E�V�[���ʐU�蕪��
        auto gameObjects = GameObjectStorage::Get()->GetGameObjectAll();
        decltype(gameObjects) sceneObject;
        for (auto& it : gameObjects) {
            if (it.GetNoAtomicData().GetScene() == sceneData) {
                sceneObject.push_back(it);
            }
        }

        //----- �Q�[���I�u�W�F�N�g�o��
        nlohmann::json gameObjectArray;
        for (auto& it : sceneObject) {
            gameObjectArray.push_back(it.GetAtomicData().Output());
        }
        auto fuga = gameObjectArray.dump(4);
        json["GameObjects"] = gameObjectArray;
        auto hoge = json.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES);
        scene << hoge;
    }
}
