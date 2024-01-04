#ifndef I_GAMEOBJECTSTORAGE_H
#define I_GAMEOBJECTSTORAGE_H
#include <Base/Singleton.h>
#include <Base/Handle.h>
#include <Base/NativeGameObject.h>


// @ MEMO : Scene������͌��
//----- GameObejctStorage�錾
namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g���Ǘ�����N���X
    class NativeGameObjectStorage : public Singleton<NativeGameObjectStorage> {
    public:
        // ��̃Q�[���I�u�W�F�N�g���쐬����
        // @ Ret  : �쐬�����Q�[���I�u�W�F�N�g�̃n���h��
        // @ Arg1 : ���W(�f�t�H���g : ���W�E��]��0, �g�k��1)
        // @ Arg2 : ���O(Default : NativeGameObject)
        Handle<NativeGameObject> CreateGameObject(const Transform& transform = Transform(), const std::string& name = "GameObject");
        // �Q�[���I�u�W�F�N�g���폜����
        // @ Ret  : �폜���ꂽ��
        // @ Arg1 : �폜����Q�[���I�u�W�F�N�g�̃n���h��
        bool DeleteGameObject(const Handle<NativeGameObject>& gameObject);


        // �S�ẴQ�[���I�u�W�F�N�g���擾����
        std::vector<Handle<NativeGameObject>> GetGameObjectAll(void) const;


        // �폜�ς݂̃Q�[���I�u�W�F�N�g���폜����
        void DeleteGameObjectsDelete(void);

    private:
        friend class Singleton<NativeGameObjectStorage>;

        std::vector<Handle<NativeGameObject>> m_gameObjects;   // �Q�[���I�u�W�F�N�g�̃n���h��
    };
}


#endif // !I_GAMEOBJECTSTORAGE_H