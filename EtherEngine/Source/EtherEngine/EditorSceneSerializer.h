#ifndef I_EDITORSCENESERIALIZER_H
#define I_EDITORSCENESERIALIZER_H
#include <Base/BaseDefines.h>
#include <Base/PathClass.h>


//----- EditorSceneSerialize �錾
namespace EtherEngine {
    // ���݂̃V�[����Ԃ��o�͂���֐�
    // @ Arg1 : �o�͐�p�X
    // @ Arg2 : �o�̓V�[��
    void EditorSceneSerialize(const PathClass& path, const SceneType& sceneData);
}


#endif // !I_EDITORSCENESERIALIZER_H
