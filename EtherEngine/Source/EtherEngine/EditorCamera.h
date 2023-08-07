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
        InputKey m_front;   // �O�i
        InputKey m_back;    // ���
        InputKey m_left;    // ���i
        InputKey m_right;   // �E�i
        InputKey m_up;      // �㏸
        InputKey m_down;    // ���~
    };
}


#endif // !I_EDITORCAMERA_H
