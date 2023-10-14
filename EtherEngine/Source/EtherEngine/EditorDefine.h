#ifndef I_EDITORDEFINE_H
#define I_EDITORDEFINE_H
#include <Base/BaseInput.h>


namespace EtherEngine {
    // �G�f�B�^�[�萔��`
    namespace EditorDefine {
        const std::string EDITOR_DEFAULT_SCENE_NAME = "UndefineScene";  // �V�[�����J���Ă��Ȃ������ۂɂ���V�[����
    }


    // �G�f�B�^�[��Default�ݒ�
    namespace EditorDefaultConfig {
        const float EDITOR_CAMERA_SPEED = 0.025f;   // �G�f�B�^�[�̃J�����̏������x
    }


    // �G�f�B�^�[�̓��̓L�[
    namespace EditorKey {
        const KeyboardInput INPUT_DECISION = VK_RETURN; // ����L�[
        const KeyboardInput INPUT_CANCEL = VK_ESCAPE;   // �L�����Z���L�[
        
        const KeyboardInput INPUT_RENAME = VK_F2;   // ���l�[���L�[
    }


    // �G�f�B�^�[�̃t�@�C���\��
    namespace EditorFileDefine {
        const std::string EDITOR_SETTING = "EditorSetting"; // �G�f�B�^�[�ɂ��Ă̐ݒ��ێ����Ă���f�B���N�g��
        const std::string EDITOR_MIDDLE_DATA = "Object";    // �G�f�B�^�[�̒��ԃt�@�C��(�A�Z���u����v���W�F�N�g���̂̒��ԃt�@�C����)���i�[����Ă���f�B���N�g��
    }
}


#endif // !I_EDITORDEFINE_H
