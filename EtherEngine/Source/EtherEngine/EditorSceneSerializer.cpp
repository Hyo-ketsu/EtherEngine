#include <EtherEngine/EditorSceneSerializer.h>
#include <Base/BaseDefines.h>
#include <Base/BaseUtility.h>
#include <Base/NativeGameObjectStorage.h>


//----- EditorSceneSerialize ��`
namespace EtherEngine {
    // ���݂̃V�[����Ԃ��o�͂���֐�
    void EditorSceneSerialize(const PathClass& path, const SceneType& sceneData) {
        ////----- �ϐ��錾
        //nlohmann::json json;
        //std::ofstream scene;

        ////----- �p�X��`
        //(path / sceneData).GetDirectory().Create_Directorie(); // �f�B���N�g���쐬
        //auto fileName = PathClass(sceneData).HasExtension() ?
        //    path / std::string(sceneData) :
        //    path / std::string(sceneData) += FileDefine::Extended::SCENE;

        ////----- �t�@�C���̐V�K�쐬
        //scene.open(fileName, std::ios::out);

        ////----- �V�[�����o��
        //json["SceneName"] = Utility::StringSubstitution(sceneData, "\\", "/");

        ////----- �Q�[���I�u�W�F�N�g�擾�E�V�[���ʐU�蕪��
        //auto gameObjects = GameObjectStorage::Get()->GetGameObjectAll();
        //decltype(gameObjects) sceneObject;
        //for (auto& it : gameObjects) {
        //    if (it.GetData().GetScene() == sceneData) {
        //        sceneObject.push_back(it);
        //    }
        //}

        ////----- �Q�[���I�u�W�F�N�g�o��
        //for (auto& it : sceneObject) {
        //    json["GameObjects"] += it.GetAtomicData().Output();
        //}

        ////----- ������o��
        //auto data = json.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES);
        //scene << data;
    }
}
