#ifndef I_GAMEOBJECTSTORAGE_H
#define I_GAMEOBJECTSTORAGE_H
#include <EngineLibrary/ManageSingleton.h>
#include <EngineLibrary/GameObject.h>


//----- GameObjectStorage �錾
namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g���Ǘ�����N���X
    public ref class GameObjectStorage {
        ETHER_ENGINE_MANAGE_SINGLETON(GameObjectStorage);
    public:
        // �Q�[���I�u�W�F�N�g��ǉ�����
        // @ Arg1 : �ǉ�����Q�[���I�u�W�F�N�g
        void AddGameObject(GameObject^ gameObject);
        // �Q�[���I�u�W�F�N�g���폜����
        // @ Arg1 : �폜����Q�[���I�u�W�F�N�g
        void DeleteGameObject(GameObject^ gameObject);
        // �Q�[���I�u�W�F�N�g���폜����
        // @ Arg1 : �폜����Q�[���I�u�W�F�N�g
        void DeleteGameObject(IDClass^ id);
        // �Q�[���I�u�W�F�N�g��S�폜����
        void DeleteAllGameObject(void);


        // �Q�[���I�u�W�F�N�g�̒ǉ��E�폜�o�[�W����
        property int UpdateGameObjectVersion {
            int get(void) { return m_updateVersion; }
        }


        // �S�ẴQ�[���I�u�W�F�N�g���擾����
        property System::Collections::Generic::List<GameObject^>^ GameObjects {
            System::Collections::Generic::List<GameObject^>^ get(void) { return m_gameObjects; }
        }


    private:
        System::Collections::Generic::List<GameObject^>^ m_gameObjects; // �ێ����Ă���Q�[���I�u�W�F�N�g�̈ꗗ
        int m_updateVersion;    // �Q�[���I�u�W�F�N�g�̒ǉ��E�폜�o�[�W����
    };

}


#endif // !I_GAMEOBJECTSTORAGE_H
