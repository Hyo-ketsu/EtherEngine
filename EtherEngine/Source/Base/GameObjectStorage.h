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
        // �Q�[���I�u�W�F�N�g��ǉ�����
        // @ Ret  : �ǉ������Q�[���I�u�W�F�N�g�̃n���h��
        // @ Arg1 : �ǉ�����Q�[���I�u�W�F�N�g
        BaseHandle<GameObject> AddGameObject(GameObject& gameObject);
        // �S�ẴQ�[���I�u�W�F�N�g���擾����
        std::vector<BaseHandle<GameObject>> GetGameObjectAll(void);

    private:

        friend class Singleton<GameObjectStorage>;

        std::vector<BaseHandle<GameObject>> m_gameObject;   // �Q�[���I�u�W�F�N�g�̃n���h��
    };
}


#endif // !I_GAMEOBJECTSTORAGE_H
