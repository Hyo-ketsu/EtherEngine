#include <Base/ComponentHelper.h>


namespace EtherEngine {
    // �R���|�[�l���g�̏����Q�[���I�u�W�F�N�g�擾
    NativeGameObject* const ComponentHelper::GetParentObject(const ComponentBase& component) {
        //----- �ϐ��錾
        void* ret = nullptr;
        component.GetParentObject(&ret);
        return static_cast<NativeGameObject*>(ret);
    }
    // �R���|�[�l���g�̏����Q�[���I�u�W�F�N�g�擾
    NativeGameObject* const ComponentHelper::GetParentObject(const ComponentBase* const component) {
        //----- �ϐ��錾
        void* ret = nullptr;
        component->GetParentObject(&ret);
        return static_cast<NativeGameObject*>(ret);
    }
}
