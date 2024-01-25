#include <EngineLibrary/SceneLoader.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/GameObjectStorage.h>
#include <Base/NativeGameObjectStorage.h>
#include <Base/NativeGameObjectUpdater.h>


//----- SceneLoader ��`
namespace EtherEngine {
    // �V�[����ǉ�����
    void SceneLoader::AddScene(Scene^ addScene) {
        using namespace System::Text::Json;

        //----- �܂��V�[����ǉ�
        m_thisScenes->Add(addScene);

        //----- �V�[���Ɋ�Â��ăQ�[���I�u�W�F�N�g�𐶐�����
        // @ MEMO : ���쒆
        // @ MEMO : ���쒆
        // @ MEMO : ���쒆
        auto sceneJson = addScene->GetScene();
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
    generic <typename SceneType>
    void SceneLoader::MoveScene(void) {
        DeleteAllScene();
        AddScene<SceneType>();
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
