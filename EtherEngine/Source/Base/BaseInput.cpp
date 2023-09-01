#include <Base/BaseInput.h>


//----- 各入力用ボタン入力設定
namespace EtherEngine {
    // コンストラクタ
    KeyboardInput::KeyboardInput(const uchar& key)
        : BaseInput(key) {
    }
    XBoxInput::XBoxInput(const usint& button, const uint playerIndex)
        : BaseInput(button)
        , m_playerIndex(playerIndex) {
    }
}


//----- InputKey宣言
namespace EtherEngine {
    // コンストラクタ
    InputKey::InputKey(const KeyboardInput& keyboard, const XBoxInput& xbox) 
        : m_keyboard(keyboard)
        , m_xbox(xbox) {
    }
    // コンストラクタ
    InputKey::InputKey(const XBoxInput& xbox, const KeyboardInput& keyboard) 
        : InputKey(keyboard, xbox) {
    }
}


//----- InputSystem定義
namespace EtherEngine {
    // 初期化
    void InputSystem::Init(void) {
        ms_keyTable.fill(0);
        ms_oldKeyTable.fill(0);
    }
    // 終了処理
    void InputSystem::Uninit(void) {
    }
    // 更新処理
    void InputSystem::Update(void) {
        //----- キー入力の前フレームの情報の退避
        ms_oldKeyTable = ms_keyTable;

        //----- キー入力の最新情報取得
        GetKeyboardState(ms_keyTable.data());
    }


    std::array<uchar, 256> InputSystem::ms_keyTable;    // キーボード入力
    std::array<uchar, 256> InputSystem::ms_oldKeyTable; // 前フレームキーボード入力
    std::optional<Eigen::Matrix<long, 2, 1>> InputSystem::ms_mousePostion;    // マウス座標
}
