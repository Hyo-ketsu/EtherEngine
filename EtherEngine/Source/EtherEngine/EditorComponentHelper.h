#ifndef I_EDITORCOMPONENTHELPER_H
#define I_EDITORCOMPONENTHELPER_H
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorComponentBase.h>


namespace EtherEngine {
    // EditorComponent�̃w���p�[
    namespace EditorComponentHelper {
        // �R���|�[�l���g�̏����Q�[���I�u�W�F�N�g�擾
        // @ Ret  : �����Q�[���I�u�W�F�N�g
        // @ Arg1 : �����Q�[���I�u�W�F�N�g���擾�������R���|�[�l���g
        EditorObject* const GetEditorObject(const EditorComponentBase& component);
        // �R���|�[�l���g�̏����Q�[���I�u�W�F�N�g�擾
        // @ Ret  : �����Q�[���I�u�W�F�N�g
        // @ Arg1 : �����Q�[���I�u�W�F�N�g���擾�������R���|�[�l���g
        EditorObject* const GetEditorObject(const EditorComponentBase* const component);
    };
}


#endif // !I_EDITORCOMPONENTHELPER_H
