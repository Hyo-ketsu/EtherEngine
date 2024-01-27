#include <EngineLibrary/SceneLoader.h>
#include <Base/NativeGameObjectStorage.h>
#include <Base/NativeGameObjectUpdater.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/GameObjectStorage.h>
#include <EngineLibrary/ClassLoader.h>


//----- SceneLoader ��`
namespace EtherEngine {
    // �R���X�g���N�^
    SceneLoader::SceneLoader(void) 
        : m_thisScenes(gcnew System::Collections::Generic::List<Scene^>(1)) {
    }


    // �V�[����ǉ�����
    void SceneLoader::AddScene(Scene^ addScene) {
        using namespace Newtonsoft::Json;
        using namespace Newtonsoft::Json::Linq;

        //----- �܂��V�[����ǉ�
        m_thisScenes->Add(addScene);

        //----- �ϐ��錾
        System::String^ sceneData = addScene->GetScene();

        //----- �����O�Ƀ`�F�b�N
        if (sceneData == System::String::Empty) return; // �����������Ȃ��B

        //----- �V�[���Ɋ�Â��ăQ�[���I�u�W�F�N�g�𐶐�����
        auto sceneJson = JObject::Parse(addScene->GetScene());
        for each (auto gameObject in sceneJson) {
            ClassLoader::Input(gameObject.Value->ToString(), gcnew GameObject());   // @ Memo : gameObject�̃G���[�͖������ĉ������c�c����Ƀr���h�ł��܂�
        }
    }
    // �V�[�����폜����
    generic <typename SceneType>
    void SceneLoader::DeleteScene(void) {
        for (int i = 0; i < m_thisScenes->Count; i++) {
            auto scene = EditorUtility::ListGet(m_thisScenes, i);
            if (scene->GetType() == SceneType::typeid) {
                NativeGameObjectStorage::Get()->DeleteGameObject(scene->GetSceneID());
                m_thisScenes->RemoveAt(i);
            }
        }
    }
    // �V�[����S�č폜����
    void SceneLoader::DeleteAllScene(void) {
        for each (auto it in m_thisScenes) {
            NativeGameObjectStorage::Get()->DeleteGameObject(it->GetSceneID());
        }
        m_thisScenes->Clear();
    }
    // �V�[�����ړ�����
    void SceneLoader::MoveScene(Scene^ moveScene) {
        DeleteAllScene();
        AddScene(moveScene);
    }


    // �w��V�[�����擾����
    generic <typename SceneType>
    Scene^ SceneLoader::GetScene(void) {
        for (int i = 0; i < m_thisScenes->Count; i++) {
            auto scene = EditorUtility::ListGet(m_thisScenes, i);
            if (scene->GetType() == SceneType::typeid) {
                return scene;
            }
        }
    }
    // �S�ẴV�[�����擾����
    System::Collections::Generic::List<Scene^>^ SceneLoader::GetAllScene(void) {
        return m_thisScenes;
    }
}
