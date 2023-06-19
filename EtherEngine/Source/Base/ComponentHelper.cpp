#include <Base/ComponentHelper.h>


namespace EtherEngine {
    // �R���|�[�l���g�̏����Q�[���I�u�W�F�N�g�擾
    GameObject* const ComponentHelper::GetGameObject(const ComponentBase& component) {
        //----- �ϐ��錾
        void* ret = nullptr;
        component.GetGameObject(&ret);
        return static_cast<GameObject*>(ret);
    }
    // �R���|�[�l���g�̏����Q�[���I�u�W�F�N�g�擾
    GameObject* const ComponentHelper::GetGameObject(const ComponentBase* const component) {
        //----- �ϐ��錾
        void* ret = nullptr;
        component->GetGameObject(&ret);
        return static_cast<GameObject*>(ret);
    }
}
