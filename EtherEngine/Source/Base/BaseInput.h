#ifndef I_BASEINPUT_H
#define I_BASEINPUT_H
#include <Base/ConceptUtility.h>
// @ MEMO : �L�[�{�[�h���͓�������̂ŕ�������H


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
        XBoxInput(const usint& button = 0, const uint playerIndex = 0);
        // �f�X�g���N�^
        ~XBoxInput(void) override {}


        // �v���C���[�Q�b�^�[
        uint GetPlayerIndex(void) const { return m_playerIndex; }

    private:
        uint m_playerIndex;  // �ێ����Ă���v���C���[�ԍ�
    };
}


//----- AxisInput�錾
namespace EtherEngine {
    // @ MEMO : �������B��Ŏ���
}


//----- InputSystem �錾
namespace EtherEngine {
    // �L�[ or �{�^�����͂��Ǘ�����N���X
    // @ MEMO : �ЂƂ܂� Xbox �̓��͂͌��
    class InputSystem {
    public:
        // ������
        static void Init(void);
        // �I������
        static void Uninit(void);
        // �X�V����
        static void Update(void);


        // �w��L�[�E�{�^����������Ă��邩
        // @ Ret  : ������Ă��邩
        // @ Arg1 : ���肷��L�[�E�{�^��
        template <typename Input>
            requires Concept::SameConcept<Input, KeyboardInput> || Concept::SameConcept<Input, XBoxInput>
        static bool IsPress(const Input& input);
        // �w��L�[�E�{�^���������ꂽ�u�Ԃ�
        // @ Ret  : �����ꂽ�u�Ԃ�
        // @ Arg1 : ���肷��L�[�E�{�^��
        template <typename Input>
            requires Concept::SameConcept<Input, KeyboardInput> || Concept::SameConcept<Input, XBoxInput>
        static bool IsTrigger(const Input& input);


        // @ MEMO : ��Platform�Ή����l�����Ă��Ȃ��̂łЂƂ܂�std::optional���g�p
        // �}�E�X���W�Q�b�^�[
        static std::optional<Eigen::Matrix<long, 2, 1>> GetMousePostion(void) { return ms_mousePostion; }
        // �}�E�X���W�Z�b�^�[
        static void SetMousePostion(const Eigen::Matrix<long, 2, 1>& in) { ms_mousePostion = in; }


    private:
        static std::array<uchar, 256> ms_keyTable;    // �L�[�{�[�h����
        static std::array<uchar, 256> ms_oldKeyTable; // �O�t���[���L�[�{�[�h����
        static std::optional<Eigen::Matrix<long, 2, 1>> ms_mousePostion;    // �}�E�X���W
    };
}




//----- InputSystem ��`
namespace EtherEngine {
    // �w��L�[�E�{�^����������Ă��邩
    template <typename Input>
        requires Concept::SameConcept<Input, KeyboardInput> || Concept::SameConcept<Input, XBoxInput>
    bool InputSystem::IsPress(const Input& input) {
        if constexpr (Concept::SameConcept<Input, KeyboardInput>) {
            //----- �L�[�{�[�h����
            return ms_keyTable.at(input.GetKeyboard().GetInput()) & 0x80;
        }
        if constexpr (Concept::SameConcept<Input, XBoxInput>) {
            static_cast(false, "Not yet implemented");
        }
    }
    // �w��L�[�E�{�^���������ꂽ�u�Ԃ�
    template <typename Input>
        requires Concept::SameConcept<Input, KeyboardInput> || Concept::SameConcept<Input, XBoxInput>
    bool InputSystem::IsTrigger(const Input& input) {
        if constexpr (Concept::SameConcept<Input, KeyboardInput>) {
            //----- �L�[�{�[�h����
            bool isOld = ms_oldKeyTable.at(input.GetKeyboard().GetInput()) & 0x80;
            bool isNew = ms_keyTable.at(input.GetKeyboard().GetInput()) & 0x80;

            //----- �ԋp
            return (isOld == false) && (isNew == true) ? true : false;
        }
        if constexpr (Concept::SameConcept<Input, XBoxInput>) {
            static_cast(false, "Not yet implemented");
        }
    }
}


#endif // !I_BASEINPUT_H
