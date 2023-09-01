#ifndef I_BASEINPUT_H
#define I_BASEINPUT_H
#include <Base/ConceptUtility.h>
// @ MEMO : キーボード入力等があるので分離する？


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
        XBoxInput(const usint& button = 0, const uint playerIndex = 0);
        // デストラクタ
        ~XBoxInput(void) override {}


        // プレイヤーゲッター
        uint GetPlayerIndex(void) const { return m_playerIndex; }

    private:
        uint m_playerIndex;  // 保持しているプレイヤー番号
    };
}


//----- AxisInput宣言
namespace EtherEngine {
    // @ MEMO : 未実装。後で実装
}


//----- InputSystem 宣言
namespace EtherEngine {
    // キー or ボタン入力を管理するクラス
    // @ MEMO : ひとまず Xbox の入力は後回し
    class InputSystem {
    public:
        // 初期化
        static void Init(void);
        // 終了処理
        static void Uninit(void);
        // 更新処理
        static void Update(void);


        // 指定キー・ボタンが押されているか
        // @ Ret  : 押されているか
        // @ Arg1 : 判定するキー・ボタン
        template <typename Input>
            requires Concept::SameConcept<Input, KeyboardInput> || Concept::SameConcept<Input, XBoxInput>
        static bool IsPress(const Input& input);
        // 指定キー・ボタンが押された瞬間か
        // @ Ret  : 押された瞬間か
        // @ Arg1 : 判定するキー・ボタン
        template <typename Input>
            requires Concept::SameConcept<Input, KeyboardInput> || Concept::SameConcept<Input, XBoxInput>
        static bool IsTrigger(const Input& input);


        // @ MEMO : 他Platform対応を考慮していないのでひとまずstd::optionalを使用
        // マウス座標ゲッター
        static std::optional<Eigen::Matrix<long, 2, 1>> GetMousePostion(void) { return ms_mousePostion; }
        // マウス座標セッター
        static void SetMousePostion(const Eigen::Matrix<long, 2, 1>& in) { ms_mousePostion = in; }


    private:
        static std::array<uchar, 256> ms_keyTable;    // キーボード入力
        static std::array<uchar, 256> ms_oldKeyTable; // 前フレームキーボード入力
        static std::optional<Eigen::Matrix<long, 2, 1>> ms_mousePostion;    // マウス座標
    };
}




//----- InputSystem 定義
namespace EtherEngine {
    // 指定キー・ボタンが押されているか
    template <typename Input>
        requires Concept::SameConcept<Input, KeyboardInput> || Concept::SameConcept<Input, XBoxInput>
    bool InputSystem::IsPress(const Input& input) {
        if constexpr (Concept::SameConcept<Input, KeyboardInput>) {
            //----- キーボード処理
            return ms_keyTable.at(input.GetKeyboard().GetInput()) & 0x80;
        }
        if constexpr (Concept::SameConcept<Input, XBoxInput>) {
            static_cast(false, "Not yet implemented");
        }
    }
    // 指定キー・ボタンが押された瞬間か
    template <typename Input>
        requires Concept::SameConcept<Input, KeyboardInput> || Concept::SameConcept<Input, XBoxInput>
    bool InputSystem::IsTrigger(const Input& input) {
        if constexpr (Concept::SameConcept<Input, KeyboardInput>) {
            //----- キーボード処理
            bool isOld = ms_oldKeyTable.at(input.GetKeyboard().GetInput()) & 0x80;
            bool isNew = ms_keyTable.at(input.GetKeyboard().GetInput()) & 0x80;

            //----- 返却
            return (isOld == false) && (isNew == true) ? true : false;
        }
        if constexpr (Concept::SameConcept<Input, XBoxInput>) {
            static_cast(false, "Not yet implemented");
        }
    }
}


#endif // !I_BASEINPUT_H
