#ifndef I_COMPONENTHELPER_H
#define I_COMPONENTHELPER_H
#include <Base/GameObject.h>
#include <Base/ComponentBase.h>


//----- ComponentHelper�錾
namespace EtherEngine {
    // Component�̃w���p�[
    class ComponentHelper {
    public:
        ComponentHelper(void) = delete;


        // �R���|�[�l���g�̏����Q�[���I�u�W�F�N�g�擾
        // @ Ret  : �����Q�[���I�u�W�F�N�g
        // @ Arg1 : �����Q�[���I�u�W�F�N�g���擾�������R���|�[�l���g
        static GameObject* const GetGameObject(const ComponentBase& component);
        // �R���|�[�l���g�̏����Q�[���I�u�W�F�N�g�擾
        // @ Ret  : �����Q�[���I�u�W�F�N�g
        // @ Arg1 : �����Q�[���I�u�W�F�N�g���擾�������R���|�[�l���g
        static GameObject* const GetGameObject(const ComponentBase* const component);
    };
}


#endif // !I_COMPONENTHELPER_H
