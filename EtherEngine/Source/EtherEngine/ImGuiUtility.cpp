#include <EtherEngine/ImGuiUtility.h>
#include <EtherEngine/EditorDefine.h>


namespace EtherEngine {
    namespace ImGuiUtility {
        // 無名も表示可能なSelectable
        bool BlankSelectable(const std::string& label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size_arg) {
            return ImGui::Selectable(label == "" ? " " : label.c_str(), selected, flags, size_arg);
        }
        // 無名も表示可能なSelectable
        bool BlankSelectable(const std::string& label, bool* selected, ImGuiSelectableFlags flags, const ImVec2& size_arg) {
            return ImGui::Selectable(label == "" ? " " : label.c_str(), selected, flags, size_arg);
        }


        // コンストラクタ
        RenameableSelectable::RenameableSelectable(void) 
            : m_isRename(false)
            , m_index(0) {
            m_inputText.fill('\0');
        }
        // デストラクタ
        RenameableSelectable::~RenameableSelectable(void) {
        }


        // 改名後の名前ゲッター
        std::string RenameableSelectable::GetRename(void) const {
            if (m_isRename == false) throw std::exception("Error! Rename");
            return std::string(m_inputText.data());
        }
        // リネーム可能なSelectable
        RenameableSelectableMessage RenameableSelectable::Show(const std::string& name, const uint index, const bool isSelect) {
            if (m_isRename && index == m_index) {
                //----- 名前入力
                ImGui::InputText("Rename... :", m_inputText.data(), m_inputText.size());

                //----- リネームを決定して終了するか
                if (ImGui::IsItemFocused() == false || InputSystem::IsPress(EditorKey::INPUT_DECISION)) {
                    //----- リネームモード終了
                    m_isRename = false;

                    //----- 返却
                    return RenameableSelectableMessage::RenameDecision;
                }

                //----- リネームをキャンセルするか
                if (InputSystem::IsPress(EditorKey::INPUT_CANCEL)) {
                    //----- リネームモード終了
                    m_isRename = false;

                    //----- 変更された名前を全てClear
                    m_inputText.fill('\0');

                    //----- 返却
                    return RenameableSelectableMessage::RenameCancel;
                }

                //----- 返却
                return RenameableSelectableMessage::Rename;
            }
            else {
                //----- 通常のSelectable表示
                auto ret = ImGuiUtility::BlankSelectable(name, isSelect);

                //----- F2入力でリネーム
                if (ImGui::IsItemFocused() && InputSystem::IsPress(EditorKey::INPUT_RENAME)) {
                    m_isRename = true;
                    m_index = index;
                    m_inputText.fill('\0');
                    // 文字列コピー
                    for (auto&& it : m_inputText) {
                        for (auto&& cha : name) {
                            it = cha;
                        }
                    }
                }

                //----- 返却
                return ret ? RenameableSelectableMessage::SelectYes : RenameableSelectableMessage::SelectNon;
            }
        }
    }
}
