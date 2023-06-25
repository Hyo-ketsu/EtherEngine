#include <EtherEngine/EditorComponentHelper.h>


//----- EditorComponentHelper��`
namespace EtherEngine {
    // �R���|�[�l���g�̏����Q�[���I�u�W�F�N�g�擾
    EditorObject* const EditorComponentHelper::GetEditorObject(const EditorComponentBase& component) {
        void* ret = nullptr;
        component.GetEditorObject(&ret);
        return static_cast<EditorObject*>(ret);
    }
    // �R���|�[�l���g�̏����Q�[���I�u�W�F�N�g�擾
    EditorObject* const EditorComponentHelper::GetEditorObject(const EditorComponentBase* const component) {
        void* ret = nullptr;
        component->GetEditorObject(&ret);
        return static_cast<EditorObject*>(ret);
    }
}
