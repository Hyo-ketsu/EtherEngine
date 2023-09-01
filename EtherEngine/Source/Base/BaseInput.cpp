#include <Base/BaseInput.h>


//----- �e���͗p�{�^�����͐ݒ�
namespace EtherEngine {
    // �R���X�g���N�^
    KeyboardInput::KeyboardInput(const uchar& key)
        : BaseInput(key) {
    }
    XBoxInput::XBoxInput(const usint& button, const uint playerIndex)
        : BaseInput(button)
        , m_playerIndex(playerIndex) {
    }
}


//----- InputKey�錾
namespace EtherEngine {
    // �R���X�g���N�^
    InputKey::InputKey(const KeyboardInput& keyboard, const XBoxInput& xbox) 
        : m_keyboard(keyboard)
        , m_xbox(xbox) {
    }
    // �R���X�g���N�^
    InputKey::InputKey(const XBoxInput& xbox, const KeyboardInput& keyboard) 
        : InputKey(keyboard, xbox) {
    }
}


//----- InputSystem��`
namespace EtherEngine {
    // ������
    void InputSystem::Init(void) {
        ms_keyTable.fill(0);
        ms_oldKeyTable.fill(0);
    }
    // �I������
    void InputSystem::Uninit(void) {
    }
    // �X�V����
    void InputSystem::Update(void) {
        //----- �L�[���͂̑O�t���[���̏��̑ޔ�
        ms_oldKeyTable = ms_keyTable;

        //----- �L�[���͂̍ŐV���擾
        GetKeyboardState(ms_keyTable.data());
    }


    std::array<uchar, 256> InputSystem::ms_keyTable;    // �L�[�{�[�h����
    std::array<uchar, 256> InputSystem::ms_oldKeyTable; // �O�t���[���L�[�{�[�h����
    std::optional<Eigen::Matrix<long, 2, 1>> InputSystem::ms_mousePostion;    // �}�E�X���W
}
