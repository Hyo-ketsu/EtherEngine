#ifndef I_IMGUIUTILITY_H
#define I_IMGUIUTILITY_H


//----- ImGui用の便利関数
namespace EtherEngine {
    //----- Selectable関連の定義
    namespace ImGuiUtility {
        // 無名も表示可能なSelectable
        bool BlankSelectable(const std::string& label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size_arg = {0,0});
        // 無名も表示可能なSelectable
        bool BlankSelectable(const std::string& label, bool* selected, ImGuiSelectableFlags flags = 0, const ImVec2& size_arg = {0,0});


        // 関数からのメッセージ
        enum class RenameableSelectableMessage {
            SelectNon = 0,  // 選択されていない
            SelectYes,      // 選択された
            Rename,         // リネームモード
            RenameDecision, // リネームが行われた
            RenameCancel,   // リネームがキャンセルされた
        };

        // リネーム可能なSelectableを表示するクラス
        class RenameableSelectable {
        public:
            // コンストラクタ
            // @ Arg1 : 
            RenameableSelectable(void);
            // デストラクタ
            ~RenameableSelectable(void);
            // コピーコンストラクタ
            RenameableSelectable(const RenameableSelectable& copy) = delete;
            // ムーブデストラクタ
            RenameableSelectable(RenameableSelectable&& move) = delete;


            // 改名後の名前ゲッター
            // @ Exce : 改名中
            std::string GetRename(void) const;
            // 入力中ゲッター
            bool GetIsRename(void) const { return m_isRename; }


            // リネーム可能なSelectable
            // @ Ret  : 関数からのメッセージ
            // @ Memo : 改名後の名前はGetRenameで取得して下さい。
            // @ Arg1 : 表示・変更名
            // @ Arg2 : インデックス
            // @ Arg3 : 選択されているか
            RenameableSelectableMessage Show(const std::string& name, const uint index, const bool isSelect);

        private:
            std::array<char, 256> m_inputText;  // 入力改名名
            bool m_isRename; // 現在入力中か
            uint m_index;    // 名前変更をしているインデックス
        };
        
    }
}


#endif // !I_IMGUIUTILITY_H
