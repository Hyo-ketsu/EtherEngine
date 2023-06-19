#ifndef I_BASEINPUT_H
#define I_BASEINPUT_H
#include <Base/ConceptUtility.h>


//----- 各入力用ボタン入力設定
namespace EtherEngine {
    // 各プラットフォーム用入力
    template <std::integral InputType>
    class BaseInput {
    public:
        // 入力情報ゲッター
        InputType GetInput(void) const { return m_input; }
        // 入力情報を取得する
        operator InputType(void) const { return GetInput(); }
        // 入力設定がされているか
        virtual operator bool(void) const { return m_input == 0; }

    protected:
        // コンストラクタ
        // @ Arg1 : 入力
        BaseInput(const InputType& input) : m_input(input) {}
        // デストラクタ
        virtual ~BaseInput(void) {}

    private:
        InputType m_input;  // 入力
    };


    // Keyboard入力
    class KeyboardInput : public BaseInput<uchar> {
    public:
        // コンストラクタ
        // @ Arg1 : 入力キー(Default : 0(何も設定しない))
        // @ Arg2 : 
        KeyboardInput(const uchar& key = 0);
        // デストラクタ
        ~KeyboardInput(void) override {}
    };
    // xbox入力
    class XBoxInput : public BaseInput<usint> {
    public:
        // コンストラクタ
        // @ Arg1 : 入力ボタン(Default : 0(何も設定しない))
        // @ Arg2 : 設定プレイヤー(Default : 0)
        XBoxInput(const usint& button = 0, const uint playerIndex);
        // デストラクタ
        ~XBoxInput(void) override {}


        // プレイヤーゲッター
        uint GetPlayerIndex(void) const { return m_playerIndex; }

    private:
        uint m_playerIndex;  // 保持しているプレイヤー番号
    };
}

//----- InputKey宣言
namespace EtherEngine {
    // キーボードやコントローラーの入力を保持するクラス
    class InputKey {
    public:
        // コンストラクタ
        // @ Arg1 : キーボード入力
        // @ Arg2 : コントローラ入力(Default : なし)
        InputKey(const KeyboardInput& keyboard, const XBoxInput& xbox = XBoxInput());
        // コンストラクタ
        // @ Arg1 : コントローラ入力
        // @ Arg2 : キーボード入力(Default : なし)
        InputKey(const XBoxInput& xbox, const KeyboardInput& keyboard = KeyboardInput());


        // Keyboard入力ゲッター
        const KeyboardInput& GetKeyboard(void) const { return m_keyboard; }
        // Keyboard入力セッター
        void SetKeyboard(const KeyboardInput& in) { m_keyboard = in; }

        // XBox入力ゲッター
        const XBoxInput& GetXBox(void) const { return m_xbox; }
        // XBox入力セッター
        void SetXBox(const XBoxInput& in) { m_xbox = in; }

    private:
        KeyboardInput m_keyboard;   // キーボード入力キー
        XBoxInput m_xbox;       // Xboxコントローラボタン
    };
}


//----- AxisInput宣言
namespace EtherEngine {
    // @ MEMO : 未実装。後で実装
}


//----- InputSystem宣言
namespace EtherEngine {
    // キー or ボタン入力を管理するクラス
    class InputSystem {
    public:
        // 指定キー・ボタンが押されているか
        // @ Ret  : 押されているか
        // @ Arg1 : 判定するキー・ボタン
        static bool IsPress(const InputKey& input);
        // 指定キー・ボタンが押された瞬間か
        // @ Ret  : 押された瞬間か
        // @ Arg1 : 判定するキー・ボタン
        static bool IsTrigger(const InputKey& input);
    };
}


#endif // !I_BASEINPUT_H
