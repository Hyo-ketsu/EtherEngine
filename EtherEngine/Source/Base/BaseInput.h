#ifndef I_BASEINPUT_H
#define I_BASEINPUT_H
#include <Base/ConceptUtility.h>


//----- �e���͗p�{�^�����͐ݒ�
namespace EtherEngine {
    // �e�v���b�g�t�H�[���p����
    template <std::integral InputType>
    class BaseInput {
    public:
        // ���͏��Q�b�^�[
        InputType GetInput(void) const { return m_input; }
        // ���͏����擾����
        operator InputType(void) const { return GetInput(); }
        // ���͐ݒ肪����Ă��邩
        virtual operator bool(void) const { return m_input == 0; }

    protected:
        // �R���X�g���N�^
        // @ Arg1 : ����
        BaseInput(const InputType& input) : m_input(input) {}
        // �f�X�g���N�^
        virtual ~BaseInput(void) {}

    private:
        InputType m_input;  // ����
    };


    // Keyboard����
    class KeyboardInput : public BaseInput<uchar> {
    public:
        // �R���X�g���N�^
        // @ Arg1 : ���̓L�[(Default : 0(�����ݒ肵�Ȃ�))
        // @ Arg2 : 
        KeyboardInput(const uchar& key = 0);
        // �f�X�g���N�^
        ~KeyboardInput(void) override {}
    };
    // xbox����
    class XBoxInput : public BaseInput<usint> {
    public:
        // �R���X�g���N�^
        // @ Arg1 : ���̓{�^��(Default : 0(�����ݒ肵�Ȃ�))
        // @ Arg2 : �ݒ�v���C���[(Default : 0)
        XBoxInput(const usint& button = 0, const uint playerIndex);
        // �f�X�g���N�^
        ~XBoxInput(void) override {}


        // �v���C���[�Q�b�^�[
        uint GetPlayerIndex(void) const { return m_playerIndex; }

    private:
        uint m_playerIndex;  // �ێ����Ă���v���C���[�ԍ�
    };
}

//----- InputKey�錾
namespace EtherEngine {
    // �L�[�{�[�h��R���g���[���[�̓��͂�ێ�����N���X
    class InputKey {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �L�[�{�[�h����
        // @ Arg2 : �R���g���[������(Default : �Ȃ�)
        InputKey(const KeyboardInput& keyboard, const XBoxInput& xbox = XBoxInput());
        // �R���X�g���N�^
        // @ Arg1 : �R���g���[������
        // @ Arg2 : �L�[�{�[�h����(Default : �Ȃ�)
        InputKey(const XBoxInput& xbox, const KeyboardInput& keyboard = KeyboardInput());


        // Keyboard���̓Q�b�^�[
        const KeyboardInput& GetKeyboard(void) const { return m_keyboard; }
        // Keyboard���̓Z�b�^�[
        void SetKeyboard(const KeyboardInput& in) { m_keyboard = in; }

        // XBox���̓Q�b�^�[
        const XBoxInput& GetXBox(void) const { return m_xbox; }
        // XBox���̓Z�b�^�[
        void SetXBox(const XBoxInput& in) { m_xbox = in; }

    private:
        KeyboardInput m_keyboard;   // �L�[�{�[�h���̓L�[
        XBoxInput m_xbox;       // Xbox�R���g���[���{�^��
    };
}


//----- AxisInput�錾
namespace EtherEngine {
    // @ MEMO : �������B��Ŏ���
}


//----- InputSystem�錾
namespace EtherEngine {
    // �L�[ or �{�^�����͂��Ǘ�����N���X
    class InputSystem {
    public:
        // �w��L�[�E�{�^����������Ă��邩
        // @ Ret  : ������Ă��邩
        // @ Arg1 : ���肷��L�[�E�{�^��
        static bool IsPress(const InputKey& input);
        // �w��L�[�E�{�^���������ꂽ�u�Ԃ�
        // @ Ret  : �����ꂽ�u�Ԃ�
        // @ Arg1 : ���肷��L�[�E�{�^��
        static bool IsTrigger(const InputKey& input);
    };
}


#endif // !I_BASEINPUT_H
