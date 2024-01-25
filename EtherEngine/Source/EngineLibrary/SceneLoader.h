#ifndef I_SCENELOADER_H
#define I_SCENELOADER_H
#include <Base/BaseDefines.h>
#include <EngineLibrary/ManageSingleton.h>
#include <EngineLibrary/Scene.h>


// @ MEMO : �z�肷��Json�̍��
// "�Q�[���I�u�W�F�N�g��" : {
//     "ID" : "�Ȃ񂿂��"
//     "Component" :  {
//         "PlayerComponent" : {
//              // �ȉ��R���|�[�l���g�̃f�[�^
//          }
//     }
// }


//----- SceneLoader ��`
namespace EtherEngine {
    public ref class SceneLoader {
        ETHER_ENGINE_MANAGE_SINGLETON(SceneLoader);
    public:
        // �V�[����ǉ�����
        // @ Arg1 : �ǉ�����V�[��
        void AddScene(Scene^ addScene);
        // �V�[�����폜����
        // @ Genr : �폜����V�[��
        generic <typename SceneType> where SceneType : Scene
        void DeleteScene(void);
        // �V�[����S�č폜����
        void DeleteAllScene(void);
        // �V�[�����ړ�����
        // @ Memo : �S�č폜��A�V�[����ǉ�����`�ł�
        // @ Genr : �ǉ�����V�[��
        generic <typename SceneType> where SceneType : Scene
        void MoveScene(void);


        // �w��V�[�����擾����
        // @ Genr : �擾����V�[��
        generic <typename SceneType> where SceneType : Scene
        Scene^ GetScene(void);
        // �S�ẴV�[�����擾����
        // @ Ret  : �擾�������ׂẴV�[��
        System::Collections::Generic::List<Scene^>^ GetAllScene(void);

    private:
        System::Collections::Generic::List<Scene^>^ m_thisScenes;
    };
}


#endif // !I_SCENELOADER_H
