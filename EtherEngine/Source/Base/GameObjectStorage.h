#ifndef I_GAMEOBJECTSTORAGE_H
#define I_GAMEOBJECTSTORAGE_H
#include <Base/Singleton.h>
#include <Base/Handle.h>
#include <Base/GameObject.h>


// @ MEMO : Scene������͌��
//----- GameObejctStorage�錾
namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g���Ǘ�����N���X
    class GameObjectStorage : public Singleton<GameObjectStorage> {
    public:
        // ��̃Q�[���I�u�W�F�N�g���쐬����
        // @ Ret  : �쐬�����Q�[���I�u�W�F�N�g�̃n���h��
        // @ Arg1 : ���W(�f�t�H���g : ���W�E��]��0, �g�k��1)
        BaseHandle<GameObject> CreateEditorObject(const Transform& transform = Transform());
        // �Q�[���I�u�W�F�N�g���폜����
        // @ Ret  : �폜���ꂽ��
        // @ Arg1 : �폜����Q�[���I�u�W�F�N�g�̃n���h��
        bool DeleteGameObject(const BaseHandle<GameObject>& gameObject);


        // �S�ẴQ�[���I�u�W�F�N�g���擾����
        std::vector<BaseHandle<GameObject>> GetEditorObjectAll(void);


        // �폜�ς݂̃Q�[���I�u�W�F�N�g���폜����
        void DeleteGameObjectsDelete(void);

    private:
        friend class Singleton<GameObjectStorage>;

        std::vector<BaseHandle<GameObject>> m_gameObjects;   // �Q�[���I�u�W�F�N�g�̃n���h��
    };
}


#endif // !I_GAMEOBJECTSTORAGE_H
