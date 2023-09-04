#ifndef I_EDITORCAMERA_H
#define I_EDITORCAMERA_H
#include <Base/CameraBase.h>
#include <Base/BaseInput.h>
#include <EtherEngine/EditorComponentBase.h>
#include <EtherEngine/EditorObject.h>


//----- EditorCamera�錾
namespace EtherEngine {
    class EditorCamera : public CameraBase, public EditorComponentBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �G�f�B�^�[�I�u�W�F�N�g
        EditorCamera(EditorObject* editorObject);


        // �J�������x�Q�b�^�[
        float GetSpeed(void) const { return m_speed; }
        // �J�������x�Z�b�^�[
        void SetSpeed(const float& in) { m_speed = in; }


        // ����������
        void Start(void) override;
        // �X�V����
        void Update(void) override;

    private:
        float    m_speed;   // �J�����̈ړ����x
        KeyboardInput m_front;   // �O�i
        KeyboardInput m_back;    // ���
        KeyboardInput m_left;    // ���i
        KeyboardInput m_right;   // �E�i
        KeyboardInput m_up;      // �㏸
        KeyboardInput m_down;    // ���~
    };
}


#endif // !I_EDITORCAMERA_H
